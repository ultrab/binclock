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

//////////////////
//Timer handlers//
//////////////////

inline void onRTCTimer() //RTC timekeeping timer
{
  if (set) tickClock(); //Tick clock if set
  if (timerset) tickTimer(); //Tick timer
  if (set && alarmset) checkAlarm(); //Check if alarm went off
  if (alarmbzr && (snooze > 0)) tickSnooze(); //Tick snooze timer
}

inline void onTimer() //Second-resolution timer handler
{
  if (mode == MOD_CLOCK) //In clock mode...
  {
    if (cset == 0)
    {
     if (!set) notSetFlash(); //If we're not in the setting mode - flash hour/minute LEDs each second to indicate that clock aren't set
    }
    else if (cset == 1) setHourFlash(&chours); //If we're setting clock - flash the parameter, which we're setting now
    else if (cset == 2) setMinuteFlash(&cminutes);
  }
  else if (mode == MOD_ALARM) //In alarm mode...
  {
    if (aset == 0)
    {
      if (buzzer && alarmbzr && prevalarm) flashAlarm(); //If alarm went off and we're not setting alarm - we flash alarm time...
      if (!prevalarm) notSetFlash(); //...and if alarm was never set - we flash hour/minute LEDs
    }
    else if (aset == 1) setHourFlash(&ahours); //Highlight the parameter currently being set by flashing it
    else if (aset == 2) setMinuteFlash(&aminutes);
  }
  else if (mode == MOD_TIMER) //In timer mode...
  {
    if (tset == 0)
    {
      if (!prevtimer) notSetFlash(); //If we never set timer - flash hour/minute LEDs...
      if (buzzer && !alarmbzr && prevtimer) notSetFlash(); //...and if timer is buzzing now, we also flash hour/minute LEDs
    }
    else if (tset == 1) setHourFlash(&tshours); //During setting of hours/minutes/seconds, current option is highlighted by LEDs flashing
    else if (tset == 2) setMinuteFlash(&tsminutes);
    else if (tset == 3) setSecondFlash(&tsseconds);
  }
}

inline void onHRTimer() //High-resolution timer (1/8th of second) handler
{
  processRTCTimer(); //Process RTC timer. We do it inside HR timer since polling it from loop wastes too much cycles
  if (buzzer) //We sound buzzer, if it's activated
  {
    soundBuzzer();
  }
  if (mode == MOD_CLOCK) //In clock mode...
  {
    if (cset == 0) //If we're not in setting mode
    {
      if (set) //If clock are set - we display current time.
      {  
        setHours(chours,ampm); //These are handled by HR timer to decrease LED "redraw" lag , e.g. during mode change.
        setMinutes(cminutes);
        setSeconds(cseconds);
      }
      else secondAnim(); //If clock aren't set - we play second LED animation
    }
    else if (cset == 1) secondAnim(); //Second LEDs are also animated during clock setting procedure because you can set only hours and minutes
    else if (cset == 2) secondAnim();
  }
  else if (mode == MOD_ALARM) //In alarm mode...
  {
    if (prevalarm && (aset == 0) && ((!buzzer) || (buzzer && !alarmbzr))) //If we're not in setting mode, if alarm was set at least once and alarm didn't went off...
    {
      setHours(ahours,ampm); //...we display set alarm time
      setMinutes(aminutes);
    }
    secondAnim(); //In alarm mode, we always play second bar animation.
  }
  else if (mode == MOD_TIMER) //In timer mode...
  {
    if (tset == 0) //If we're not in setting mode.
    {
      if (prevtimer && ((!buzzer) || (buzzer && alarmbzr))) //If timer was set at least once and it didn't went off yet...
      {
        setHours(thours,false); //...we display current countdown
        setMinutes(tminutes);
        setSeconds(tseconds);
      }
      if ((!prevtimer) || (buzzer && !alarmbzr && prevtimer)) secondAnim(); //Second bar animation in timer mode is played only during buzzer or if we never set timer before.
    }
    if (!prevtimer) setAMPM(false,false); //We switch off AM/PM LEDs if timer was never set
    else if (timerset && tpaused) setAMPM(true,true); //Both LEDs are set if timer is active, but paused
    else if (timerset) setAMPM(false,true); //PM LED is lit if timer is active
    else setAMPM(true,false); //And AM LED is lit if timer is disabled now
  }
}
