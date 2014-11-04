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

/////////////////////////
//LED Buffer operations//
/////////////////////////

inline void pushLEDs() //Push LED buffer onto shift registers
{
  if (dim) { //If dimming mode is used - we push zeroes to turn off all LEDs
    digitalWrite(LATCH,LOW);
    shiftOut(DATA,CLK,LSBFIRST,0);
    shiftOut(DATA,CLK,LSBFIRST,0);
    shiftOut(DATA,CLK,LSBFIRST,0);
    digitalWrite(LATCH,HIGH);
  }
  else { //Else - we feed the shift registers with data
    digitalWrite(LATCH,LOW);
    shiftOut(DATA,CLK,LSBFIRST,led[0]); //LSBFIRST greatly simplifies the logic
    shiftOut(DATA,CLK,LSBFIRST,led[1]);
    shiftOut(DATA,CLK,LSBFIRST,led[2]);
    digitalWrite(LATCH,HIGH);
  }
}

inline void resetLEDs() //Clear LED buffer
{
  for (char i = 0; i < 3; i++)
  {
    led[i] = 0;
  }
}

inline void flashLEDs() //Set LED buffer to all-on state
{
  for (char i = 0; i < 3; i++)
  {
    led[i] = 255;
  }
}
