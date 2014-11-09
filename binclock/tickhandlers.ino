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

////////////////////////////
//Tick processing routines//
////////////////////////////

inline void tickSnooze() //Process snooze timer
{
  if (snooze > 0) snooze--; //Decrease snooze counter until it's zero
  if (snooze == 0) {
    buzzer = true; //And then, sound the buzzer
    flash = true;
    animframe = 0;
    buzzercycle = 0;
    if (dim) dim = false;
  }
}

inline void tickClock() //Sync clock with RTC
{
  updateTimeFromRTC();
}

inline void tickTimer() //Tick timer one second and see if it went off
{
  if (!tpaused) { //Timer is ticked only if it's not paused now
    tseconds--;
    if (tseconds > 59) { //Decrementing from an unsigned zero would cause this variable to wrap around to 255, making this condition valid
      tseconds = 59;
      tminutes--;
      if (tminutes > 59) {
        tminutes = 59;
        thours--;
        if (thours > 23) { //If hours are more than 23 - unsigned wrap around has occured, i.e. timer went off.
          timerset = false; //Buzzer is sounded, timer will be reset to original time
          buzzer = true;
          buzzercycle = 0;
          flash = true;
          animframe = 0;
          thours = tshours;
          tminutes = tsminutes;
          tseconds = tsseconds;
          if (dim) dim = false;
        }
      }
    }
  }
}

inline void checkAlarm() //Check if alarm went off
{
  if ((chours == ahours) && (cminutes == aminutes))
  {
    alarmset = false;
    storeEEPROMAlarmFlag();
    buzzer = true; //Sound the buzzer
    flash = true;
    animframe = 0;
    alarmbzr = true;
    buzzercycle = 0;
    if (dim) dim = false;
  }
}
