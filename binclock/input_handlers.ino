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

///////////////////
//Button handlers//
///////////////////

inline void handleBtn1() //Handle SET button
{
  if (mode == MOD_CLOCK) {
    if (cset == 0) { //Begin setting hours
      cset = 1;
      set = false;
      flash = true;
      setMinutes(cminutes);
    }
    else if (cset == 1) { //Move on to setting minutes
      cset = 2;
      flash = true;
      setHours(chours,ampm);
    }
    else if (cset == 2) { //We apply new time and start the clock
      setHours(chours,ampm);
      setMinutes(cminutes);
      cseconds = 0;
      setSeconds(cseconds);
      cset = 0;
      storeTimeToRTC(); //Store new time to RTC
      set = true;
      flash = true;
      animframe = 0;
    }
  }
  else if (mode == MOD_ALARM) {
    if (aset == 0 && set) { //Setting alarm works only if clock are set. Begin setting alarm hour
      aset = 1;
      alarmset = false;
      storeEEPROMAlarmFlag();
      flash = true;
      setMinutes(aminutes);
    }
    else if (aset == 1) { //Move on to setting minutes
      aset = 2;
      flash = true;
      setHours(ahours,ampm);
    }
    else if (aset == 2) { //We apply new alarm time and enable alarm
      setHours(ahours,ampm);
      setMinutes(aminutes);
      aset = 0;
      alarmset = true;
      alarmbzr = false;
      snooze = 0;
      prevalarm = true;
      flash = true;
      animframe = 0;
      storeEEPROMAlarmTime();
      storeEEPROMAlarmFlag();
    }
  }
  else if (mode == MOD_TIMER) {
    if (tset == 0) { //Start setting hours
      tset = 1;
      timerset = false;
      flash = true;
      setMinutes(tsminutes);
      setSeconds(tsseconds);
    }
    else if (tset == 1) { //Move on to setting minutes
      tset = 2;
      flash = true;
      setHours(tshours,false);
    }
    else if (tset == 2) { //Move on to setting seconds
      tset = 3;
      flash = true;
      setMinutes(tsminutes);
    }
    else if (tset == 3) { //Apply new timer interval and start countdown
      setHours(tshours,false);
      setMinutes(tsminutes);
      setSeconds(tsseconds);
      tseconds = tsseconds;
      tminutes = tsminutes;
      thours = tshours;
      tset = 0;
      tpaused = false;
      timerset = true;
      prevtimer = true;
      flash = true;
      animframe = 0;
      storeEEPROMTimer();
    }
  }
}

inline void handleBtn2() //Handle MODE button
{
  if (mode == MOD_CLOCK) {
    if (cset == 0) //Mode switching works only if we're not in middle of setting clock/alarm/timer
    {
      mode = MOD_ALARM;
      flash = true;
      animframe = 0;
      setHours(0,false);
      setMinutes(0);
      setSeconds(0);
    }
  }
  else if (mode == MOD_ALARM) {
    if (aset == 0)
    {
      mode = MOD_TIMER;
      flash = true;
      animframe = 0;
      setHours(0,false);
      setMinutes(0);
      setSeconds(0);
    }
  }
  else if (mode == MOD_TIMER) {
    if (tset == 0)
    {
      mode = MOD_CLOCK;
      flash = true;
      animframe = 0;
      setHours(0,false);
      setMinutes(0);
      setSeconds(0);
    }
  }
}

