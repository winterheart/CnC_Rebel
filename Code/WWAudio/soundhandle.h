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
 *                     $Archive:: /Commando/Code/WWAudio/soundhandle.h           $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 8/13/01 3:11p                                               $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "wwaudio.h"

//////////////////////////////////////////////////////////////////////
//	Forward declarations
//////////////////////////////////////////////////////////////////////
class Sound3DHandleClass;
class Sound2DHandleClass;
class SoundStreamHandleClass;
class SoundBufferClass;
class ListenerHandleClass;

//////////////////////////////////////////////////////////////////////
//
//	SoundHandleClass
//
//////////////////////////////////////////////////////////////////////
class SoundHandleClass {
public:
  ///////////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  ///////////////////////////////////////////////////////////////////
  SoundHandleClass();
  virtual ~SoundHandleClass();

  ///////////////////////////////////////////////////////////////////
  //	Public methods
  ///////////////////////////////////////////////////////////////////

  //
  //	RTTI
  //
  virtual Sound3DHandleClass *As_Sound3DHandleClass() { return nullptr; }
  virtual Sound2DHandleClass *As_Sound2DHandleClass() { return nullptr; }
  virtual SoundStreamHandleClass *As_SoundStreamHandleClass() { return nullptr; }
  virtual ListenerHandleClass *As_ListenerHandleClass() { return nullptr; }

  //
  //	Handle access
  //
  virtual H3DSAMPLE Get_H3DSAMPLE() { return nullptr; }
  virtual HSAMPLE Get_HSAMPLE() { return nullptr; }
  virtual HSTREAM Get_HSTREAM() { return nullptr; }

  //
  //	Initialization
  //
  virtual void Set_Miles_Handle(uint32 handle) = 0;
  virtual void Initialize(SoundBufferClass *buffer);

  //
  //	Sample control
  //
  virtual void Start_Sample() = 0;
  virtual void Stop_Sample() = 0;
  virtual void Resume_Sample() = 0;
  virtual void End_Sample() = 0;
  virtual void Set_Sample_Pan(S32 pan) = 0;
  virtual S32 Get_Sample_Pan() = 0;
  virtual void Set_Sample_Volume(S32 volume) = 0;
  virtual S32 Get_Sample_Volume() = 0;
  virtual void Set_Sample_Loop_Count(U32 count) = 0;
  virtual U32 Get_Sample_Loop_Count() = 0;
  virtual void Set_Sample_MS_Position(U32 ms) = 0;
  virtual void Get_Sample_MS_Position(S32 *len, S32 *pos) = 0;
  virtual void Set_Sample_User_Data(S32 i, U32 val) = 0;
  virtual U32 Get_Sample_User_Data(S32 i) = 0;
  virtual S32 Get_Sample_Playback_Rate() = 0;
  virtual void Set_Sample_Playback_Rate(S32 rate) = 0;

protected:
  ///////////////////////////////////////////////////////////////////
  //	Protected methods
  ///////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////
  //	Protected member data
  ///////////////////////////////////////////////////////////////////
  SoundBufferClass *Buffer;
};
