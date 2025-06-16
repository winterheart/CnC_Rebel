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
 *                     $Archive:: /Commando/Code/WWAudio/SoundBuffer.cpp                      $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 11/01/01 11:00a                                             $*
 *                                                                                             *
 *                    $Revision:: 12                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "SoundBuffer.h"
#include "rawfile.h"
#include "wwdebug.h"
#include "utils.h"
#include "ffactory.h"
#include "win.h"
#include "wwprofile.h"

/////////////////////////////////////////////////////////////////////////////////
//
//	SoundBufferClass
//
SoundBufferClass::SoundBufferClass()
    : m_Buffer(nullptr), m_Length(0), m_Filename(nullptr), m_Duration(0), m_Rate(0), m_Bits(0), m_Channels(0),
      m_Type(WAVE_FORMAT_IMA_ADPCM) {}

/////////////////////////////////////////////////////////////////////////////////
//
//	~SoundBufferClass
//
SoundBufferClass::~SoundBufferClass() {
  SAFE_FREE(m_Filename);
  SoundBufferClass::Free_Buffer();
}

/////////////////////////////////////////////////////////////////////////////////
//
//	Free_Buffer
//
void SoundBufferClass::Free_Buffer() {
  // Free the buffer's memory
  if (m_Buffer != nullptr) {
    delete[] m_Buffer;
    m_Buffer = nullptr;
  }

  // Make sure we reset the length
  m_Length = 0L;
}

/////////////////////////////////////////////////////////////////////////////////
//
//	Determine_Stats
//
void SoundBufferClass::Determine_Stats(unsigned char *buffer) {
  WWPROFILE("Determine_Stats");

  MMSLockClass lock;

  m_Duration = 0;
  m_Rate = 0;
  m_Channels = 0;
  m_Bits = 0;
  m_Type = WAVE_FORMAT_IMA_ADPCM;

  // Attempt to get statistical information about this sound
  AILSOUNDINFO info = {0};
  if ((buffer != nullptr) && (::AIL_WAV_info(buffer, &info) != 0)) {

    // Cache this information
    m_Rate = info.rate;
    m_Channels = info.channels;
    m_Bits = info.bits;
    m_Type = info.format;

    // Determine how long this sound will play for
    float bytes_sec = float((m_Channels * m_Rate * m_Bits) >> 3);
    m_Duration = (unsigned long)((((float)m_Length) / bytes_sec) * 1000.0F);
  }
}

/////////////////////////////////////////////////////////////////////////////////
//
//	Set_Filename
//
void SoundBufferClass::Set_Filename(const char *name) {
  SAFE_FREE(m_Filename);
  if (name != nullptr) {
    m_Filename = ::strdup(name);
  }
}

/////////////////////////////////////////////////////////////////////////////////
//
//	Load_From_File
//
bool SoundBufferClass::Load_From_File(const char *filename) {
  WWPROFILE("SoundBufferClass::Load_From_File");
  WWDEBUG_SAY(("Loading sound file %s.\r\n", filename));

  // Assume failure
  bool retval = false;

  // Param OK?
  WWASSERT(filename != nullptr);
  if (filename != nullptr) {

    // Create a file object and pass it onto the appropriate function
    FileClass *file = _TheFileFactory->Get_File(filename);
    if (file) {
      retval = Load_From_File(*file);
      _TheFileFactory->Return_File(file);
    }
    file = nullptr;
  }

  // Return the true/false result code
  return retval;
}

/////////////////////////////////////////////////////////////////////////////////
//
//	Load_From_File
//
bool SoundBufferClass::Load_From_File(FileClass &file) {
  WWPROFILE("SoundBufferClass::Load_From_File");

  MMSLockClass lock;

  // Assume failure
  bool retval = false;

  // Start from scratch
  Free_Buffer();
  Set_Filename(file.File_Name());

  // Open the file if necessary
  bool we_opened = false;
  if (file.Is_Open() == false) {
    we_opened = (file.Open() == TRUE);
  }

  // Determine the size of the buffer
  m_Length = file.Size();
  WWASSERT(m_Length > 0L);
  if (m_Length > 0L) {

    // Allocate a new buffer of the correct length and read the contents
    // of the file into the buffer
    m_Buffer = new unsigned char[m_Length];
    retval = bool(file.Read(m_Buffer, m_Length) == (int)m_Length);

    // If we failed, free the buffer
    if (retval == false) {
      Free_Buffer();
    }
    Determine_Stats(m_Buffer);
  }

  // Close the file if necessary
  if (we_opened) {
    file.Close();
  }

  // Return the true/false result code
  return retval;
}

/////////////////////////////////////////////////////////////////////////////////
//
//	Load_From_Memory
//
bool SoundBufferClass::Load_From_Memory(unsigned char *mem_buffer, unsigned long size) {
  MMSLockClass lock;

  // Assume failure
  bool retval = false;

  // Start from scratch
  Free_Buffer();
  Set_Filename("unknown.wav");

  // Params OK?
  WWASSERT(mem_buffer != nullptr);
  WWASSERT(size > 0L);
  if ((mem_buffer != nullptr) && (size > 0L)) {

    // Allocate a new buffer of the correct length and copy the contents
    // into the buffer
    m_Length = size;
    m_Buffer = new unsigned char[m_Length];
    ::memcpy(m_Buffer, mem_buffer, size);
    retval = true;

    // If we failed, free the buffer
    if (retval == false) {
      Free_Buffer();
    }
    Determine_Stats(m_Buffer);
  }

  // Return the true/false result code
  return retval;
}

/////////////////////////////////////////////////////////////////////////////////
//
//	StreamSoundBufferClass
//
StreamSoundBufferClass::StreamSoundBufferClass() : SoundBufferClass() {}

/////////////////////////////////////////////////////////////////////////////////
//
//	~StreamSoundBufferClass
//
StreamSoundBufferClass::~StreamSoundBufferClass() = default;

/////////////////////////////////////////////////////////////////////////////////
//
//	Free_Buffer
//
void StreamSoundBufferClass::Free_Buffer() {}

/////////////////////////////////////////////////////////////////////////////////
//
//	Load_From_File
//
/////////////////////////////////////////////////////////////////////////////////
bool StreamSoundBufferClass::Load_From_File(const char *filename) {
  WWPROFILE("StreamSoundBufferClass::Load_From_File");
  return true;
}

/////////////////////////////////////////////////////////////////////////////////
//
//	Load_From_File
//
/////////////////////////////////////////////////////////////////////////////////
bool StreamSoundBufferClass::Load_From_File(FileClass &file) {
  WWPROFILE("StreamSoundBufferClass::Load_From_File");

  MMSLockClass lock;

  // Start from scratch
  Free_Buffer();
  Set_Filename(file.File_Name());

  // Open the file if necessary
  bool we_opened = false;
  if (file.Is_Open() == false) {
    we_opened = (file.Open() == TRUE);
  }

  m_Length = file.Size();

  // Allocate a new buffer of the correct length and read the contents
  // of the file into the buffer
  unsigned char buffer[4096] = {0};
  file.Read(buffer, sizeof(buffer));
  Determine_Stats(buffer);

  // Close the file if necessary
  if (we_opened) {
    file.Close();
  }

  return true;
}
