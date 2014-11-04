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

/////////////
//RTC Tools//
/////////////

inline void getTimeFromRTC() //If EEPROM is marked, we try to get time from RTC
{
  if (readEEPROMFlag())
  {
    clock.getTime();
    chours = clock.hour;
    cminutes = clock.minute;
    cseconds = clock.second;
    set = true;
  }
}

inline boolean checkTimeChg() //See if time has updated
{
  clock.getTime();
  if ((prevHourRTC != clock.hour) || (prevMinuteRTC != clock.minute) || (prevSecondRTC != clock.second))
  {
    prevHourRTC = clock.hour;
    prevMinuteRTC = clock.minute;
    prevSecondRTC = clock.second;
    return true;
  }
  return false;
}

inline void updateTimeFromRTC() //Get new time from RTC
{
  chours = clock.hour;
  cminutes = clock.minute;
  cseconds = clock.second;
}

inline void storeTimeToRTC() //We store the new time into RTC
{
  clock.fillByHMS(chours,cminutes,cseconds);
  clock.setTime();
  if (!readEEPROMFlag()) setEEPROMFlag(true);
}
