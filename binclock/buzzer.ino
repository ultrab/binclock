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

////////////////////
//Buzzer utilities//
////////////////////

inline void soundBuzzer() //Alarm beep sequence
{
  if (bzrsound[buzzercycle]) tone(BZR,FRQ_ALARM,LEN_ALARM);
  buzzercycle++;
  if (buzzercycle > 7) buzzercycle = 0;
}

inline void btnBuzz() //Pushbutton beep
{
  tone(BZR,FRQ_BTN,LEN_BTN);
}

inline void POSTBuzz() //POST beep
{
  tone(BZR,FRQ_POST,LEN_POST);
}

inline void resetBuzz() //Device reset beep
{
  tone(BZR,FRQ_RESET,LEN_RESET);
}
