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

////////////////
//EEPROM Tools//
////////////////

inline boolean readEEPROMFlag() //Read RTC flag from EEPROM
{
  if (EEPROM.read(EEP_USERTC) != 0) return true;
  else return false;
}

inline void setEEPROMFlag(boolean flag) //Set EEPROM RTC flag
{
  if (flag) EEPROM.write(EEP_USERTC,1);
  else EEPROM.write(EEP_USERTC,0);
}

inline void readEEPROM() //Read config from EEPROM
{
  if (set)
  {
  ahours = EEPROM.read(EEP_AHOURS);
  aminutes = EEPROM.read(EEP_AMINUTES);
  prevalarm = EEPROM.read(EEP_PREVALARM);
  alarmset = EEPROM.read(EEP_ALARMSET);
  }
  thours = tshours = EEPROM.read(EEP_TSHOURS);
  tminutes = tsminutes = EEPROM.read(EEP_TSMINUTES);
  tseconds = tsseconds = EEPROM.read(EEP_TSSECONDS);
  prevtimer = EEPROM.read(EEP_PREVTIMER);
  ampm = EEPROM.read(EEP_AMPM);
}

inline void storeEEPROMAlarmTime() //Store alarm time
{
  EEPROM.write(EEP_AHOURS,ahours);
  EEPROM.write(EEP_AMINUTES,aminutes);
  EEPROM.write(EEP_PREVALARM,prevalarm);
}

inline void storeEEPROMAlarmFlag() //Store alarm-set flag
{
  EEPROM.write(EEP_ALARMSET,alarmset);
}

inline void storeTimeFormatFlag() //Store current time format flag
{
  EEPROM.write(EEP_AMPM,ampm);
}

inline void storeEEPROMTimer() //Store timer settings
{
  EEPROM.write(EEP_TSHOURS,tshours);
  EEPROM.write(EEP_TSMINUTES,tsminutes);
  EEPROM.write(EEP_TSSECONDS,tsseconds);
  EEPROM.write(EEP_PREVTIMER,prevtimer);
}

inline void wipeEEPROM() //Wipe all EEPROM data
{
  EEPROM.write(EEP_USERTC,0);
  EEPROM.write(EEP_AHOURS,0);
  EEPROM.write(EEP_AMINUTES,0);
  EEPROM.write(EEP_PREVALARM,0);
  EEPROM.write(EEP_ALARMSET,0);
  EEPROM.write(EEP_TSHOURS,0);
  EEPROM.write(EEP_TSMINUTES,0);
  EEPROM.write(EEP_TSSECONDS,0);
  EEPROM.write(EEP_PREVTIMER,0);
  EEPROM.write(EEP_AMPM,0);
}
