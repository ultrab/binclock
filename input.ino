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
//Input processing code//
/////////////////////////

inline void scanBtn() //We read button state and call appropriate input handlers
{
  if ((digitalRead(BTN1) == LOW) && (!btn[BTN_SET])) //Connecting buttons via internal pull-up resistor causes it's effect to be reversed (LOW on press, HIGH on release)
  {
    btn[BTN_SET] = true;
    if (!dim) handleBtn1(); //All buttons except for DIM are disabled if LEDs are switched off
    btnBuzz();
  }
  if (digitalRead(BTN1) == HIGH)
  {
    btn[BTN_SET] = false;
  }
  if ((digitalRead(BTN2) == LOW) && (!btn[BTN_MODE]))
  {
    btn[BTN_MODE] = true;
    if (!dim) handleBtn2();
    btnBuzz();
  }
  if (digitalRead(BTN2) == HIGH)
  {
    btn[BTN_MODE] = false;
  }
  if ((digitalRead(BTN3) == LOW) && (!btn[BTN_UP]))
  {
    btn[BTN_UP] = true;
    if (!dim) handleBtn3();
    btnBuzz();
  }
  if (digitalRead(BTN3) == HIGH)
  {
    btn[BTN_UP] = false;
  }
  if ((digitalRead(BTN4) == LOW) && (!btn[BTN_DOWN]))
  {
    btn[BTN_DOWN] = true;
    if (!dim) handleBtn4();
    btnBuzz();
  }
  if (digitalRead(BTN4) == HIGH)
  {
    btn[BTN_DOWN] = false;
  }
  if ((digitalRead(BTN5) == LOW) && (!btn[BTN_AMPM]))
  {
    btn[BTN_AMPM] = true;
    if (!dim) handleBtn5();
    btnBuzz();
  }
  if (digitalRead(BTN5) == HIGH)
  {
    btn[BTN_AMPM] = false;
  }
  if ((digitalRead(BTN6) == LOW) && (!btn[BTN_DIM]))
  {
    btn[BTN_DIM] = true;
    handleBtn6();
    btnBuzz();
  }
  if (digitalRead(BTN6) == HIGH)
  {
    btn[BTN_DIM] = false;
  }
}
