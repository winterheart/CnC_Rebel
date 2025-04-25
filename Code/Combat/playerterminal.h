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
 *                 Project Name : Combat                                                       *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/Combat/playerterminal.h                      $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 8/22/01 5:34p                                               $*
 *                                                                                             *
 *                    $Revision:: 4                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __PLAYERTERMINAL_H
#define __PLAYERTERMINAL_H

////////////////////////////////////////////////////////////////
//	Forward declarations
////////////////////////////////////////////////////////////////
class SoldierGameObj;

////////////////////////////////////////////////////////////////
//
//	PlayerTerminalClass
//
////////////////////////////////////////////////////////////////
class PlayerTerminalClass {
public:
  ////////////////////////////////////////////////////////////////
  //	Public constants
  ////////////////////////////////////////////////////////////////
  typedef enum { TYPE_NONE = -1, TYPE_GDI = 0, TYPE_NOD, TYPE_MUTANT } TYPE;

  ////////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  ////////////////////////////////////////////////////////////////
  virtual ~PlayerTerminalClass(void) {}

  ////////////////////////////////////////////////////////////////
  //	Public methods
  ////////////////////////////////////////////////////////////////

  //
  //	Display methods
  //
  virtual void Display_Terminal(SoldierGameObj * /*player*/, TYPE /*type*/) {}
  virtual void Display_Default_Terminal_For_Player(SoldierGameObj * /*player*/) {}

  //
  //	Static methods
  //
  static PlayerTerminalClass *Get_Instance(void) { return _TheInstance; }

protected:
  ////////////////////////////////////////////////////////////////
  //	Protected methods
  ////////////////////////////////////////////////////////////////
  static PlayerTerminalClass *_TheInstance;
};

#endif //__PLAYERTERMINAL_H
