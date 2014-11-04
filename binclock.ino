/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

///////////////
//Pin aliases//
///////////////

//Button pins
#define BTN1 2
#define BTN2 13
#define BTN3 12
#define BTN4 11
#define BTN5 10
#define BTN6 9

//LEDs via 74HC595
#define LATCH 8
#define CLK 7
#define DATA 4

//Piezo buzzer pin
#define BZR 3

/////////////
//Constants//
/////////////

//Mode constants
const unsigned char MOD_CLOCK = 1;
const unsigned char MOD_ALARM = 2;
const unsigned char MOD_TIMER = 3;

//Timing constants
const unsigned long TMR_SECOND = 1000;
const unsigned long TMR_HIRES = 125; //1/8th of second

//Second indicator animation array
const unsigned char secanim[10] = {32,16,8,4,2,1,2,4,8,16}; //Oscillator pattern, displayed on the second LEDs

//Buzzer definition array
const boolean bzrsound[8] = {true,true,true,true,false,false,false,false}; //Buzzer activation

//Internal button constants
const unsigned char BTN_SET = 0;
const unsigned char BTN_MODE = 1;
const unsigned char BTN_UP = 2;
const unsigned char BTN_DOWN = 3;
const unsigned char BTN_AMPM = 4;
const unsigned char BTN_DIM = 5;

//Alarm constants
const unsigned int ALM_SNOOZE = 300; //5-minute snooze

//Tone constants
const unsigned int LEN_ALARM = 85;
const unsigned int LEN_BTN = 100;
const unsigned int LEN_POST = 200;
const unsigned int FRQ_ALARM = 3800;
const unsigned int FRQ_BTN = 6000;
const unsigned int FRQ_POST = 4000;

////////////////////
//Global variables//
////////////////////

//Shared state
unsigned char led[3]; //LED byte buffer. Contains raw bits, which will be fed to 3 daisy-chained 74HC595's
unsigned char mode = MOD_CLOCK; //Current mode. By default, we go into clock mode.
boolean btn[6] = {false,false,false,false,false,false}; //Button state buffer. Used to determine if button press was already handled.
unsigned long now = 0; //Current milliseconds counter
unsigned long prevTimer = 0; //Previous milliseconds counter
unsigned long TimerCorr = 0; //Interval correction
unsigned long prevHRTimer = 0; //Previous high-res milliseconds counter
unsigned long HRTimerCorr = 0; //High-res interval correction
boolean dim = false; //If this variable is true, we switch off all LEDs (night mode)
boolean ampm = false; //If true, we display hours in 12-hour system rather than 24-hour system.

//Animation state
boolean flash = true; //State variable used for flashing effects.
unsigned char animframe = 0; //Current animation frame of second LEDs

//Buzzer state
boolean buzzer = false; //If true, buzzer will be sounded
unsigned char buzzercycle = 0; //Current cycle of buzzer signal
boolean alarmbzr = false; //Whether buzzer was sounded by alarm. If true, this enables snooze function
unsigned int snooze = 0; //Snooze timer

//Clock mode state
boolean set = false; //Whether clock is set.
unsigned char cset = 0; //Current phase of setting clock (total 3)
unsigned char chours = 0; //Current time
unsigned char cminutes = 0;
unsigned char cseconds = 0;

//Alarm mode state
boolean alarmset = false; //Whether alarm is set
unsigned char aset = 0; //Current phase of alarm setting (total 3)
boolean prevalarm = false; //Whether alarm was ever set
unsigned char ahours = 0; //Alarm time
unsigned char aminutes = 0;

//Timer mode state
boolean timerset = false; //Whether timer is set
boolean tpaused = false; //Whether timer is paused
boolean prevtimer = false; //Whether timer was ever set
unsigned char tset = 0; //Current phase of timer setting (total 4)
unsigned char tshours = 0; //Last saved timer settings
unsigned char tsminutes = 0;
unsigned char tsseconds = 0;
unsigned char thours = 0; //Current timer variables
unsigned char tminutes = 0;
unsigned char tseconds = 0;

////////////////////////////////
//Initialization and loop code//
////////////////////////////////

void setup()
{
  pinMode(BTN1,INPUT_PULLUP); //Initialize button pins as inputs via internal pull-up resistors
  pinMode(BTN2,INPUT_PULLUP);
  pinMode(BTN3,INPUT_PULLUP);
  pinMode(BTN4,INPUT_PULLUP);
  pinMode(BTN5,INPUT_PULLUP);
  pinMode(BTN6,INPUT_PULLUP);
  pinMode(LATCH,OUTPUT); //Initialize LED and buzzer pins as outputs
  pinMode(CLK,OUTPUT);
  pinMode(BZR,OUTPUT);
  pinMode(DATA,OUTPUT);
  resetLEDs();
  POST(); //Do the power-on self test
}

void loop()
{
  scanBtn(); //Scan button state and process button handlers
  now = millis(); //Update timer. Millis counter rollover won't affect the logic
  processTimer(); //Process regular timer
  processHRTimer(); //Process HR timer
  setAlarm(alarmset || alarmbzr); //Alarm LED is set if either alarm is set or we're in snooze mode
  setMode(mode); //Set mode LEDs to display current mode
  setBacklight(true,true); //Backlight LEDs are always on
  pushLEDs(); //Push current LED state to the shift registers
}
