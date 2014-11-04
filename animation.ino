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

/////////////////
//LED Animation//
/////////////////

void setHourFlash(unsigned char *hrptr) //Hours setting animation. Function accepts pointer to hour value to allow reusability for all modes.
{
  if (flash) {
    if (*hrptr == 0 && !ampm) setHours(31,false);
    else setHours(*hrptr,ampm);
  }
  else {
    setHours(0,false);
  }
  flash = !flash;
}

void setMinuteFlash(unsigned char *mnptr) //Minutes setting animation. Function accepts pointer to minute value to allow reusability for all modes.
{
  if (flash) {
    if (*mnptr == 0) setMinutes(63);
    else setMinutes(*mnptr);
  }
  else {
    setMinutes(0);
  }
  flash = !flash;
}

void setSecondFlash(unsigned char *scptr) //Seconds setting animation. Function accepts pointer to second value to allow reusability for all modes.
{
  if (flash) {
    if (*scptr == 0) setSeconds(63);
    else setSeconds(*scptr);
  }
  else {
    setSeconds(0);
  }
  flash = !flash;
}

inline void notSetFlash() //Not set animation with flashing hour/minute LEDs
{
  if (flash) {
    setHours(31,false);
    setMinutes(63);
  }
  else {
    setHours(0,false);
    setMinutes(0);
  }
  flash = !flash;
}

inline void flashAlarm() //Alarm flash
{
  if (flash) {
    if (ahours == 0 && !ampm) setHours(31,false);
    else setHours(ahours,ampm);
    if (aminutes == 0) setMinutes(63);
    else setMinutes(aminutes);
  }
  else {
    setHours(0,false);
    setMinutes(0);
  }
  flash = !flash;
}

inline void secondAnim() //Seconds LED oscillator animation
{
  setSeconds(secanim[animframe]);
  animframe++;
  if (animframe > 9) animframe = 0;
}
