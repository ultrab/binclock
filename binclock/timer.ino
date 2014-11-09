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

////////////////////////
//Timer implementation//
////////////////////////

inline void processRTCTimer() //Check, if RTC time updated and call handler if necessary
{
  if (checkTimeChg()) onRTCTimer();
}

inline void processTimer() //Check, if timer interval has passed and call handler if necessary
{
  if ((now - prevTimer) >= (TMR_SECOND-TimerCorr))
  {
    if ((now-prevTimer) > TMR_SECOND) TimerCorr = (now - prevTimer)-TMR_SECOND; //Timer correction allows to adjust interval if timer fired a little off
    else TimerCorr = 0;
    if (TimerCorr >= TMR_SECOND) TimerCorr = 0; //Timer correction interval shouldn't ever get anywhere near the second. However, if this happens for whatever reason, it would break the algorithm, so in that case we'd better drop the correction.
    onTimer(); //Call handler
    prevTimer = now;
  }
}

inline void processHRTimer() //Check, if timer interval has passed and call handler if necessary
{
  if ((now - prevHRTimer) >= (TMR_HIRES-HRTimerCorr))
  {
    if ((now-prevHRTimer) > TMR_HIRES) HRTimerCorr = (now - prevHRTimer)-TMR_HIRES; //Timer correction allows to adjust interval if timer fired a little off
    else HRTimerCorr = 0;
    if (HRTimerCorr >= TMR_HIRES) HRTimerCorr = 0;
    onHRTimer(); //Call handler
    prevHRTimer = now;
  }
}
