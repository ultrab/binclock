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

///////////////////////////////
//LED Buffer bit manipulators//
///////////////////////////////

inline void setHours(unsigned char hours) //Set hours LEDs
{
  led[2] &= 7; //Reset previously set bits with ANDing
  led[2] |= (hours << 3); //Aligning hours properly and ORing it to the LED buffer
}

inline void setHours12(unsigned char hours) //Set hours LEDs in 12-hour system
{
  if (hours == 0) //If it's 0 hours in 24-hour system, it's 12 AM.
  {
    setAMPM(true,false);
    setHours(12);
  }
  else if (hours < 12) //Then, until 12 PM, we just set AM LED and assign time
  {
    setAMPM(true,false);
    setHours(hours);
  }
  else if (hours == 12) //If it's 12 in 24-hour system, we set PM LED
  {
    setAMPM(false,true);
    setHours(12);
  }
  else //Finally, if it's more than 12 hours, we set hour LEDs to (Hours-12) and light up PM LED
  {
    setAMPM(false,true);
    setHours(hours-12);
  }
}

inline void setHours(unsigned char hours, boolean twelve) //Set hours LEDs, automatically selecting appropriate clock system (24/12) accoring to passed boolean value
{
  if (twelve) setHours12(hours);
  else {
    setHours(hours);
    setAMPM(false,false);
  }
}

inline void setMinutes(unsigned char minutes) //Set minutes LEDs
{
  led[1] &= 31;
  led[2] &= 248;
  unsigned char tmp = minutes & 7;
  led[1] |= (tmp << 5);
  tmp = minutes & 56;
  led[2] |= (tmp >> 3);
}

inline void setSeconds(unsigned char seconds) //Set seconds LEDs
{
  led[0] &= 127;
  led[1] &= 224;
  unsigned char tmp = seconds & 1;
  led[0] |= (tmp << 7);
  tmp = seconds & 62;
  led[1] |= (tmp >> 1);
}


inline void setAMPM(boolean AM, boolean PM) //Set AM/PM indication
{
  led[0] &= 159;
  if (AM) led[0] |= 64;
  if (PM) led[0] |= 32;
}

inline void setAlarm(boolean set) //Set alarm indication LED
{
  led[0] &= 239;
  if (set) led[0] |= 16;
}

inline void setMode(unsigned char mode) //Set mode LEDs
{
  led[0] &= 243;
  switch (mode) {
    case MOD_CLOCK:
      led[0] |= 8;
      break;
    case MOD_ALARM:
      led[0] |= 4;
      break;
    case MOD_TIMER:
      led[0] |= 12;
      break;
    default:
      break;
  }
}

inline void setBacklight(boolean first, boolean second) //Set backlight LEDs state
{
  led[0] &= 252;
  if (first) led[0] |= 2;
  if (second) led[0] |= 1;
}
