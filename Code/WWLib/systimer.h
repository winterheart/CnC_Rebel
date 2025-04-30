/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**	Copyright 2025 CnC Rebel Developers.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/***********************************************************************************************
 ***                            Confidential - Westwood Studios                              ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Commando                                                     *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwlib/systimer.h                             $*
 *                                                                                             *
 *                      $Author:: Steve_t                                                     $*
 *                                                                                             *
 *                     $Modtime:: 12/09/01 6:41p                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once
#ifndef _SYSTIMER_H

#include "always.h"
#include <windows.h>
#include "mmsys.h"

#define TIMEGETTIME SystemTime.Get

/*
** Class that just wraps around timeGetTime()
**
**
*/
class SysTimeClass {

public:
  /*
  ** Get. Use everywhere you would use timeGetTime
  */
  __forceinline unsigned long Get();
  __forceinline unsigned long operator()() { return (Get()); }
  __forceinline operator unsigned long() { return (Get()); }

  /*
  ** Use periodically (like every few days!) to make sure the timer doesn't wrap.
  */
  void Reset();

  /*
  ** See if the timer is about to wrap.
  */
  bool Is_Getting_Late();

private:
  /*
  ** Time we were first called.
  */
  unsigned long StartTime;

  /*
  ** Time to add after timer wraps.
  */
  unsigned long WrapAdd;
};

extern SysTimeClass SystemTime;

/***********************************************************************************************
 * SysTimeClass::Get -- Wrapper around system timeGetTime() api call                           *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   Current system time in ms                                                         *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   10/25/2001 1:38PM ST : Created                                                            *
 *=============================================================================================*/
__forceinline unsigned long SysTimeClass::Get() {
  /*
  ** This has to be static here since we don't know if we will get called in a global constructor of another object
  *before our
  ** constructor gets called. In fact, we don't even have a constructor because it's pointless.
  */
  static bool is_init = false;

  if (!is_init) {
    Reset();
    is_init = true;
  }

  unsigned long time = timeGetTime();
  if (time > StartTime) {
    return (time - StartTime);
  }

  /*
  ** Timer wrapped around. Eeek.
  */
  return (time + WrapAdd);
}

#ifdef timeGetTime
#undef timeGetTime
#define timeGetTime SystemTime.Get
#endif // timeGetTime

#endif //_SYSTIMER_H