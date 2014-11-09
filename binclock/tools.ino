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

/////////
//Tools//
/////////

void(* softReset) (void) = 0; //Software reset function

inline void fullResetPoll() //Reset device to factory settings (resetting EEPROM) if SET is pressed;
{
  if (digitalRead(BTN1) == LOW) //If SET is pressed during POST - we reset the device
  {
    resetBuzz();
    wipeEEPROM();
    delay(LEN_RESET);
    softReset();
  }
}

inline void POST() //Power-on self test. We just flash all LEDs and sound the buzzer.
{
  flashLEDs(); //Flash all LEDs
  pushLEDs();
  POSTBuzz(); //Sound a short beep
  delay(2000); //Wait
  resetLEDs();
  pushLEDs(); //Reset LEDs
  fullResetPoll(); //Check for hard reset
}
