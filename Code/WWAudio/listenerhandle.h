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
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : wwaudio                                                      *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/WWAudio/listenerhandle.h                     $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 8/13/01 11:54a                                              $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "sound3dhandle.h"

//////////////////////////////////////////////////////////////////////
//
//	ListenerHandleClass
//
//////////////////////////////////////////////////////////////////////
class ListenerHandleClass : public Sound3DHandleClass {
public:
  ///////////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  ///////////////////////////////////////////////////////////////////
  ListenerHandleClass();
  ~ListenerHandleClass();

  ///////////////////////////////////////////////////////////////////
  //	Public methods
  ///////////////////////////////////////////////////////////////////

  //
  //	RTTI
  //
  ListenerHandleClass *As_ListenerHandleClass() { return this; }

  //
  //	Inherited
  //
  void Initialize(SoundBufferClass *buffer);
  void Start_Sample() {}
  void Stop_Sample() {}
  void Resume_Sample() {}
  void End_Sample() {}
  void Set_Sample_Volume(S32 volume) {}
  S32 Get_Sample_Volume() { return 0; }
  void Set_Sample_Pan(S32 pan) {}
  S32 Get_Sample_Pan() { return 64; }
  void Set_Sample_Loop_Count(U32 count) {}
  U32 Get_Sample_Loop_Count() { return 0; }
  void Set_Sample_MS_Position(U32 ms) {}
  void Get_Sample_MS_Position(S32 *len, S32 *pos) {}
  S32 Get_Sample_Playback_Rate() { return 0; }
  void Set_Sample_Playback_Rate(S32 rate) {}

protected:
  ///////////////////////////////////////////////////////////////////
  //	Protected methods
  ///////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////
  //	Protected member data
  ///////////////////////////////////////////////////////////////////
};
