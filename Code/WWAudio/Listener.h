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
 *                 Project Name : WWAudio                                                      *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/WWAudio/Listener.h         $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 2/07/01 6:10p                                               $*
 *                                                                                             *
 *                    $Revision:: 7                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "Sound3D.h"

/////////////////////////////////////////////////////////////////////////////////
//
//	Listener3DClass
//
//	Class defining the 'listeners' 3D position/velocity in the world.  This should
// only be used by the SoundSceneClass.
//
class Listener3DClass : public Sound3DClass {
public:
  //////////////////////////////////////////////////////////////////////
  //	Friend classes
  //////////////////////////////////////////////////////////////////////
  friend class SoundSceneClass;

  //////////////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  //////////////////////////////////////////////////////////////////////
  Listener3DClass();
  virtual ~Listener3DClass();

  //////////////////////////////////////////////////////////////////////
  //	Identification methods
  //////////////////////////////////////////////////////////////////////
  virtual SOUND_CLASSID Get_Class_ID() const { return CLASSID_LISTENER; }

  //////////////////////////////////////////////////////////////////////
  //	Conversion methods
  //////////////////////////////////////////////////////////////////////
  virtual Listener3DClass *As_Listener3DClass() { return this; }

  //////////////////////////////////////////////////////////////////////
  //	Initialization methods
  //////////////////////////////////////////////////////////////////////
  virtual void On_Added_To_Scene();
  virtual void On_Removed_From_Scene();

  //////////////////////////////////////////////////////////////////////
  //	State control methods
  //////////////////////////////////////////////////////////////////////
  // virtual bool Play () { return false; }
  virtual bool Pause() { return false; }
  virtual bool Resume() { return false; }
  virtual bool Stop(bool /*remove*/) { return false; }
  virtual void Seek(unsigned long milliseconds) {}
  virtual SOUND_STATE Get_State() const { return STATE_STOPPED; }

  //////////////////////////////////////////////////////////////////////
  //	Attenuation settings
  //////////////////////////////////////////////////////////////////////
  virtual void Set_Max_Vol_Radius(float radius = 0) {}
  virtual float Get_Max_Vol_Radius() const { return 0; }
  virtual void Set_DropOff_Radius(float radius = 1) {}
  virtual float Get_DropOff_Radius() const { return 0; }

  //////////////////////////////////////////////////////////////////////
  //	Velocity methods
  //////////////////////////////////////////////////////////////////////
  virtual void Set_Velocity(const Vector3 &velocity) {}

protected:
  //////////////////////////////////////////////////////////////////////
  //	Internal representations
  //////////////////////////////////////////////////////////////////////
  virtual void Start_Sample() {}
  virtual void Stop_Sample() {}
  virtual void Resume_Sample() {}
  virtual void End_Sample() {}
  virtual void Set_Sample_Volume(S32 volume) {}
  virtual S32 Get_Sample_Volume() { return 0; }
  virtual void Set_Sample_Pan(S32 pan) {}
  virtual S32 Get_Sample_Pan() { return 64; }
  virtual void Set_Sample_Loop_Count(U32 count) {}
  virtual U32 Get_Sample_Loop_Count() { return 0; }
  virtual void Set_Sample_MS_Position(U32 ms) {}
  virtual void Get_Sample_MS_Position(S32 *len, S32 *pos) {}
  virtual S32 Get_Sample_Playback_Rate() { return 0; }
  virtual void Set_Sample_Playback_Rate(S32 rate) {}

  //////////////////////////////////////////////////////////////////////
  //	Handle information
  //////////////////////////////////////////////////////////////////////
  virtual void Initialize_Miles_Handle();
  virtual void Allocate_Miles_Handle();
  virtual void Free_Miles_Handle();

private:
  //////////////////////////////////////////////////////////////////////
  //	Private member data
  //////////////////////////////////////////////////////////////////////
};
