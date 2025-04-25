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
 *                 Project Name : Combat
 **
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwui/menubackdrop.h          $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 11/21/01 11:30a                                             $*
 *                                                                                             *
 *                    $Revision:: 6                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __MENU_BACKDROP_H
#define __MENU_BACKDROP_H

#include "wwstring.h"
#include "rendobj.h"

////////////////////////////////////////////////////////////////
//	Forward declarations
////////////////////////////////////////////////////////////////
class SimpleSceneClass;
class CameraClass;

////////////////////////////////////////////////////////////////
//
//	MenuBackDropClass
//
////////////////////////////////////////////////////////////////
class MenuBackDropClass {
public:
  ////////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  ////////////////////////////////////////////////////////////////
  MenuBackDropClass(void);
  virtual ~MenuBackDropClass(void);

  ////////////////////////////////////////////////////////////////
  //	Public methods
  ////////////////////////////////////////////////////////////////

  //
  //	Display methods
  //
  void Render(void);

  //
  //	Configuration
  //
  void Set_Model(const char *name);
  void Remove_Model(void);
  void Set_Animation(const char *anim_name);
  void Set_Animation_Percentage(float percent);
  void Clear_Screen(bool onoff) { ClearScreen = onoff; }

  //
  //	Accessors
  //
  SimpleSceneClass *Peek_Scene(void) { return Scene; };
  CameraClass *Peek_Camera(void) { return Camera; };
  RenderObjClass *Peek_Model(void) const { return Model; }

protected:
  ////////////////////////////////////////////////////////////////
  //	Protected methods
  ////////////////////////////////////////////////////////////////
  void Play_Animation(void);

  ////////////////////////////////////////////////////////////////
  //	Protected member data
  ////////////////////////////////////////////////////////////////
  SimpleSceneClass *Scene;
  CameraClass *Camera;
  StringClass AnimationName;
  RenderObjClass *Model;
  HAnimClass *Anim;
  bool ClearScreen;
};

#endif //__MENU_BACKDROP_H
