/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
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
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WWPhys                                                       *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwphys/wwphystrig.h                          $*
 *                                                                                             *
 *                       Author:: Greg_h                                                       *
 *                                                                                             *
 *                     $Modtime:: 8/08/00 9:57a                                               $*
 *                                                                                             *
 *                    $Revision:: 8                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef WWPHYSTRIG_H
#define WWPHYSTRIG_H

/*
** Debug triggers for WWPhys
** These are ID's for various debugging operations that the application can
** trigger inside of WWPhys.  Just hook a trigger handler into the WWDebug library
** and when you see the trigger id come in, return true or false depending on whether
** the you want to trigger the behavior
*/
enum {
  WWPHYS_TRIGGER_COLLISION_DEBUGGING = 0x200,
  WWPHYS_TRIGGER_COLLISION_DISPLAY = 0x201,
  WWPHYS_TRIGGER_INVERT_VIS = 0x202,
  WWPHYS_TRIGGER_DISABLE_VIS = 0x203,
};

#endif
