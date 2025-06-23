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
 *                     $Archive:: /Commando/Code/WWAudio/sound3dhandle.cpp                    $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 10/31/01 3:00p                                              $*
 *                                                                                             *
 *                    $Revision:: 3                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "Sound3DHandle.h"
#include "AudibleSound.h"
#include "wwprofile.h"

//////////////////////////////////////////////////////////////////////
//
//	Sound3DHandleClass
//
//////////////////////////////////////////////////////////////////////
Sound3DHandleClass::Sound3DHandleClass() : SampleHandle((H3DSAMPLE)INVALID_MILES_HANDLE) {}

//////////////////////////////////////////////////////////////////////
//
//	~Sound3DHandleClass
//
//////////////////////////////////////////////////////////////////////
Sound3DHandleClass::~Sound3DHandleClass() = default;

//////////////////////////////////////////////////////////////////////
//
//	Initialize
//
//////////////////////////////////////////////////////////////////////
void Sound3DHandleClass::Initialize(SoundBufferClass *buffer) {
  WWPROFILE("Sound3DHandleClass::Initialize");

  SoundHandleClass::Initialize(buffer);

  if (SampleHandle != (H3DSAMPLE)INVALID_MILES_HANDLE && Buffer != nullptr) {

    //
    //	Configure the 3D sample
    //
    U32 success = ::AIL_set_3D_sample_file(SampleHandle, Buffer->Get_Raw_Buffer());

    S32 test1 = 0;
    S32 test2 = 0;
    Get_Sample_MS_Position(&test1, &test2);

    //
    //	Check for success
    //
    WWASSERT(success != 0);
    if (success == 0) {
      WWDEBUG_SAY(("WWAudio: Couldn't set 3d sample file.  Reason %s\r\n", ::AIL_last_error()));
    }
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Start_Sample
//
//////////////////////////////////////////////////////////////////////
void Sound3DHandleClass::Start_Sample() {
  if (SampleHandle != (H3DSAMPLE)INVALID_MILES_HANDLE) {
    ::AIL_start_3D_sample(SampleHandle);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Stop_Sample
//
//////////////////////////////////////////////////////////////////////
void Sound3DHandleClass::Stop_Sample() {
  if (SampleHandle != (H3DSAMPLE)INVALID_MILES_HANDLE) {
    ::AIL_stop_3D_sample(SampleHandle);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Resume_Sample
//
//////////////////////////////////////////////////////////////////////
void Sound3DHandleClass::Resume_Sample() {
  if (SampleHandle != (H3DSAMPLE)INVALID_MILES_HANDLE) {
    ::AIL_resume_3D_sample(SampleHandle);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	End_Sample
//
//////////////////////////////////////////////////////////////////////
void Sound3DHandleClass::End_Sample() {
  if (SampleHandle != (H3DSAMPLE)INVALID_MILES_HANDLE) {
    ::AIL_end_3D_sample(SampleHandle);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Set_Sample_Pan
//
//////////////////////////////////////////////////////////////////////
void Sound3DHandleClass::Set_Sample_Pan(S32 /*pan*/) {}

//////////////////////////////////////////////////////////////////////
//
//	Get_Sample_Pan
//
//////////////////////////////////////////////////////////////////////
S32 Sound3DHandleClass::Get_Sample_Pan() { return 64; }

//////////////////////////////////////////////////////////////////////
//
//	Set_Sample_Volume
//
//////////////////////////////////////////////////////////////////////
void Sound3DHandleClass::Set_Sample_Volume(S32 volume) {
  if (SampleHandle != (H3DSAMPLE)INVALID_MILES_HANDLE) {
    ::AIL_set_3D_sample_volume(SampleHandle, volume);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Get_Sample_Volume
//
//////////////////////////////////////////////////////////////////////
S32 Sound3DHandleClass::Get_Sample_Volume() {
  S32 retval = 0;

  if (SampleHandle != (H3DSAMPLE)INVALID_MILES_HANDLE) {
    retval = ::AIL_3D_sample_volume(SampleHandle);
  }

  return retval;
}

//////////////////////////////////////////////////////////////////////
//
//	Set_Sample_Loop_Count
//
//////////////////////////////////////////////////////////////////////
void Sound3DHandleClass::Set_Sample_Loop_Count(U32 count) {
  if (SampleHandle != (H3DSAMPLE)INVALID_MILES_HANDLE) {
    ::AIL_set_3D_sample_loop_count(SampleHandle, count);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Get_Sample_Loop_Count
//
//////////////////////////////////////////////////////////////////////
U32 Sound3DHandleClass::Get_Sample_Loop_Count() {
  U32 retval = 0;

  if (SampleHandle != (H3DSAMPLE)INVALID_MILES_HANDLE) {
    retval = ::AIL_3D_sample_loop_count(SampleHandle);
  }

  return retval;
}

//////////////////////////////////////////////////////////////////////
//
//	Set_Sample_MS_Position
//
//////////////////////////////////////////////////////////////////////
void Sound3DHandleClass::Set_Sample_MS_Position(U32 ms) {
  if (SampleHandle != (H3DSAMPLE)INVALID_MILES_HANDLE) {

    WWASSERT(Buffer != nullptr);
    U32 bytes_per_sec = (Buffer->Get_Rate() * Buffer->Get_Bits()) >> 3;
    U32 bytes = (ms * bytes_per_sec) / 1000;
    bytes += (bytes & 1);
    ::AIL_set_3D_sample_offset(SampleHandle, bytes);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Get_Sample_MS_Position
//
//////////////////////////////////////////////////////////////////////
void Sound3DHandleClass::Get_Sample_MS_Position(S32 *len, S32 *pos) {
  if (SampleHandle != (H3DSAMPLE)INVALID_MILES_HANDLE) {

    WWASSERT(Buffer != nullptr);
    if (pos != nullptr) {
      U32 bytes = ::AIL_3D_sample_offset(SampleHandle);
      U32 bytes_per_sec = (Buffer->Get_Rate() * Buffer->Get_Bits()) >> 3;
      U32 ms = (bytes * 1000) / bytes_per_sec;
      (*pos) = ms;
    }

    if (len != nullptr) {
      U32 bytes = ::AIL_3D_sample_length(SampleHandle);
      U32 bytes_per_sec = (Buffer->Get_Rate() * Buffer->Get_Bits()) >> 3;
      U32 ms = (bytes * 1000) / bytes_per_sec;
      (*len) = ms;
    }
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Set_Sample_User_Data
//
//////////////////////////////////////////////////////////////////////
void Sound3DHandleClass::Set_Sample_User_Data(S32 i, U32 val) {
  if (SampleHandle != (H3DSAMPLE)INVALID_MILES_HANDLE) {
    ::AIL_set_3D_object_user_data(SampleHandle, i, val);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Get_Sample_User_Data
//
//////////////////////////////////////////////////////////////////////
U32 Sound3DHandleClass::Get_Sample_User_Data(S32 i) {
  U32 retval = 0;

  if (SampleHandle != (H3DSAMPLE)INVALID_MILES_HANDLE) {
    retval = AIL_3D_object_user_data(SampleHandle, i);
  }

  return retval;
}

//////////////////////////////////////////////////////////////////////
//
//	Get_Sample_Playback_Rate
//
//////////////////////////////////////////////////////////////////////
S32 Sound3DHandleClass::Get_Sample_Playback_Rate() {
  S32 retval = 0;

  if (SampleHandle != (H3DSAMPLE)INVALID_MILES_HANDLE) {
    retval = ::AIL_3D_sample_playback_rate(SampleHandle);
  }

  return retval;
}

//////////////////////////////////////////////////////////////////////
//
//	Set_Sample_Playback_Rate
//
//////////////////////////////////////////////////////////////////////
void Sound3DHandleClass::Set_Sample_Playback_Rate(S32 rate) {
  if (SampleHandle != (H3DSAMPLE)INVALID_MILES_HANDLE) {
    ::AIL_set_3D_sample_playback_rate(SampleHandle, rate);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Set_Miles_Handle
//
//////////////////////////////////////////////////////////////////////
void Sound3DHandleClass::Set_Miles_Handle(uint32 handle) {
  WWASSERT(SampleHandle == (H3DSAMPLE)INVALID_MILES_HANDLE);

  SampleHandle = (H3DSAMPLE)handle;
}
