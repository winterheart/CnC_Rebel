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
 *                     $Archive:: /Commando/Code/WWAudio/soundstreamhandle.cpp                $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 8/23/01 4:47p                                               $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "soundstreamhandle.h"
#include "audiblesound.h"

//////////////////////////////////////////////////////////////////////
//
//	SoundStreamHandleClass
//
//////////////////////////////////////////////////////////////////////
SoundStreamHandleClass::SoundStreamHandleClass()
    : SampleHandle((HSAMPLE)INVALID_MILES_HANDLE), StreamHandle((HSTREAM)INVALID_MILES_HANDLE) {}

//////////////////////////////////////////////////////////////////////
//
//	~SoundStreamHandleClass
//
//////////////////////////////////////////////////////////////////////
SoundStreamHandleClass::~SoundStreamHandleClass() = default;

//////////////////////////////////////////////////////////////////////
//
//	Initialize
//
//////////////////////////////////////////////////////////////////////
void SoundStreamHandleClass::Initialize(SoundBufferClass *buffer) {
  SoundHandleClass::Initialize(buffer);

  if (Buffer != nullptr) {

    //
    //	Create a stream from the sample handle
    //
#if 0
    StreamHandle = ::AIL_open_stream_by_sample (WWAudioClass::Get_Instance ()->Get_2D_Driver (),
								SampleHandle, buffer->Get_Filename (), 0);
#endif
    // TODO: Problems?
    StreamHandle = ::AIL_open_stream(WWAudioClass::Get_Instance()->Get_2D_Driver(), buffer->Get_Filename(), 0);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Start_Sample
//
//////////////////////////////////////////////////////////////////////
void SoundStreamHandleClass::Start_Sample() {
  if (StreamHandle != (HSTREAM)INVALID_MILES_HANDLE) {
    ::AIL_start_stream(StreamHandle);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Stop_Sample
//
//////////////////////////////////////////////////////////////////////
void SoundStreamHandleClass::Stop_Sample() {
  if (StreamHandle != (HSTREAM)INVALID_MILES_HANDLE) {
    ::AIL_pause_stream(StreamHandle, 1);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Resume_Sample
//
//////////////////////////////////////////////////////////////////////
void SoundStreamHandleClass::Resume_Sample() {
  if (StreamHandle != (HSTREAM)INVALID_MILES_HANDLE) {
    ::AIL_pause_stream(StreamHandle, 0);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	End_Sample
//
//////////////////////////////////////////////////////////////////////
void SoundStreamHandleClass::End_Sample() {
  //
  //	Stop the sample and then release our hold on the stream handle
  //
  Stop_Sample();

  if (StreamHandle != (HSTREAM)INVALID_MILES_HANDLE) {
    ::AIL_close_stream(StreamHandle);
    StreamHandle = (HSTREAM)INVALID_MILES_HANDLE;
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Set_Sample_Pan
//
//////////////////////////////////////////////////////////////////////
void SoundStreamHandleClass::Set_Sample_Pan(S32 pan) {
  if (StreamHandle != (HSTREAM)INVALID_MILES_HANDLE) {
    ::AIL_set_stream_pan(StreamHandle, pan);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Get_Sample_Pan
//
//////////////////////////////////////////////////////////////////////
S32 SoundStreamHandleClass::Get_Sample_Pan() {
  S32 retval = 0;

  if (StreamHandle != (HSTREAM)INVALID_MILES_HANDLE) {
    retval = ::AIL_stream_pan(StreamHandle);
  }

  return retval;
}

//////////////////////////////////////////////////////////////////////
//
//	Set_Sample_Volume
//
//////////////////////////////////////////////////////////////////////
void SoundStreamHandleClass::Set_Sample_Volume(S32 volume) {
  if (StreamHandle != (HSTREAM)INVALID_MILES_HANDLE) {
    ::AIL_set_stream_volume(StreamHandle, volume);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Get_Sample_Volume
//
//////////////////////////////////////////////////////////////////////
S32 SoundStreamHandleClass::Get_Sample_Volume() {
  S32 retval = 0;

  if (StreamHandle != (HSTREAM)INVALID_MILES_HANDLE) {
    retval = ::AIL_stream_volume(StreamHandle);
  }

  return retval;
}

//////////////////////////////////////////////////////////////////////
//
//	Set_Sample_Loop_Count
//
//////////////////////////////////////////////////////////////////////
void SoundStreamHandleClass::Set_Sample_Loop_Count(U32 count) {
  if (StreamHandle != (HSTREAM)INVALID_MILES_HANDLE) {
    ::AIL_set_stream_loop_block(StreamHandle, 0, -1);
    ::AIL_set_stream_loop_count(StreamHandle, count);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Get_Sample_Loop_Count
//
//////////////////////////////////////////////////////////////////////
U32 SoundStreamHandleClass::Get_Sample_Loop_Count() {
  U32 retval = 0;

  if (StreamHandle != (HSTREAM)INVALID_MILES_HANDLE) {
    ::AIL_stream_loop_count(StreamHandle);
  }

  return retval;
}

//////////////////////////////////////////////////////////////////////
//
//	Set_Sample_MS_Position
//
//////////////////////////////////////////////////////////////////////
void SoundStreamHandleClass::Set_Sample_MS_Position(U32 ms) {
  if (StreamHandle != (HSTREAM)INVALID_MILES_HANDLE) {
    ::AIL_set_stream_ms_position(StreamHandle, ms);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Get_Sample_MS_Position
//
//////////////////////////////////////////////////////////////////////
void SoundStreamHandleClass::Get_Sample_MS_Position(S32 *len, S32 *pos) {
  if (StreamHandle != (HSTREAM)INVALID_MILES_HANDLE) {
    ::AIL_stream_ms_position(StreamHandle, len, pos);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Set_Sample_User_Data
//
//////////////////////////////////////////////////////////////////////
void SoundStreamHandleClass::Set_Sample_User_Data(S32 i, U32 val) {
  if (SampleHandle != (HSAMPLE)INVALID_MILES_HANDLE) {
    ::AIL_set_sample_user_data(SampleHandle, i, val);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Get_Sample_User_Data
//
//////////////////////////////////////////////////////////////////////
U32 SoundStreamHandleClass::Get_Sample_User_Data(S32 i) {
  U32 retval = 0;

  if (SampleHandle != (HSAMPLE)INVALID_MILES_HANDLE) {
    retval = ::AIL_sample_user_data(SampleHandle, i);
  }

  return retval;
}

//////////////////////////////////////////////////////////////////////
//
//	Get_Sample_Playback_Rate
//
//////////////////////////////////////////////////////////////////////
S32 SoundStreamHandleClass::Get_Sample_Playback_Rate() {
  S32 retval = 0;

  if (StreamHandle != (HSTREAM)INVALID_MILES_HANDLE) {
    retval = ::AIL_stream_playback_rate(StreamHandle);
  }

  return retval;
}

//////////////////////////////////////////////////////////////////////
//
//	Set_Sample_Playback_Rate
//
//////////////////////////////////////////////////////////////////////
void SoundStreamHandleClass::Set_Sample_Playback_Rate(S32 rate) {
  if (StreamHandle != (HSTREAM)INVALID_MILES_HANDLE) {
    ::AIL_set_stream_playback_rate(StreamHandle, rate);
  }
}

//////////////////////////////////////////////////////////////////////
//
//	Set_Miles_Handle
//
//////////////////////////////////////////////////////////////////////
void SoundStreamHandleClass::Set_Miles_Handle(uint32 handle) { SampleHandle = (HSAMPLE)handle; }