inline void handleBtn3() //Handle UP button
{
  if (buzzer) { //Buzzer is highest priority input interceptor. Pressing UP during buzzer will stop it.
    buzzer = false;
    buzzercycle = 0;
    alarmbzr = false;
    snooze = 0;
    flash = true;
  }
  else if (mode == MOD_CLOCK) {
    if (cset == 1) { //In clock mode, UP button works only during time setting (to increase current option)
      chours++;
      if (chours > 23) chours = 0;
      setHours(chours,ampm);
    }
    else if (cset == 2) {
      cminutes++;
      if (cminutes > 59) cminutes = 0;
      setMinutes(cminutes);
    }
  }
  else if (mode == MOD_ALARM) {
    if (aset == 0) { //Pressing UP in alarm mode will cause it to toggle alarm (if it was ever set). Pressing UP with snooze active will also cancel it.
      if (prevalarm)
      {
        if (!alarmbzr)
        {
          alarmset = !alarmset;
          storeEEPROMAlarmFlag();
        }
        else
        {
          alarmbzr = false;
          snooze = 0;
          flash = true;
        }
        setAlarm(alarmset || alarmbzr);
      }
    }
    else if (aset == 1) { //During alarm setting, UP button increases current option
      ahours++;
      if (ahours > 23) ahours = 0;
      setHours(ahours,ampm);
    }
    else if (aset == 2) {
      aminutes++;
      if (aminutes > 59) aminutes = 0;
      setMinutes(aminutes);
    }
  }
  else if (mode == MOD_TIMER) {
    if (tset == 0) //Pressing UP is timer mode will cause it to toggle timer with last set interval (if it was ever set). If timer is stopped, it's countdown reset to the last set interval.
    {
      if (prevtimer)
      {
        thours = tshours;
        tminutes = tsminutes;
        tseconds = tsseconds;
        timerset = !timerset;
        tpaused = false;
      }
      if (!prevtimer) setAMPM(false,false);
      else if (timerset && tpaused) setAMPM(true,true);
      else if (timerset) setAMPM(false,true);
      else setAMPM(true,false);
    }
    else if (tset == 1) { //During timer setting, UP button increases current option
      tshours++;
      if (tshours > 23) tshours = 0;
      setHours(tshours,false);
    }
    else if (tset == 2) {
      tsminutes++;
      if (tsminutes > 59) tsminutes = 0;
      setMinutes(tsminutes);
    }
    else if (tset == 3) {
      tsseconds++;
      if (tsseconds > 59) tsseconds = 0;
      setSeconds(tsseconds);
    }
  }
}

inline void handleBtn4() //Handle DOWN button
{
  if (buzzer && alarmbzr) { //Buzzer is highest priority input interceptor. If buzzer was sounded by alarm (not the timer), pressing DOWN will delay it for 5 minutes (snooze function).
    buzzer = false;
    buzzercycle = 0;
    snooze = ALM_SNOOZE;
    flash = true;
  }
  else if (mode == MOD_CLOCK) {
    if (cset == 1) { //In clock mode, DOWN button works only during time setting (to decrease current option)
      chours--;
      if (chours > 23) chours = 23;
      setHours(chours,ampm);
    }
    else if (cset == 2) {
      cminutes--;
      if (cminutes > 59) cminutes = 59;
      setMinutes(cminutes);
    }
  }
  else if (mode == MOD_ALARM) {
    if (aset == 1) { //In alarm mode, DOWN button works only during time setting (to decrease current option)
      ahours--;
      if (ahours > 23) ahours = 23;
      setHours(ahours,ampm);
    }
    else if (aset == 2) {
      aminutes--;
      if (aminutes > 59) aminutes = 59;
      setMinutes(aminutes);
    }
  }
  else if (mode == MOD_TIMER) {
    if (tset == 0) //Pressing DOWN while timer is ticking will cause it to toggle pause
    {
      if (prevtimer && timerset) tpaused = !tpaused;
      if (!prevtimer) setAMPM(false,false);
      else if (timerset && tpaused) setAMPM(true,true);
      else if (timerset) setAMPM(false,true);
      else setAMPM(true,false);
    }
    else if (tset == 1) { //During timer setting, DOWN button increases current option
      tshours--;
      if (tshours > 23) tshours = 23;
      setHours(tshours,false);
    }
    else if (tset == 2) {
      tsminutes--;
      if (tsminutes > 59) tsminutes = 59;
      setMinutes(tsminutes);
    }
    else if (tset == 3) {
      tsseconds--;
      if (tsseconds > 59) tsseconds = 59;
      setSeconds(tsseconds);
    }
  }
}

inline void handleBtn5() //Handle 24/12 button.
{
  if (mode == MOD_CLOCK) { //This button works only in clock and alarm modes
    if (cset == 0 && set) //It doesn't work if current mode (clock or alarm) is not set. It also won't work in middle of setting clock/alarm
    {
      ampm = !ampm;
      storeTimeFormatFlag();
      setHours(chours,ampm);
    }
  }
  else if (mode == MOD_ALARM) {
    if (aset == 0 && prevalarm)
    {
      ampm = !ampm;
      storeTimeFormatFlag();
      setHours(chours,ampm);
    }
  }
}

inline void handleBtn6() //Handle DIM button
{
  if (mode == MOD_CLOCK) { //DIM works in all modes if we're not in middle of setting time
    if (cset == 0) dim = !dim;
  }
  else if (mode == MOD_ALARM) {
    if (aset == 0) dim = !dim;
  }
  else if (mode == MOD_TIMER) {
    if (tset == 0) dim = !dim;
  }
}
