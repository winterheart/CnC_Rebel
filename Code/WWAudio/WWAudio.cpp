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
 *                     $Archive:: /Commando/Code/WWAudio/WWAudio.cpp                          $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 1/30/02 2:47p                                               $*
 *                                                                                             *
 *                    $Revision:: 76                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include <algorithm>
#include <windows.h>

#include "always.h"
#include "WWAudio.h"
#include "WWDebug.h"
#include "Utils.h"
#include "RealCRC.h"
#include "SoundBuffer.h"
#include "AudibleSound.h"
#include "Sound3D.h"
#include "WW3D.h"
#include "SoundScene.h"
#include "SoundPseudo3D.h"
#include "FFactory.h"
#include "Registry.h"
#include "Threads.h"
#include "LogicalSound.h"
#include "LogicalListener.h"
#include "definitionclassids.h"
#include "wwmemlog.h"
#include "wwprofile.h"
#include "Ini.h"

#ifdef G_CODE_BASE
#include "..\wwlib\argv.h"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////
//	Static member initialization
////////////////////////////////////////////////////////////////////////////////////////////////
WWAudioClass *WWAudioClass::_theInstance = nullptr;
HANDLE WWAudioClass::_TimerSyncEvent = nullptr;

////////////////////////////////////////////////////////////////////////////////////////////////
//	Registry value names
////////////////////////////////////////////////////////////////////////////////////////////////
const char *VALUE_NAME_IS_STEREO = "stereo";
const char *VALUE_NAME_BITS = "bits";
const char *VALUE_NAME_HERTZ = "hertz";
const char *VALUE_NAME_DEVICE_NAME = "device name";
const char *VALUE_NAME_MUSIC_ENABLED = "music enabled";
const char *VALUE_NAME_SOUND_ENABLED = "sound enabled";
const char *VALUE_NAME_DIALOG_ENABLED = "dialog enabled";
const char *VALUE_NAME_CINEMATIC_ENABLED = "cinematic enabled";
const char *VALUE_NAME_MUSIC_VOL = "music volume";
const char *VALUE_NAME_SOUND_VOL = "sound volume";
const char *VALUE_NAME_DIALOG_VOL = "dialog volume";
const char *VALUE_NAME_CINEMATIC_VOL = "cinematic volume";
const char *VALUE_NAME_SPEAKER_TYPE = "speaker type";

const int MAX_VIRTUAL_CHANNELS = 100;

////////////////////////////////////////////////////////////////////////////////////////////////
//	INI names
////////////////////////////////////////////////////////////////////////////////////////////////
const char *WWAUDIO_INI_FILENAME = "WWAudio.ini";
const char *WWAUDIO_INI_RELATIVE_PATHNAME = "Data\\WWAudio.ini";
const char *INI_DEFAULT_VOLUME_SECTION = "Default Volume";
const char *INI_MUSIC_VOLUME_ENTRY = "MUSIC_VOLUME";
const char *INI_SOUND_VOLUME_ENTRY = "SOUND_VOLUME";
const char *INI_DIALOG_VOLUME_ENTRY = "DIALOG_VOLUME";
const char *INI_CINEMATIC_VOLUME_ENTRY = "CINEMATIC_VOLUME";

////////////////////////////////////////////////////////////////////////////////////////////////
//	Local inlines
////////////////////////////////////////////////////////////////////////////////////////////////
__inline bool WWAudioClass::Is_OK_To_Give_Handle(const AudibleSoundClass &sound_obj) {
  bool is_ok = false;
  AudibleSoundClass::SOUND_TYPE type = sound_obj.Get_Type();
  if (m_AreNewSoundsEnabled) {
    if (((type == AudibleSoundClass::TYPE_SOUND_EFFECT) && m_AreSoundEffectsEnabled) ||
        ((type == AudibleSoundClass::TYPE_MUSIC) && m_IsMusicEnabled) ||
        ((type == AudibleSoundClass::TYPE_DIALOG) && m_IsDialogEnabled) ||
        ((type == AudibleSoundClass::TYPE_CINEMATIC) && m_IsCinematicSoundEnabled)) {
      is_ok = true;
    }
  }
  return is_ok;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	WWAudioClass
//
// 1/25/2002 12:13PM ST. Added the 'lite' flag which causes us to go through the motions of
//                       creating the object (including theInstance) so it exists but disables
//                       the call that initialises Miles and doesn't create a sound scene.
//
////////////////////////////////////////////////////////////////////////////////////////////////
WWAudioClass::WWAudioClass(bool lite)
    : m_PlaybackRate(44100), m_PlaybackBits(16), m_PlaybackStereo(true), m_MusicVolume(DEF_MUSIC_VOL),
      m_SoundVolume(DEF_SFX_VOL), m_RealMusicVolume(DEF_MUSIC_VOL), m_RealSoundVolume(DEF_SFX_VOL),
      m_DialogVolume(DEF_DIALOG_VOL), m_CinematicVolume(DEF_CINEMATIC_VOL), m_Max2DSamples(DEF_2D_SAMPLE_COUNT),
      m_Max3DSamples(DEF_3D_SAMPLE_COUNT), m_Max2DBufferSize(DEF_MAX_2D_BUFFER_SIZE),
      m_Max3DBufferSize(DEF_MAX_3D_BUFFER_SIZE), m_UpdateTimer(-1), m_IsMusicEnabled(true), m_IsDialogEnabled(true),
      m_IsCinematicSoundEnabled(true), m_AreSoundEffectsEnabled(true), m_AreNewSoundsEnabled(true),
      m_FileFactory(nullptr), m_BackgroundMusic(nullptr), m_CachedIsMusicEnabled(true), m_CachedIsDialogEnabled(true),
      m_CachedIsCinematicSoundEnabled(true), m_CachedAreSoundEffectsEnabled(true), m_SoundScene(nullptr),
      m_CurrPage(PAGE_PRIMARY), m_Driver2D(nullptr), m_Driver3D(0), m_Driver3DPseudo(0),
      m_ReverbFilter(INVALID_MILES_HANDLE), m_SpeakerType(0), m_Playlist(PAGE_COUNT),
      m_MaxCacheSize(DEF_CACHE_SIZE * 1024), m_CurrentCacheSize(0), m_EffectsLevel(0),
      m_ReverbRoomType(ENVIRONMENT_GENERIC), m_NonDialogFadeTime(DEF_FADE_TIME), m_FadeType(FADE_NONE), m_FadeTimer(0),
      AudioIni(nullptr) {
  ::InitializeCriticalSection(&MMSLockClass::_MSSLockCriticalSection);

  m_ForceDisable = lite;

  //
  // Start Miles Sound System
  //
  if (!lite) {
    AIL_startup();
  }
  _theInstance = this;
  _TimerSyncEvent = ::CreateEvent(nullptr, TRUE, FALSE, "WWAUDIO_TIMER_SYNC");

  //
  // Set some default values
  //
  Set_Sound_Effects_Volume();
  Set_Music_Volume();

  //
  //	Allocate the virtual channels
  //
  for (int index = 0; index < MAX_VIRTUAL_CHANNELS; index++) {
    m_VirtualChannels.push_back(nullptr);
  }

  // Create a new sound scene to manage our 3D sounds...
  if (!lite) {
    m_SoundScene = new SoundSceneClass;
  }

  m_Max3DBufferSize = m_Max3DBufferSize * 2.0F;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	~WWAudioClass
//
////////////////////////////////////////////////////////////////////////////////////////////////
WWAudioClass::~WWAudioClass() {
  //
  //	Stop the background music
  //
  Set_Background_Music(nullptr);

  //
  //	Make sure the delayed-release thread is terminated
  // before we exit (otherwise the process will crash).
  //
  WWAudioThreadsClass::End_Delayed_Release_Thread();

  Shutdown();
  _theInstance = nullptr;
  ::CloseHandle(_TimerSyncEvent);
  _TimerSyncEvent = nullptr;

  ::DeleteCriticalSection(&MMSLockClass::_MSSLockCriticalSection);

  //
  //	Free the list of logical "types".
  //
  Reset_Logical_Types();

  delete AudioIni;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Flush_Cache
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Flush_Cache() {
  // Loop through all the hash indicies
  for (auto &m_CachedBuffer : m_CachedBuffers) {

    // Loop through all the buffers at this hash index and free them all
    for (int index = 0; index < m_CachedBuffer.Count(); index++) {
      CACHE_ENTRY_STRUCT &info = m_CachedBuffer[index];

      // Free the buffer data
      REF_PTR_RELEASE(info.buffer);
    }

    // Remove all the entries for this hash index
    m_CachedBuffer.Delete_All();
  }

  m_CurrentCacheSize = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Open_2D_Device
//
////////////////////////////////////////////////////////////////////////////////////////////////
WWAudioClass::DRIVER_TYPE_2D WWAudioClass::Open_2D_Device(LPWAVEFORMAT format) {
  MMSLockClass lock;

  //
  //	Store the playback settings for future reference
  //
  m_PlaybackRate = format->nSamplesPerSec;
  m_PlaybackBits = (format->nAvgBytesPerSec << 3) / (format->nChannels * format->nSamplesPerSec);
  m_PlaybackStereo = bool(format->nChannels > 1);

  //
  // Assume we will open the DirectSound driver
  //
  DRIVER_TYPE_2D type = DRIVER2D_DSOUND;

  // First close the current 2D device and take
  // all the sound handles away from the sound objects.
  Close_2D_Device();

  AIL_set_preference(AIL_LOCK_PROTECTION, NO);

  // Try to use DirectSound if possible
  S32 success = ::AIL_set_preference(DIG_USE_WAVEOUT, FALSE);
  // WWASSERT (success == AIL_NO_ERROR);		// This assert fires if there is no sound card.

  // Open the driver
  success = ::AIL_waveOutOpen(&m_Driver2D, nullptr, 0, format);

  // Do we need to switch from direct sound to waveout?
  if ((success == AIL_NO_ERROR) && (m_Driver2D != nullptr) && (m_Driver2D->emulated_ds == TRUE)) {
    ::AIL_waveOutClose(m_Driver2D);
    success = 2;
    WWDEBUG_SAY(("WWAudio: Detected 2D DirectSound emulation, switching to WaveOut.\r\n"));
  }

  // If we couldn't open the direct sound device, then use the
  // default wave out device
  if (success != AIL_NO_ERROR) {

    // Try to use the default wave out driver
    success = ::AIL_set_preference(DIG_USE_WAVEOUT, TRUE);
    // WWASSERT (success == AIL_NO_ERROR);	// This assert fires if there is no sound card.

    // Open the driver
    success = ::AIL_waveOutOpen(&m_Driver2D, nullptr, 0, format);
    type = (success == AIL_NO_ERROR) ? DRIVER2D_WAVEOUT : DRIVER2D_ERROR;
  }

  // Allocate all the available handles if we were successful
  if (success == AIL_NO_ERROR) {
    Allocate_2D_Handles();
    ReAssign_2D_Handles();
  } else {
    Close_2D_Device();
    WWDEBUG_SAY(("WWAudio: Error initializing 2D device.\r\n"));
  }

  // Return the opened device type
  return type;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Open_2D_Device
//
////////////////////////////////////////////////////////////////////////////////////////////////
WWAudioClass::DRIVER_TYPE_2D WWAudioClass::Open_2D_Device(bool stereo, int bits, int hertz) {
  // Build a wave format structure from the params
  PCMWAVEFORMAT wave_format = {0};
  wave_format.wf.wFormatTag = WAVE_FORMAT_PCM;
  wave_format.wf.nChannels = stereo ? 2 : 1;
  wave_format.wf.nSamplesPerSec = hertz;
  wave_format.wf.nAvgBytesPerSec = (wave_format.wf.nChannels * wave_format.wf.nSamplesPerSec * bits) >> 3;
  wave_format.wf.nBlockAlign = (wave_format.wf.nChannels * bits) >> 3;
  wave_format.wBitsPerSample = bits;

  DRIVER_TYPE_2D type = DRIVER2D_ERROR;
  while (((type = Open_2D_Device((LPWAVEFORMAT)&wave_format)) == DRIVER2D_ERROR) &&
         (wave_format.wf.nSamplesPerSec >= 11025)) {

    //
    //	Cut the playback rate in half and try again
    //
    wave_format.wf.nSamplesPerSec = wave_format.wf.nSamplesPerSec >> 1;
    wave_format.wf.nAvgBytesPerSec = (wave_format.wf.nChannels * wave_format.wf.nSamplesPerSec * bits) >> 3;
    wave_format.wf.nBlockAlign = (wave_format.wf.nChannels * bits) >> 3;
  }

  // Pass this structure onto the function that actually opens the device
  return type;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Close_2D_Device
//
////////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Close_2D_Device() {
  MMSLockClass lock;

  //
  //	Note:  We MUST close the 3D device when we close the 2D device...
  //
  Close_3D_Device();

  //
  //	Free any 2D sound handles
  //
  Remove_2D_Sound_Handles();
  Release_2D_Handles();

  //
  // Do we have an open driver handle to close?
  //
  bool retval = false;
  if (m_Driver2D != nullptr) {

    //
    // Close the driver
    //
    ::AIL_waveOutClose(m_Driver2D);
    m_Driver2D = nullptr;
    retval = true;
  }

  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Close_3D_Device
//
////////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Close_3D_Device() {
  MMSLockClass lock;

  bool retval = false;

  //
  //	Remove all the handles
  //
  Remove_3D_Sound_Handles();
  Release_3D_Handles();

  //
  // Do we have an open driver handle to close?
  //
  if (m_Driver3D != 0) {
    ::AIL_close_3D_provider(m_Driver3D);
    m_Driver3D = 0;
    retval = true;
  }

  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Get_Sound_Buffer
//
////////////////////////////////////////////////////////////////////////////////////////////////
SoundBufferClass *WWAudioClass::Get_Sound_Buffer(const char *filename, bool is_3d) {
  WWPROFILE("Get_Sound_Buffer");

  //
  // Try to find the buffer in our cache, otherwise create a new buffer.
  //
  SoundBufferClass *buffer = Find_Cached_Buffer(filename);
  if (buffer == nullptr) {
    FileClass *file = Get_File(filename);
    if (file != nullptr && file->Is_Available()) {
      buffer = Create_Sound_Buffer(*file, filename, is_3d);
    } else {
      static int count = 0;
      if (++count < 10) {
        WWDEBUG_SAY(("Sound \"%s\" not found\r\n", filename));
      }
    }
    Return_File(file);
  }

  return buffer;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Get_Sound_Buffer
//
////////////////////////////////////////////////////////////////////////////////////////////////
SoundBufferClass *WWAudioClass::Get_Sound_Buffer(FileClass &file, const char *string_id, bool is_3d) {
  WWMEMLOG(MEM_SOUND);

  //
  // Try to find the buffer in our cache, otherwise create a new buffer.
  //
  SoundBufferClass *buffer = Find_Cached_Buffer(string_id);
  if (buffer == nullptr) {
    buffer = Create_Sound_Buffer(file, string_id, is_3d);
  }

  return buffer;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Find_Cached_Buffer
//
////////////////////////////////////////////////////////////////////////////////////////////////
SoundBufferClass *WWAudioClass::Find_Cached_Buffer(const char *string_id) {
  WWPROFILE("Find_Cached_Buffer");

  SoundBufferClass *sound_buffer = nullptr;

  // Param OK?
  WWASSERT(string_id != nullptr);
  if (string_id != nullptr) {

    //
    // Determine which index in our hash table to use
    //
    int hash_index = ::CRC_Stringi(string_id) & CACHE_HASH_MASK;

    //
    // Loop through all the buffers at this hash index and try to find
    // one that matches the requested name
    //
    for (int index = 0; index < m_CachedBuffers[hash_index].Count(); index++) {

      //
      // Is this the sound buffer we were looking for?
      //
      CACHE_ENTRY_STRUCT &info = m_CachedBuffers[hash_index][index];
      if (info.string_id == string_id) {
        sound_buffer = info.buffer;
        sound_buffer->Add_Ref();
        break;
      }
    }
  }

  //
  // Return a pointer to the cached sound buffer
  //
  return sound_buffer;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Free_Cache_Space
//
////////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Free_Cache_Space(int bytes) {
  int bytes_freed = 0;

  // Loop through all the hash indicies
  for (int hash_index = 0; (hash_index < MAX_CACHE_HASH) && (bytes_freed < bytes); hash_index++) {

    // Loop through all the buffers at this hash index
    for (int index = 0; (index < m_CachedBuffers[hash_index].Count()) && (bytes_freed < bytes); index++) {

      // Can we free this cached buffer?
      CACHE_ENTRY_STRUCT &info = m_CachedBuffers[hash_index][index];
      if ((info.buffer != nullptr) && (info.buffer->Num_Refs() == 1)) {

        // Add the size of this buffer to our count of bytes freed
        bytes_freed += info.buffer->Get_Raw_Length();

        // Free the buffer data
        REF_PTR_RELEASE(info.buffer);

        // Remove this entry from the hash table
        m_CachedBuffers[hash_index].Delete(index);
        index--;
      }
    }
  }

  // Make sure to recompute out current cache size
  m_CurrentCacheSize -= bytes_freed;
  WWASSERT(m_CurrentCacheSize >= 0);

  // Return true if we freed enough bytes in the cache
  return (bytes_freed >= bytes);
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Cache_Buffer
//
////////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Cache_Buffer(SoundBufferClass *buffer, const char *string_id) {
  WWPROFILE("Cache_Buffer");

  // Assume failure
  bool retval = false;

  // Params OK?
  WWASSERT(buffer != nullptr);
  WWASSERT(string_id != nullptr);
  if ((buffer != nullptr) && (string_id != nullptr)) {

    //
    // Attempt to free space in the cache (if needed)
    //
    /*int space_needed = (m_CurrentCacheSize + buffer->Get_Raw_Length ()) - (int)m_MaxCacheSize;
    if (space_needed > 0) {
            Free_Cache_Space (space_needed);
    }*/

    // Do we have enough space in the cache for this buffer?
    // space_needed = (m_CurrentCacheSize + buffer->Get_Raw_Length ()) - (int)m_MaxCacheSize;
    // if (space_needed <= 0) {

    //
    // Determine which index in our hash table to use
    //
    int hash_index = ::CRC_Stringi(string_id) & CACHE_HASH_MASK;

    //
    // Add this buffer to the hash table at the given index.
    //	Note:  The assignment operator caused by the Add call
    //			will add a reference to the sound buffer.
    //
    CACHE_ENTRY_STRUCT info;
    info.string_id = (char *)string_id;
    info.buffer = buffer;
    m_CachedBuffers[hash_index].Add(info);

    // Update our current cache size
    m_CurrentCacheSize += buffer->Get_Raw_Length();
    retval = true;
    //}
  }

  if (retval == false) {
    WWDEBUG_SAY(("Unable to cache sound: %s.\r\n", string_id));
  }

  // Return the true/false result code
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Create_Sound_Buffer
//
////////////////////////////////////////////////////////////////////////////////////////////////
SoundBufferClass *WWAudioClass::Create_Sound_Buffer(FileClass &file, const char *string_id, bool is_3d) {
  WWPROFILE("Create_Sound_Buffer");

  SoundBufferClass *sound_buffer = nullptr;

  //
  //	Determine how large this buffer can be
  //
  int max_size = is_3d ? m_Max3DBufferSize : m_Max2DBufferSize;

  //
  // Create a streaming sound buffer object if the
  // file is too large to preload.
  //
  if (file.Size() > max_size) {
    sound_buffer = new StreamSoundBufferClass;
  } else {
    sound_buffer = new SoundBufferClass;
  }
  SET_REF_OWNER(sound_buffer);

  //
  // Create a new sound buffer from the provided file
  //
  bool success = sound_buffer->Load_From_File(file);
  sound_buffer->Set_Filename(string_id);
  WWASSERT(success);

  // If we were successful in creating the sound buffer, then
  // try to cache it as well, otherwise free the buffer and return nullptr.
  if (success && (string_id != nullptr)) {
    Cache_Buffer(sound_buffer, string_id);
  } else if (success == false) {
    REF_PTR_RELEASE(sound_buffer);
  }

  // Return a pointer to the new sound buffer
  return sound_buffer;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Create_Sound_Buffer
//
////////////////////////////////////////////////////////////////////////////////////////////////
SoundBufferClass *WWAudioClass::Create_Sound_Buffer(unsigned char *file_image, unsigned long bytes,
                                                    const char *string_id, bool is_3d) {
  WWPROFILE("Create_Sound_Buffer");

  // Create a new sound buffer from the provided file
  SoundBufferClass *sound_buffer = new SoundBufferClass;
  SET_REF_OWNER(sound_buffer);

  //
  //	Initialize the sound from this piece of memory
  //
  bool success = sound_buffer->Load_From_Memory(file_image, bytes);
  sound_buffer->Set_Filename(string_id);
  WWASSERT(success);

  // If we were successful in creating the sound buffer, then
  // try to cache it as well, otherwise free the buffer and return nullptr.
  if (success && (string_id != nullptr)) {
    Cache_Buffer(sound_buffer, string_id);
  } else if (success == false) {
    REF_PTR_RELEASE(sound_buffer);
  }

  // Return a pointer to the new sound buffer
  return sound_buffer;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Create_Sound_Effect
//
////////////////////////////////////////////////////////////////////////////////////////////////
AudibleSoundClass *WWAudioClass::Create_Sound_Effect(FileClass &file, const char *string_id) {
  WWPROFILE("Create_Sound_Effect");

  // Create a new sound object
  AudibleSoundClass *sound_obj = NEW_REF(AudibleSoundClass, ());
  if (Is_Disabled() == false) {

    // Try to find the buffer in our cache, otherwise create a new buffer.
    SoundBufferClass *buffer = Get_Sound_Buffer(file, string_id, false);

    // Pass the actual sound data onto the sound object
    sound_obj->Set_Buffer(buffer);
    REF_PTR_RELEASE(buffer);
  }

  // Return a pointer to the sound effect
  return sound_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Create_Sound_Effect
//
////////////////////////////////////////////////////////////////////////////////////////////////
AudibleSoundClass *WWAudioClass::Create_Sound_Effect(const char *filename) {
  WWPROFILE("Create_Sound_Effect");

  // Assume failure
  AudibleSoundClass *sound_obj = nullptr;
  if (Is_Disabled() == false) {

    // Param OK?
    WWASSERT(filename != nullptr);
    if (filename != nullptr) {

      // Create a file object and pass it onto the appropriate function
      FileClass *file = Get_File(filename);
      if (file && file->Is_Available()) {
        sound_obj = Create_Sound_Effect(*file, filename);
      } else {
        WWDEBUG_SAY(("Sound %s not found\r\n", filename));
      }
      Return_File(file);
    }
  }

  // Return a pointer to the sound effect
  return sound_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Create_Sound_Effect
//
////////////////////////////////////////////////////////////////////////////////////////////////
AudibleSoundClass *WWAudioClass::Create_Sound_Effect(const char *string_id, unsigned char *raw_wave_data,
                                                     unsigned long bytes) {
  WWPROFILE("Create_Sound_Effect");

  // Create a new sound object
  AudibleSoundClass *sound_obj = NEW_REF(AudibleSoundClass, ());
  if (Is_Disabled() == false) {

    // Try to find the buffer in our cache, otherwise create a new buffer.
    SoundBufferClass *buffer = Find_Cached_Buffer(string_id);
    if (buffer == nullptr) {
      buffer = Create_Sound_Buffer(raw_wave_data, bytes, string_id, false);
    }

    // Pass the actual sound data onto the sound object
    sound_obj->Set_Buffer(buffer);
    REF_PTR_RELEASE(buffer);
  }

  // Return a pointer to the sound effect
  return sound_obj;
}

/////////////////////////////////////////////////////////////////////////////////
//
//	Create_3D_Sound
//
////////////////////////////////////////////////////////////////////////////////////////////////
Sound3DClass *WWAudioClass::Create_3D_Sound(FileClass &file, const char *string_id, int classid_hint) {
  WWPROFILE("Create_3D_Sound (FileClass)");

  Sound3DClass *sound_obj = nullptr;
  if (Is_Disabled() == false) {

    // Try to find the buffer in our cache, otherwise create a new buffer.
    SoundBufferClass *buffer = Get_Sound_Buffer(file, string_id, true);

    //
    // What type of sound object should we create? A true 3D sound or one of
    // our pseudo-3d sounds?  (volume and panning only)
    //
    if (classid_hint == CLASSID_PSEUDO3D || Validate_3D_Sound_Buffer(buffer) == false) {
      sound_obj = new SoundPseudo3DClass;
      sound_obj->Set_Buffer(buffer);
    } else if (buffer != nullptr) {
      sound_obj = new Sound3DClass;
      sound_obj->Set_Buffer(buffer);
    }

    REF_PTR_RELEASE(buffer);
  }

  // Return a pointer to the sound effect
  return sound_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Create_3D_Sound
//
////////////////////////////////////////////////////////////////////////////////////////////////
Sound3DClass *WWAudioClass::Create_3D_Sound(const char *filename, int classid_hint) {
  WWPROFILE("Create_3D_Sound (filename)");
  WWMEMLOG(MEM_SOUND);

  // Assume failure
  Sound3DClass *sound_obj = nullptr;
  if (Is_Disabled() == false) {

    // Param OK?
    WWASSERT(filename != nullptr);
    if (filename != nullptr) {

      // Try to find the buffer in our cache, otherwise create a new buffer.
      SoundBufferClass *buffer = Get_Sound_Buffer(filename, true);

      //
      // What type of sound object should we create? A true 3D sound or one of
      // our pseudo-3d sounds?  (volume and panning only)
      //
      if (classid_hint == CLASSID_PSEUDO3D || Validate_3D_Sound_Buffer(buffer) == false) {
        sound_obj = new SoundPseudo3DClass;
        sound_obj->Set_Buffer(buffer);
      } else if (buffer != nullptr) {
        sound_obj = new Sound3DClass;
        sound_obj->Set_Buffer(buffer);
      } else {
        static int count = 0;
        if (++count < 10) {
          WWDEBUG_SAY(("Sound File not Found \"%s\"\r\n", filename));
        }
      }

      REF_PTR_RELEASE(buffer);
    }
  }

  // Return a pointer to the sound effect
  return sound_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Create_3D_Sound
//
////////////////////////////////////////////////////////////////////////////////////////////////
Sound3DClass *WWAudioClass::Create_3D_Sound(const char *string_id, unsigned char *raw_wave_data, unsigned long bytes,
                                            int classid_hint) {
  WWPROFILE("Create_3D_Sound (Raw)");

  Sound3DClass *sound_obj = nullptr;
  if (Is_Disabled() == false) {

    //
    // Try to find the buffer in our cache, otherwise create a new buffer.
    //
    SoundBufferClass *buffer = Find_Cached_Buffer(string_id);
    if (buffer == nullptr) {
      buffer = Create_Sound_Buffer(raw_wave_data, bytes, string_id, true);
    }

    //
    // What type of sound object should we create? A true 3D sound or one of
    // our pseudo-3d sounds?  (volume and panning only)
    //
    if (classid_hint == CLASSID_PSEUDO3D || Validate_3D_Sound_Buffer(buffer) == false) {
      sound_obj = new SoundPseudo3DClass;
      sound_obj->Set_Buffer(buffer);
    } else if (buffer != nullptr) {
      sound_obj = new Sound3DClass;
      sound_obj->Set_Buffer(buffer);
    }

    REF_PTR_RELEASE(buffer);
  }

  // Return a pointer to the sound effect
  return sound_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Create_Sound
//
////////////////////////////////////////////////////////////////////////////////////////////////
AudibleSoundClass *WWAudioClass::Create_Sound(int definition_id, RefCountClass *user_obj, uint32 user_data,
                                              int classid_hint) {
  WWPROFILE("Create_Sound");
  AudibleSoundClass *sound = nullptr;

  //
  //	Find the definition
  //
  DefinitionClass *definition = DefinitionMgrClass::Find_Definition(definition_id);
  if (definition != nullptr) {

    //
    //	Make sure this is really a sound definition
    //
    WWASSERT(definition->Get_Class_ID() == CLASSID_SOUND);
    if (definition->Get_Class_ID() == CLASSID_SOUND) {
      AudibleSoundDefinitionClass *sound_def = reinterpret_cast<AudibleSoundDefinitionClass *>(definition);

      //
      //	Create an instance of the sound
      //
      sound = sound_def->Create_Sound(classid_hint);
      if (sound != nullptr) {
        sound->Set_User_Data(user_obj, user_data);
      }
    }
  }

  return sound;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Create_Sound
//
////////////////////////////////////////////////////////////////////////////////////////////////
AudibleSoundClass *WWAudioClass::Create_Sound(const char *def_name, RefCountClass *user_obj, uint32 user_data,
                                              int classid_hint) {
  WWPROFILE("Create_Sound");
  AudibleSoundClass *sound = nullptr;

  //
  //	Find the definition
  //
  DefinitionClass *definition = DefinitionMgrClass::Find_Typed_Definition(def_name, CLASSID_SOUND, true);
  if (definition != nullptr) {

    //
    //	Make sure this is really a sound definition
    //
    WWASSERT(definition->Get_Class_ID() == CLASSID_SOUND);
    if (definition->Get_Class_ID() == CLASSID_SOUND) {
      AudibleSoundDefinitionClass *sound_def = reinterpret_cast<AudibleSoundDefinitionClass *>(definition);

      //
      //	Create an instance of the sound
      //
      sound = sound_def->Create_Sound(classid_hint);
      if (sound != nullptr) {
        sound->Set_User_Data(user_obj, user_data);
      }
    }
  }

  return sound;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Create_Continuous_Sound
//
////////////////////////////////////////////////////////////////////////////////////////////////
AudibleSoundClass *WWAudioClass::Create_Continuous_Sound(int definition_id, RefCountClass *user_obj, uint32 user_data,
                                                         int classid_hint) {
  WWPROFILE("Create_Continuous_Sound");

  //
  //	Create an instance of the sound and play it
  //
  AudibleSoundClass *sound = Create_Sound(definition_id, user_obj, user_data, classid_hint);
  if (sound != nullptr) {

    if (sound->Get_Loop_Count() != INFINITE_LOOPS) {
      WWDEBUG_SAY(("Audio Error:  Creating a continuous sound with a finite loop count!\r\n"));
    }
  }

  return sound;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Create_Instant_Sound
//
////////////////////////////////////////////////////////////////////////////////////////////////
int WWAudioClass::Create_Instant_Sound(int definition_id, const Matrix3D &tm, RefCountClass *user_obj, uint32 user_data,
                                       int classid_hint) {
  WWPROFILE("Create_Instant_Sound");

  int sound_id = 0;

  //
  //	Create an instance of the sound and play it
  //
  AudibleSoundClass *sound = Create_Sound(definition_id, user_obj, user_data, classid_hint);
  if (sound != nullptr) {

    if (sound->Get_Loop_Count() == INFINITE_LOOPS) {
      WWDEBUG_SAY(("Audio Error:  Creating an instant sound %s with an infinite loop count!\r\n",
                   sound->Get_Definition()->Get_Name()));
    }

    sound_id = sound->Get_ID();
    sound->Set_Transform(tm);
    sound->Add_To_Scene();
    sound->Release_Ref();
  }

  return sound_id;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Create_Continuous_Sound
//
////////////////////////////////////////////////////////////////////////////////////////////////
AudibleSoundClass *WWAudioClass::Create_Continuous_Sound(const char *def_name, RefCountClass *user_obj,
                                                         uint32 user_data, int classid_hint) {
  WWPROFILE("Create_Continuous_Sound");

  //
  //	Create an instance of the sound and play it
  //
  AudibleSoundClass *sound = Create_Sound(def_name, user_obj, user_data, classid_hint);
  if (sound != nullptr) {

    if (sound->Get_Loop_Count() != INFINITE_LOOPS) {
      WWDEBUG_SAY(("Audio Error:  Creating a continuous sound with a finite loop count!\r\n"));
    }
  }

  return sound;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Create_Instant_Sound
//
////////////////////////////////////////////////////////////////////////////////////////////////
int WWAudioClass::Create_Instant_Sound(const char *def_name, const Matrix3D &tm, RefCountClass *user_obj,
                                       uint32 user_data, int classid_hint) {
  WWPROFILE("Create_Instant_Sound");
  int sound_id = 0;

  //
  //	Create an instance of the sound and play it
  //
  AudibleSoundClass *sound = Create_Sound(def_name, user_obj, user_data, classid_hint);
  if (sound != nullptr) {

    if (sound->Get_Loop_Count() == INFINITE_LOOPS) {
      WWDEBUG_SAY(("Audio Error:  Creating an instant sound %s with an infinite loop count!\r\n",
                   sound->Get_Definition()->Get_Name()));
    }

    sound_id = sound->Get_ID();
    sound->Set_Transform(tm);
    sound->Add_To_Scene();
    sound->Release_Ref();
  }

  return sound_id;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Flush_Playlist
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Flush_Playlist(SOUND_PAGE page) {
  //
  // Loop through all the entries in this playlist
  //
  for (auto sound_obj : m_Playlist[page]) {
    if (sound_obj != nullptr) {
      sound_obj->Stop();
      sound_obj->Remove_From_Scene();
    }
    // REF_PTR_RELEASE (sound_obj);
  }

  //
  // Now, make sure to free any completed sounds
  //
  Free_Completed_Sounds();

  //
  // Free the list structure
  //
  m_Playlist[page].clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Flush_Playlist
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Flush_Playlist() {
  Flush_Playlist(PAGE_PRIMARY);
  Flush_Playlist(PAGE_SECONDARY);
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Free_Completed_Sounds
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Free_Completed_Sounds() {
  if (!m_CompletedSounds.empty()) {

    //
    // Loop through all the entries in the completed sounds list
    //
    for (auto sound_obj : m_CompletedSounds) {
      WWASSERT(sound_obj != nullptr); // TSS 05/24/99

      //
      // Be careful not to remove the sound from the playlist unless it's really done playing
      //
      if (sound_obj->Get_State() == AudibleSoundClass::STATE_STOPPED) {

        //
        // Remove this sound from the playlist
        //
        bool found = false;
        for (int page = 0; page < PAGE_COUNT && !found; page++) {
          for (int play_index = 0; (static_cast<size_t>(play_index) < m_Playlist[page].size()) && !found;
               play_index++) {
            if (m_Playlist[page][play_index] == sound_obj) {

              //
              // Free our hold on this sound object
              //
              m_Playlist[page].erase(m_Playlist[page].begin() + play_index);
              REF_PTR_RELEASE(sound_obj);
              found = true;
            }
          }
        }
      }
    }

    //
    // Free the list structure
    //
    m_CompletedSounds.clear();

    //
    // Try to give a play-handle back to a sound that was priority-bumped.
    //
    Reprioritize_Playlist();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Get_Playlist_Entry
//
////////////////////////////////////////////////////////////////////////////////////////////////
AudibleSoundClass *WWAudioClass::Get_Playlist_Entry(int index) const {
  AudibleSoundClass *sound_obj = nullptr;

  // Params OK?
  WWASSERT(index >= 0 && static_cast<size_t>(index) < m_Playlist[m_CurrPage].size());
  if ((index >= 0) && (static_cast<size_t>(index) < m_Playlist[m_CurrPage].size())) {
    m_Playlist[m_CurrPage][index]->Add_Ref();
  }

  // Return a pointer to the sound object
  return sound_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Add_To_Playlist
//
////////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Add_To_Playlist(AudibleSoundClass *sound) {
  bool retval = false;

  WWASSERT(sound != nullptr);
  if (sound != nullptr) {

    //
    // Loop through all the entries in the playlist
    //
    bool already_added = false;
    for (size_t index = 0; (index < m_Playlist[m_CurrPage].size()) && (already_added == false); index++) {
      already_added = (sound == m_Playlist[m_CurrPage][index]);
    }

    //
    // Add this sound to our playlist
    //
    if (already_added == false) {
      sound->Add_Ref();
      m_Playlist[m_CurrPage].push_back(sound);
    }
  }

  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Remove_From_Playlist
//
////////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Remove_From_Playlist(AudibleSoundClass *sound_obj) {
  bool retval = false;

  WWASSERT(sound_obj != nullptr);
  if (sound_obj != nullptr) {

    //
    // Loop through all the entries in the playlist
    //
    for (int page = 0; page < PAGE_COUNT && !retval; page++) {
      for (size_t index = 0; (index < m_Playlist[page].size()) && !retval; index++) {

        //
        // Is this the entry we are looking for?
        //
        if (sound_obj == m_Playlist[page][index]) {

          //
          // Add this sound to the 'completed' list
          //
          m_CompletedSounds.push_back(sound_obj);
          retval = true;
        }
      }
    }

    //
    // Notify any callbacks that this sound is ending...
    //
    if (sound_obj->Get_Loop_Count() != INFINITE_LOOPS) {
      for (int index = 0; index < m_EOSCallbackList.Count(); index++) {
        uint32 user_data = 0;
        LPFNEOSCALLBACK callback = m_EOSCallbackList.Get_Callback(index, &user_data);
        if (callback != nullptr) {
          (*callback)(sound_obj, user_data);
        }
      }
    }
  }

  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Is_Sound_In_Playlist
//
////////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Is_Sound_In_Playlist(AudibleSoundClass *sound_obj) {
  // Assume failure
  bool retval = false;

  // Loop through all the entries in the playlist
  for (size_t index = 0; (index < m_Playlist[m_CurrPage].size()) && (retval == false); index++) {
    if (sound_obj == m_Playlist[m_CurrPage][index]) {
      retval = true;
    }
  }

  // Return the true/false result code
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Reprioritize_Playlist
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Reprioritize_Playlist() {
  AudibleSoundClass *sound_to_get_handle = nullptr;
  float hightest_priority = 0;

  //
  // Loop through all the entries in the playlist
  //
  for (auto sound_obj : m_Playlist[m_CurrPage]) {

    //
    // Is this the highest priority without a miles handle?
    //
    if ((sound_obj->Get_Miles_Handle() == nullptr) && (sound_obj->Is_Sound_Culled() == false) &&
        (sound_obj->Get_Priority() > hightest_priority)) {
      //
      // This is now the highest priority sound effect without
      // a play-handle.
      //
      sound_to_get_handle = sound_obj;
      hightest_priority = sound_obj->Get_Priority();
    }
  }

  //
  // Get a new handle for this sound if necessary
  //
  if (sound_to_get_handle != nullptr) {
    sound_to_get_handle->Allocate_Miles_Handle();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	On_Frame_Update
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::On_Frame_Update(unsigned int milliseconds) {
  //
  // Free any sounds we completed last frame
  //
  Free_Completed_Sounds();

  //
  // Calculate the time in ms since the last frame
  //
  unsigned int time_delta = milliseconds;
  if (time_delta == 0) {
    time_delta = WW3D::Get_Frame_Time();
  }

  //
  //	Update the sound scene as necessary
  //
  if (m_CurrPage == PAGE_PRIMARY && m_SoundScene != nullptr) {
    m_SoundScene->On_Frame_Update(milliseconds);
    m_SoundScene->Collect_Logical_Sounds();
  }

  // int dialog_count = 0;

  //
  // Loop through all the entries in the playlist
  //
  for (auto sound_obj : m_Playlist[m_CurrPage]) {

    //
    // Update this sound object
    //
    sound_obj->On_Frame_Update(time_delta);

    //
    //	Is this an important piece of dialog?
    //
    /*if (	sound_obj->Is_Sound_Culled () == false &&
                    sound_obj->Get_Type () == AudibleSoundClass::TYPE_DIALOG &&
                    sound_obj->Get_Priority () > 0.5F)
    {
            dialog_count ++;
    }*/
  }

  //
  //	Fade sound fx and music when there's important dialog playing.
  //
  /*if (dialog_count == 0) {
          Fade_Non_Dialog_In ();
  } else {
          Fade_Non_Dialog_Out ();
  }*/

  //
  //	Update any fading we have going on
  //
  // Update_Fade ();
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Release_2D_Handles
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Release_2D_Handles() {
  MMSLockClass lock;

  // Release our hold on all the samples we've allocated
  for (const auto sample : m_2DSampleHandles) {
    if (sample != nullptr) {
      ::AIL_release_sample_handle(sample);
    }
  }

  m_2DSampleHandles.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Allocate_2D_Handles
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Allocate_2D_Handles() {
  MMSLockClass lock;

  // Start fresh
  Release_2D_Handles();

  if (m_Driver2D != nullptr) {

    // Attempt to allocate our share of 2D sample handles
    for (int index = 0; index < m_Max2DSamples; index++) {
      HSAMPLE sample = ::AIL_allocate_sample_handle(m_Driver2D);
      if (sample != nullptr) {
        ::AIL_set_sample_user_data(sample, INFO_OBJECT_PTR, 0);
        m_2DSampleHandles.push_back(sample);
      }
    }

    // Record our actual number of available 2D sample handles
    m_Max2DSamples = m_2DSampleHandles.size();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Get_2D_Sample
//
////////////////////////////////////////////////////////////////////////////////////////////
HSAMPLE
WWAudioClass::Get_2D_Sample(const AudibleSoundClass &sound_obj) {
  if (Is_OK_To_Give_Handle(sound_obj) == false) {
    return (HSAMPLE)INVALID_MILES_HANDLE;
  }

  MMSLockClass lock;

  float lowest_priority = sound_obj.Get_Priority();
  float lowest_runtime_priority = sound_obj.Get_Runtime_Priority();
  AudibleSoundClass *lowest_pri_sound = nullptr;
  HSAMPLE lowest_pri_sample = nullptr;
  HSAMPLE free_sample = (HSAMPLE)INVALID_MILES_HANDLE;

  // Loop through all the available sample handles and try to find
  // one that isn't being used to play a sound.
  bool found = false;
  for (int index = 0; (static_cast<size_t>(index) < m_2DSampleHandles.size()) && !found; index++) {

    HSAMPLE sample = m_2DSampleHandles[index];
    if (sample != nullptr) {

      // Get a pointer to the object that is currently using this sample
      AudibleSoundClass *obj = (AudibleSoundClass *)::AIL_sample_user_data(sample, INFO_OBJECT_PTR);
      if (obj == nullptr) {

        // Return this sample handle to the caller
        free_sample = sample;
        found = true;
      } else {

        //
        //	Determine if this sound's priority is lesser then the sound we want to play.
        // This is done by comparing both the designer-specified priority and the current
        // runtime priority (which is calculated by distance to the listener).
        //
        float priority = obj->Get_Priority();
        float runtime_priority = obj->Get_Runtime_Priority();
        if ((priority < lowest_priority) ||
            (priority == lowest_priority && runtime_priority <= lowest_runtime_priority)) {
          lowest_priority = priority;
          lowest_pri_sound = obj;
          lowest_pri_sample = sample;
          lowest_runtime_priority = runtime_priority;
        }
      }
    }
  }

  // Steal the sample handle from the lower priority
  // sound and return the handle to the caller.
  if ((found == false) && (lowest_pri_sound != nullptr)) {
    lowest_pri_sound->Free_Miles_Handle();
    free_sample = lowest_pri_sample;
  }

  // Return the free sample handle if we found one
  return free_sample;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Get_3D_Sample
//
////////////////////////////////////////////////////////////////////////////////////////////////
H3DSAMPLE
WWAudioClass::Get_3D_Sample(const Sound3DClass &sound_obj) {
  if (Is_OK_To_Give_Handle(sound_obj) == false) {
    return (H3DSAMPLE)INVALID_MILES_HANDLE;
  }

  MMSLockClass lock;

  float lowest_priority = sound_obj.Get_Priority();
  float lowest_runtime_priority = sound_obj.Get_Runtime_Priority();
  AudibleSoundClass *lowest_pri_sound = nullptr;
  H3DSAMPLE lowest_pri_sample = nullptr;
  H3DSAMPLE free_sample = (H3DSAMPLE)INVALID_MILES_HANDLE;

  // Loop through all the available sample handles and try to find
  // one that isn't being used to play a sound.
  bool found = false;
  for (int index = 0; (static_cast<size_t>(index) < m_3DSampleHandles.size()) && !found; index++) {

    H3DSAMPLE sample = m_3DSampleHandles[index];
    if (sample != nullptr) {

      // Get a pointer to the object that is currently using this sample
      AudibleSoundClass *obj = (AudibleSoundClass *)::AIL_3D_object_user_data(sample, INFO_OBJECT_PTR);
      if (obj == nullptr) {

        // Return this sample handle to the caller
        free_sample = sample;
        found = true;
      } else {

        //
        //	Determine if this sound's priority is lesser then the sound we want to play.
        // This is done by comparing both the designer-specified priority and the current
        // runtime priority (which is calculated by distance to the listener).
        //
        float priority = obj->Get_Priority();
        float runtime_priority = obj->Get_Runtime_Priority();
        if ((priority < lowest_priority) ||
            (priority == lowest_priority && runtime_priority <= lowest_runtime_priority)) {
          lowest_priority = priority;
          lowest_pri_sound = obj;
          lowest_pri_sample = sample;
          lowest_runtime_priority = runtime_priority;
        }
      }
    }
  }

  // Steal the sample handle from the lower priority
  // sound and return the handle to the caller.
  if ((found == false) && (lowest_pri_sound != nullptr)) {
    lowest_pri_sound->Free_Miles_Handle();
    free_sample = lowest_pri_sample;
  }

  // Return the free sample handle if we found one
  return free_sample;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Get_Listener_Handle
//
////////////////////////////////////////////////////////////////////////////////////////////////
H3DPOBJECT
WWAudioClass::Get_Listener_Handle() {
  MMSLockClass lock;
  return ::AIL_3D_open_listener(m_Driver3D);
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Build_3D_Driver_List
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Build_3D_Driver_List() {
  MMSLockClass lock;

  HPROENUM next = HPROENUM_FIRST;
  HPROVIDER provider = 0;
  char *name = nullptr;
  while (::AIL_enumerate_3D_providers(&next, &provider, &name) > 0) {

    // Can we successfully open this provider?
    if (::AIL_open_3D_provider(provider) == M3D_NOERR) {
      std::shared_ptr<DRIVER_INFO_STRUCT> info = std::make_shared<DRIVER_INFO_STRUCT>();
      info->driver = provider;
      info->name = name;
      m_Driver3DList.push_back(info);
      ::AIL_close_3D_provider(provider);
    } else {
      char *error_info = ::AIL_last_error();
      WWDEBUG_SAY(("WWAudio: Unable to open %s: error %s.\r\n", name, error_info));
    }
  }

  //
  // Attempt to select one of the known drivers (in the following order).
  //
  if (!Select_3D_Device(DRIVER3D_PSEUDO) && !Select_3D_Device(DRIVER3D_EAX) &&
      !Select_3D_Device(DRIVER3D_A3D) && !Select_3D_Device(DRIVER3D_D3DSOUND) &&
      !Select_3D_Device(DRIVER3D_DOLBY)) {
    //
    // Couldn't select a known driver, so just use the first possible.
    //
    if (!m_Driver3DList.empty()) {
      Select_3D_Device(0);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Free_3D_Driver_List
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Free_3D_Driver_List() {
  MMSLockClass lock;

  //
  //	Remove all the handles
  //
  Remove_3D_Sound_Handles();
  Release_3D_Handles();

  if (m_Driver3D != 0) {
    ::AIL_close_3D_provider(m_Driver3D);
    m_Driver3D = 0;
  }

  //
  // Clear the list
  //
  m_Driver3DList.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Select_3D_Device
//
////////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Select_3D_Device(const std::string &device_name) {
  bool retval = false;

  //
  // Loop through all the drivers until we've found the one we want
  //
  for (auto const &entry : m_Driver3DList) {
    //	Is this the device we were looking for?
    if (entry->name == device_name) {
      retval = Select_3D_Device(device_name, entry->driver);
      break;
    }
  }

  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Select_3D_Device
//
////////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Select_3D_Device(const std::string &device_name, HPROVIDER provider) {
  bool retval = false;
  if ((provider != 0) && (provider != m_Driver3D)) {

    Close_3D_Device();

    //
    // Select this device and re-allocate all handles
    //
    if (::AIL_open_3D_provider(provider) == M3D_NOERR) {
      m_Driver3D = provider;
      m_SoundScene->Initialize();
      Allocate_3D_Handles();
      AIL_set_3D_speaker_type(provider, AIL_3D_2_SPEAKER);

      //
      //	Adjust the effects level to 1.0 if this is an EAX based driver
      //
      StringClass lower_name = device_name.c_str();
      ::strlwr(lower_name.Peek_Buffer());
      if (::strstr(device_name.c_str(), "eax") != nullptr) {
        m_EffectsLevel = 1.0F;
      } else {
        m_EffectsLevel = 0.0F;
      }

      m_Driver3DName = device_name;
    }

    retval = true;
  }

  // Return true if we successfully selected the device
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Select_3D_Device
//
////////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Select_3D_Device(int index) {
  bool retval = false;

  //
  // Index valid?
  //
  if ((index >= 0) && (static_cast<size_t>(index) < m_Driver3DList.size())) {
    Select_3D_Device(m_Driver3DList[index]->name, m_Driver3DList[index]->driver);
    WWDEBUG_SAY(("WWAudio: Selecting 3D sound device: %s.\r\n", m_Driver3DList[index]->name.c_str()));
    retval = true;
  }

  //
  // Return true if we successfully selected the device
  //
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Select_3D_Device
//
////////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Select_3D_Device(DRIVER_TYPE_3D type) {
  // Return true if we successfully selected the device
  return Select_3D_Device(Find_3D_Device(type));
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Find_3D_Device
//
////////////////////////////////////////////////////////////////////////////////////////////////
int WWAudioClass::Find_3D_Device(DRIVER_TYPE_3D type) const {
  // Determine which substring to search for in the
  // name of the driver.
  const char *sub_string = "RSX";
  switch (type) {
  case DRIVER3D_D3DSOUND:
    sub_string = "DirectSound";
    break;

  case DRIVER3D_EAX:
    sub_string = "EAX";
    break;

  case DRIVER3D_A3D:
    sub_string = "A3D";
    break;

  case DRIVER3D_PSEUDO:
    sub_string = "Fast";
    break;

  case DRIVER3D_DOLBY:
    sub_string = "Dolby";
    break;
  default:
    break;
  }

  // Loop through all the driver entries and free them all
  for (size_t index = 0; index < m_Driver3DList.size(); index++) {
    auto info = m_Driver3DList[index];
    if (info != nullptr) {

      // Is this the driver we were looking for?
      if (::strstr(info->name.c_str(), sub_string) != nullptr) {
        return static_cast<int>(index);
      }
    }
  }

  // Return -1 if not found, otherwise the 0 based index
  return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Allocate_3D_Handles
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Allocate_3D_Handles() {
  MMSLockClass lock;

  // Start fresh
  Release_3D_Handles();

  if (m_Driver3D != 0) {

    // Attempt to allocate our share of 3D sample handles
    for (int index = 0; index < m_Max3DSamples; index++) {
      H3DSAMPLE sample = ::AIL_allocate_3D_sample_handle(m_Driver3D);
      if (sample != nullptr) {
        ::AIL_set_3D_object_user_data(sample, INFO_OBJECT_PTR, 0);
        m_3DSampleHandles.push_back(sample);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Release_3D_Handles
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Release_3D_Handles() {
  MMSLockClass lock;

  //
  // Release our hold on all the samples we've allocated
  //
  for (const auto sample : m_3DSampleHandles) {
    if (sample != nullptr) {
      ::AIL_release_3D_sample_handle(sample);
    }
  }

  m_3DSampleHandles.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Validate_3D_Sound_Buffer
//
////////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Validate_3D_Sound_Buffer(SoundBufferClass *buffer) {
  bool retval = false;

  //
  // 3D sound buffer MUST be uncompressed mono WAV data
  //
  if ((buffer != nullptr) && (buffer->Get_Channels() == 1) && (buffer->Get_Type() == WAVE_FORMAT_PCM) &&
      (buffer->Is_Streaming() == false)) {
    retval = true;
  }

  // Return a true/false result code
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	ReAssign_2D_Handles
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::ReAssign_2D_Handles() {
  // Loop through all the entries in the playlist
  for (auto sound_obj : m_Playlist[m_CurrPage]) {
    // If this is a 2D sound effect, then force it to 'get' a new
    // sound handle.
    if ((sound_obj->Get_Class_ID() == CLASSID_2D) || (sound_obj->Get_Class_ID() == CLASSID_PSEUDO3D) ||
        (sound_obj->Get_Class_ID() == CLASSID_2DTRIGGER)) {
      sound_obj->Free_Miles_Handle();
      sound_obj->Allocate_Miles_Handle();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	ReAssign_3D_Handles
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::ReAssign_3D_Handles() {
  // Loop through all the entries in the playlist
  for (auto sound_obj : m_Playlist[m_CurrPage]) {
    // If this is a 3D sound effect, then force it to 'get' a new
    // sound handle.
    if (sound_obj->Get_Class_ID() == CLASSID_3D) {
      sound_obj->Free_Miles_Handle();
      sound_obj->Allocate_Miles_Handle();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Remove_2D_Sound_Handles
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Remove_2D_Sound_Handles() {
  //
  //	Loop over all the 2D handles
  //
  for (const auto sample : m_2DSampleHandles) {
    if (sample != nullptr) {

      //
      // Get a pointer to the object that is currently using this sample
      //
      AudibleSoundClass *sound_obj = (AudibleSoundClass *)::AIL_sample_user_data(sample, INFO_OBJECT_PTR);
      if (sound_obj != nullptr) {
        sound_obj->Free_Miles_Handle();
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Remove_3D_Sound_Handles
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Remove_3D_Sound_Handles() {
  //
  //	Loop over all the 3D handles
  //
  for (auto const sample : m_3DSampleHandles) {
    if (sample != nullptr) {

      //
      // Get a pointer to the object that is currently using this sample
      //
      AudibleSoundClass *sound_obj = (AudibleSoundClass *)::AIL_3D_object_user_data(sample, INFO_OBJECT_PTR);
      if (sound_obj != nullptr) {
        sound_obj->Free_Miles_Handle();
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Set_Dialog_Volume
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Set_Dialog_Volume(float volume) {
  m_DialogVolume = std::clamp(volume, 0.0F, 1.0F);

  // Update all the currently playing 'Dialog' to
  // reflect this new volume
  for (auto sound_obj : m_Playlist[m_CurrPage]) {
    if (sound_obj->Get_Type() == AudibleSoundClass::TYPE_DIALOG) {
      sound_obj->Update_Volume();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Set_Cinematic_Volume
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Set_Cinematic_Volume(float volume) {
  m_CinematicVolume = std::clamp(volume, 0.0F, 1.0F);

  //
  // Update all the currently playing cinematic-counds to
  // reflect this new volume
  //
  for (auto sound_obj : m_Playlist[m_CurrPage]) {
    if (sound_obj->Get_Type() == AudibleSoundClass::TYPE_CINEMATIC) {
      sound_obj->Update_Volume();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Set_Sound_Effects_Volume
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Set_Sound_Effects_Volume(float volume) {
  m_RealSoundVolume = std::clamp(volume, 0.0F, 1.0F);

  Internal_Set_Sound_Effects_Volume(m_RealSoundVolume);
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Set_Music_Volume
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Set_Music_Volume(float volume) {
  m_RealMusicVolume = std::clamp(volume, 0.0F, 1.0F);

  Internal_Set_Music_Volume(m_RealMusicVolume);
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Internal_Set_Sound_Effects_Volume
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Internal_Set_Sound_Effects_Volume(float volume) {
  m_SoundVolume = std::clamp(volume, 0.0F, 1.0F);

  // Update all the currently playing 'Sound Effects' to
  // reflect this new volume
  for (auto sound_obj : m_Playlist[m_CurrPage]) {
    if (sound_obj->Get_Type() == AudibleSoundClass::TYPE_SOUND_EFFECT) {
      sound_obj->Update_Volume();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Internal_Set_Music_Volume
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Internal_Set_Music_Volume(float volume) {
  m_MusicVolume = std::clamp(volume, 0.0F, 1.0F);

  // Update all currently playing music to
  // reflect this new volume
  for (auto sound_obj : m_Playlist[m_CurrPage]) {
    if (sound_obj->Get_Type() == AudibleSoundClass::TYPE_MUSIC) {
      sound_obj->Update_Volume();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Is_Disabled
//
////////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Is_Disabled() const {
  static bool _firsttime = true;
  static bool _disabled = false;

  if (_firsttime) {
    _firsttime = false;

#ifdef G_CODE_BASE
    //
    // Use command line arguement.
    //
    ArgvClass argv;
    if (argv.Find("-NOAUDIO")) {
      _disabled = true;
    }
#endif

    //
    //	Read the disabled key from the registry
    //
    RegistryClass registry("Software\\CnC_Rebel\\WWAudio");
    if (registry.Is_Valid()) {
      if (registry.Get_Int("Disabled", 0) == 1) {
        _disabled = true;
        WWDEBUG_SAY(("WWAudio: Audio system disabled in registry.\r\n"));
      }
    }
  }

  return (_disabled | m_ForceDisable);
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Initialize
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Initialize(const char *registry_subkey_name) {
  WWMEMLOG(MEM_SOUND);

  if (Is_Disabled() == false) {

    //
    //	Initialize the audio system from the registry settings
    //
    Load_From_Registry(registry_subkey_name);

    //
    //	Grab the first (and only) filter for use with our 'tinny' effect.
    //
    HPROENUM next = HPROENUM_FIRST;
    char *name = nullptr;
    if (::AIL_enumerate_filters(&next, &m_ReverbFilter, &name) == 0) {
      m_ReverbFilter = INVALID_MILES_HANDLE;
    }

    m_RealMusicVolume = m_MusicVolume;
    m_RealSoundVolume = m_SoundVolume;
  }

  //
  //	Register the file callbacks so we can support streaming from MIX files...
  //
  ::AIL_set_file_callbacks(File_Open_Callback, File_Close_Callback, File_Seek_Callback, File_Read_Callback);
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Initialize
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Initialize(bool stereo, int bits, int hertz) {
  // Open the default 2D device, then build a list of 3D
  // devices and open the default.
  if (Is_Disabled() == false) {

    Open_2D_Device(stereo, bits, hertz);
    Build_3D_Driver_List();

    //
    //	Grab the first (and only) filter for use with our 'tinny' effect.
    //
    HPROENUM next = HPROENUM_FIRST;
    char *name = nullptr;
    if (::AIL_enumerate_filters(&next, &m_ReverbFilter, &name) == 0) {
      m_ReverbFilter = INVALID_MILES_HANDLE;
    }
  }

  //
  //	Register the file callbacks so we can support streaming from MIX files...
  //
  ::AIL_set_file_callbacks(File_Open_Callback, File_Close_Callback, File_Seek_Callback, File_Read_Callback);
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Shutdown
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Shutdown() {
  //
  // If there is a timer running, then stop the timer...
  //
  if (m_UpdateTimer != -1) {

    // Kill the timer
    ::AIL_stop_timer(m_UpdateTimer);
    ::AIL_release_timer_handle(m_UpdateTimer);
    m_UpdateTimer = -1;

    // Wait for the timer callback function to end
    ::WaitForSingleObject(_TimerSyncEvent, 20000);
    ::CloseHandle(_TimerSyncEvent);
    _TimerSyncEvent = nullptr;
  }

  //
  //	Stop the background music
  //
  Set_Background_Music(nullptr);

  //
  // Stop all sounds from playing
  //
  Flush_Playlist();
  if (m_SoundScene != nullptr) {
    m_SoundScene->Flush_Scene();
  }

  //
  // Free all our cached sound buffers
  //
  Flush_Cache();

  //
  // Close-out our hold on any driver resources
  //
  Remove_2D_Sound_Handles();
  Remove_3D_Sound_Handles();
  Release_2D_Handles();
  Release_3D_Handles();
  Free_3D_Driver_List();
  SAFE_DELETE(m_SoundScene);
  Close_2D_Device();

  //
  // Shutdown Miles Sound System
  //
  ::AIL_shutdown();
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Register_EOS_Callback
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Register_EOS_Callback(LPFNEOSCALLBACK callback, DWORD user_param) {
  m_EOSCallbackList.Add_Callback(callback, user_param);
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	UnRegister_EOS_Callback
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::UnRegister_EOS_Callback(LPFNEOSCALLBACK callback) { m_EOSCallbackList.Remove_Callback(callback); }

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Register_Text_Callback
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Register_Text_Callback(LPFNTEXTCALLBACK callback, DWORD user_param) {
  m_TextCallbackList.Add_Callback(callback, user_param);
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	UnRegister_Text_Callback
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::UnRegister_Text_Callback(LPFNTEXTCALLBACK callback) { m_TextCallbackList.Remove_Callback(callback); }

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Fire_Text_Callback
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Fire_Text_Callback(AudibleSoundClass *sound_obj, const StringClass &text) {
  if (text.Get_Length() > 0) {

    //
    //	Loop over all the text-callbacks that have been registered
    //
    for (int index = 0; index < m_TextCallbackList.Count(); index++) {
      uint32 user_data = 0L;
      LPFNTEXTCALLBACK callback = m_TextCallbackList.Get_Callback(index, &user_data);
      if (callback != nullptr) {

        //
        //	Fire the notification
        //
        (*callback)(sound_obj, text, user_data);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Allow_Sound_Effects
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Allow_Sound_Effects(bool onoff) {
  //
  // Is the state changing?
  //
  if (m_AreSoundEffectsEnabled != onoff) {
    m_AreSoundEffectsEnabled = onoff;

    //
    // Update all the currently playing 'Sound Effects' to
    // reflect this new state.
    //
    if (m_AreSoundEffectsEnabled) {

      for (int page = 0; page < PAGE_COUNT; page++) {
        Push_Active_Sound_Page((WWAudioClass::SOUND_PAGE)page);
        for (auto sound_obj : m_Playlist[page]) {
          if (sound_obj->Get_Type() == AudibleSoundClass::TYPE_SOUND_EFFECT) {
            sound_obj->Allocate_Miles_Handle();
          }
        }
        Pop_Active_Sound_Page();
      }
    } else {

      for (auto &page : m_Playlist) {
        for (auto sound_obj : page) {
          if (sound_obj->Get_Type() == AudibleSoundClass::TYPE_SOUND_EFFECT) {
            sound_obj->Free_Miles_Handle();
          }
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Allow_Music
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Allow_Music(bool onoff) {
  // Is the state changing?
  if (m_IsMusicEnabled != onoff) {
    m_IsMusicEnabled = onoff;

    //
    // Update all the currently playing 'music tracks' to
    // reflect this new state.
    //
    if (m_IsMusicEnabled) {

      for (int page = 0; page < PAGE_COUNT; page++) {
        Push_Active_Sound_Page((WWAudioClass::SOUND_PAGE)page);
        for (auto sound_obj : m_Playlist[page]) {
          if (sound_obj->Get_Type() == AudibleSoundClass::TYPE_MUSIC) {
            sound_obj->Stop(false);
            sound_obj->Play();
          }
        }
        Pop_Active_Sound_Page();
      }

    } else {

      for (auto &page : m_Playlist) {
        for (auto sound_obj : page) {
          if (sound_obj->Get_Type() == AudibleSoundClass::TYPE_MUSIC) {
            sound_obj->Free_Miles_Handle();
          }
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Allow_Dialog
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Allow_Dialog(bool onoff) {
  // Is the state changing?
  if (m_IsDialogEnabled != onoff) {
    m_IsDialogEnabled = onoff;

    //
    // Update all the currently playing 'dialog' to
    // reflect this new state.
    //
    if (m_IsDialogEnabled) {

      for (int page = 0; page < PAGE_COUNT; page++) {
        Push_Active_Sound_Page((WWAudioClass::SOUND_PAGE)page);
        for (auto sound_obj : m_Playlist[page]) {
          if (sound_obj->Get_Type() == AudibleSoundClass::TYPE_DIALOG) {
            sound_obj->Stop(false);
            sound_obj->Play();
          }
        }
        Pop_Active_Sound_Page();
      }

    } else {

      for (auto &page : m_Playlist) {
        for (auto sound_obj : page) {
          if (sound_obj->Get_Type() == AudibleSoundClass::TYPE_DIALOG) {
            sound_obj->Free_Miles_Handle();
          }
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Allow_Cinematic_Sound
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Allow_Cinematic_Sound(bool onoff) {
  // Is the state changing?
  if (m_IsCinematicSoundEnabled != onoff) {
    m_IsCinematicSoundEnabled = onoff;

    //
    // Update all the currently playing 'dialog' to
    // reflect this new state.
    //
    if (m_IsCinematicSoundEnabled) {

      for (int page = 0; page < PAGE_COUNT; page++) {
        Push_Active_Sound_Page((WWAudioClass::SOUND_PAGE)page);
        for (auto sound_obj : m_Playlist[page]) {
          if (sound_obj->Get_Type() == AudibleSoundClass::TYPE_CINEMATIC) {
            sound_obj->Stop(false);
            sound_obj->Play();
          }
        }
        Pop_Active_Sound_Page();
      }

    } else {

      for (auto &page : m_Playlist) {
        for (auto sound_obj : page) {
          if (sound_obj->Get_Type() == AudibleSoundClass::TYPE_CINEMATIC) {
            sound_obj->Free_Miles_Handle();
          }
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Simple_Play_2D_Sound_Effect
//
////////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Simple_Play_2D_Sound_Effect(const char *filename, float priority, float volume) {
  bool retval = false;
  AudibleSoundClass *sound = Create_Sound_Effect(filename);
  if (sound != nullptr) {
    sound->Set_Priority(priority);
    sound->Set_Loop_Count(1);
    sound->Set_Volume(volume);
    sound->Play();
    sound->Release_Ref();
    sound = nullptr;
    retval = true;
  }

  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Simple_Play_2D_Sound_Effect
//
////////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Simple_Play_2D_Sound_Effect(FileClass &file, float priority, float volume) {
  bool retval = false;
  AudibleSoundClass *sound = Create_Sound_Effect(file);
  if (sound != nullptr) {
    sound->Set_Priority(priority);
    sound->Set_Loop_Count(1);
    sound->Set_Volume(volume);
    sound->Play();
    sound->Release_Ref();
    sound = nullptr;
    retval = true;
  }

  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Get_File
//
////////////////////////////////////////////////////////////////////////////////////////////////
FileClass *WWAudioClass::Get_File(LPCTSTR filename) {
  FileClass *file = nullptr;
  if (m_FileFactory != nullptr) {
    file = m_FileFactory->Get_File(filename);
  } else {
    file = _TheFileFactory->Get_File(filename);
  }

  // Return a pointer to the file
  return file;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Return_File
//
////////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Return_File(FileClass *file) {
  if (m_FileFactory != nullptr) {
    m_FileFactory->Return_File(file);
  } else {
    SAFE_DELETE(file);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Create_Logical_Sound
//
////////////////////////////////////////////////////////////////////////////////////////////
LogicalSoundClass *WWAudioClass::Create_Logical_Sound() { return new LogicalSoundClass; }

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Create_Logical_Listener
//
////////////////////////////////////////////////////////////////////////////////////////////
LogicalListenerClass *WWAudioClass::Create_Logical_Listener() { return new LogicalListenerClass; }

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Add_Logical_Type
//
////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Add_Logical_Type(int id, LPCTSTR display_name) { m_LogicalTypes.emplace_back(id, display_name); }

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Reset_Logical_Types
//
////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Reset_Logical_Types() { m_LogicalTypes.clear(); }

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Get_Logical_Type
//
////////////////////////////////////////////////////////////////////////////////////////////
int WWAudioClass::Get_Logical_Type(size_t index, StringClass &name) {
  int type_id = 0;

  WWASSERT(index < m_LogicalTypes.size());
  if (index < m_LogicalTypes.size()) {
    type_id = m_LogicalTypes[index].id;
    name = m_LogicalTypes[index].display_name;
  }

  return type_id;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Find_Sound_Object
//
////////////////////////////////////////////////////////////////////////////////////////////
SoundSceneObjClass *WWAudioClass::Find_Sound_Object(uint32 sound_obj_id) {
  SoundSceneObjClass *sound_obj = nullptr;

  //
  //	Lookup the sound object and return it to the caller
  //
  int index = 0;
  if (SoundSceneObjClass::Find_Sound_Object(sound_obj_id, &index)) {
    sound_obj = SoundSceneObjClass::m_GlobalSoundList[index];
  }

  return sound_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Load_From_Registry
//
////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Load_From_Registry(const char *subkey_name) {
  bool retval = true;

  std::string device_name;
  bool is_stereo = true;
  int bits = 16;
  int hertz = 44100;

  //
  //	Load the settings from the registry
  //
  if (Load_From_Registry(subkey_name, device_name, is_stereo, bits, hertz, m_AreSoundEffectsEnabled, m_IsMusicEnabled,
                         m_IsDialogEnabled, m_IsCinematicSoundEnabled, m_SoundVolume, m_MusicVolume, m_DialogVolume,
                         m_CinematicVolume, m_SpeakerType)) {
    //
    //	Close any open devices
    //
    Free_3D_Driver_List();
    Close_2D_Device();

    //
    //	Open the 2D device as specified
    //
    Open_2D_Device(is_stereo, bits, hertz);

    //
    //	Find and open the 3D device specified
    //
    Build_3D_Driver_List();
    Select_3D_Device(device_name);
    retval = true;

    //
    //	Select the speaker type
    //
    Set_Speaker_Type(m_SpeakerType);
  }

  m_RealMusicVolume = m_MusicVolume;
  m_RealSoundVolume = m_SoundVolume;
  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Load_From_Registry
//
////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Load_From_Registry(const char *subkey_name, std::string &device_name, bool &is_stereo, int &bits,
                                      int &hertz, bool &sound_enabled, bool &music_enabled, bool &dialog_enabled,
                                      bool &cinematic_enabled, float &sound_volume, float &music_volume,
                                      float &dialog_volume, float &cinematic_volume, int &speaker_type) {
  bool retval = false;

  //
  //	Attempt to open the registry key
  //
  RegistryClass registry(subkey_name);
  if (registry.Is_Valid()) {

    int defaultmusicvolume, defaultsoundvolume, defaultdialogvolume, defaultcinematicvolume;

    //
    //	Read the device name into a string object
    //
    char temp_buffer[256] = {0};
    registry.Get_String(VALUE_NAME_DEVICE_NAME, temp_buffer, sizeof(temp_buffer));
    device_name = temp_buffer;

    //
    //	Read the 2D settings
    //
    is_stereo = (registry.Get_Int(VALUE_NAME_IS_STEREO, true) == 1);
    bits = registry.Get_Int(VALUE_NAME_BITS, 16);
    hertz = registry.Get_Int(VALUE_NAME_HERTZ, 44100);

    //
    //	Read the sound/music enabled settings
    //
    music_enabled = (registry.Get_Int(VALUE_NAME_MUSIC_ENABLED, 1) == 1);
    sound_enabled = (registry.Get_Int(VALUE_NAME_SOUND_ENABLED, 1) == 1);
    dialog_enabled = (registry.Get_Int(VALUE_NAME_DIALOG_ENABLED, 1) == 1);
    cinematic_enabled = (registry.Get_Int(VALUE_NAME_CINEMATIC_ENABLED, 1) == 1);

    Load_Default_Volume(defaultmusicvolume, defaultsoundvolume, defaultdialogvolume, defaultcinematicvolume);

    //
    //	Read the volume information
    //
    music_volume = registry.Get_Int(VALUE_NAME_MUSIC_VOL, defaultmusicvolume) / 100.0F;
    sound_volume = registry.Get_Int(VALUE_NAME_SOUND_VOL, defaultsoundvolume) / 100.0F;
    dialog_volume = registry.Get_Int(VALUE_NAME_DIALOG_VOL, defaultdialogvolume) / 100.0F;
    cinematic_volume = registry.Get_Int(VALUE_NAME_CINEMATIC_VOL, defaultcinematicvolume) / 100.0F;
    music_volume = std::clamp(music_volume, 0.0F, 1.0F);
    sound_volume = std::clamp(sound_volume, 0.0F, 1.0F);
    dialog_volume = std::clamp(dialog_volume, 0.0F, 1.0F);
    cinematic_volume = std::clamp(cinematic_volume, 0.0F, 1.0F);

    //
    //	Misc
    //
    speaker_type = registry.Get_Int(VALUE_NAME_SPEAKER_TYPE, 0);

    retval = true;
  }

  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Save_To_Registry
//
////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Save_To_Registry(const char *subkey_name) {
  std::string device_name;

  //
  // Get the name of the current 3D driver
  //
  for (const auto &info : m_Driver3DList) {
    //
    //	Is this the device we were looking for?
    //
    if (info != nullptr && info->driver == m_Driver3D) {
      device_name = info->name;
      break;
    }
  }

  //
  //	Save these settings to the registry
  //
  return Save_To_Registry(subkey_name, device_name, m_PlaybackStereo, m_PlaybackBits, m_PlaybackRate,
                          m_AreSoundEffectsEnabled, m_IsMusicEnabled, m_IsDialogEnabled, m_IsCinematicSoundEnabled,
                          m_SoundVolume, m_MusicVolume, m_DialogVolume, m_CinematicVolume, m_SpeakerType);
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Save_To_Registry
//
////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Save_To_Registry(const char *subkey_name, const std::string &device_name, bool is_stereo, int bits,
                                    int hertz, bool sound_enabled, bool music_enabled, bool dialog_enabled,
                                    bool cinematic_enabled, float sound_volume, float music_volume, float dialog_volume,
                                    float cinematic_volume, int speaker_type) {
  bool retval = false;

  //
  //	Attempt to open the registry key
  //
  RegistryClass registry(subkey_name);
  if (registry.Is_Valid()) {

    //
    //	Save the settings to the registry
    //
    registry.Set_String(VALUE_NAME_DEVICE_NAME, device_name.c_str());
    registry.Set_Int(VALUE_NAME_IS_STEREO, is_stereo);
    registry.Set_Int(VALUE_NAME_BITS, bits);
    registry.Set_Int(VALUE_NAME_HERTZ, hertz);
    registry.Set_Int(VALUE_NAME_MUSIC_ENABLED, music_enabled);
    registry.Set_Int(VALUE_NAME_SOUND_ENABLED, sound_enabled);
    registry.Set_Int(VALUE_NAME_DIALOG_ENABLED, dialog_enabled);
    registry.Set_Int(VALUE_NAME_CINEMATIC_ENABLED, cinematic_enabled);
    registry.Set_Int(VALUE_NAME_MUSIC_VOL, music_volume * 100);
    registry.Set_Int(VALUE_NAME_SOUND_VOL, sound_volume * 100);
    registry.Set_Int(VALUE_NAME_DIALOG_VOL, dialog_volume * 100);
    registry.Set_Int(VALUE_NAME_CINEMATIC_VOL, cinematic_volume * 100);
    registry.Set_Int(VALUE_NAME_SPEAKER_TYPE, speaker_type);

    retval = true;
  }

  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	File_Open_Callback
//
////////////////////////////////////////////////////////////////////////////////////////////
U32 AILCALLBACK WWAudioClass::File_Open_Callback(char const *filename, U32 *file_handle) {
  U32 retval = false;

  if (Get_Instance() != nullptr) {

    //
    //	Open the file
    //
    FileClass *file = Get_Instance()->Get_File(filename);
    if (file != nullptr && file->Open()) {
      (*file_handle) = (U32)file;
      retval = true;
    }
  }

  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	File_Close_Callback
//
////////////////////////////////////////////////////////////////////////////////////////////
void AILCALLBACK WWAudioClass::File_Close_Callback(U32 file_handle) {
  if (Get_Instance() != nullptr) {

    //
    //	Close the file (if necessary)
    //
    auto *file = reinterpret_cast<FileClass *>(file_handle);
    if (file != nullptr) {
      Get_Instance()->Return_File(file);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	File_Seek_Callback
//
////////////////////////////////////////////////////////////////////////////////////////////
S32 AILCALLBACK WWAudioClass::File_Seek_Callback(U32 file_handle, S32 offset, U32 type) {
  S32 retval = 0;

  //
  //	Convert the handle to a file handle type
  //
  FileClass *file = reinterpret_cast<FileClass *>(file_handle);
  if (file != nullptr) {

    //
    //	Convert the Miles seek type to one of our own
    //
    int seek_type = SEEK_CUR;
    switch (type) {
    case AIL_FILE_SEEK_BEGIN:
      seek_type = SEEK_SET;
      break;

    case AIL_FILE_SEEK_CURRENT:
      seek_type = SEEK_CUR;
      break;

    case AIL_FILE_SEEK_END:
      seek_type = SEEK_END;
      break;
    }

    //
    //	Perform the seek
    //
    retval = file->Seek(offset, seek_type);
  }

  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	File_Read_Callback
//
////////////////////////////////////////////////////////////////////////////////////////////
U32 AILCALLBACK WWAudioClass::File_Read_Callback(U32 file_handle, void *buffer, U32 bytes) {
  U32 retval = 0;

  //
  //	Convert the handle to a file handle type
  //
  FileClass *file = reinterpret_cast<FileClass *>(file_handle);
  if (file != nullptr) {

    //
    //	Read the bytes from the file
    //
    retval = file->Read(buffer, bytes);
  }

  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Fade_Background_Music
//
////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Fade_Background_Music(const char *filename, int fade_out_time, int fade_in_time) {
  //
  //	Fade-out the background music (as necessary)
  //
  if (m_BackgroundMusic != nullptr) {
    m_BackgroundMusic->Fade_Out(fade_out_time);
    REF_PTR_RELEASE(m_BackgroundMusic);
  }

  m_BackgroundMusicName = filename;
  if (filename != nullptr) {

    //
    //	Create the sound
    //
    m_BackgroundMusic = Create_Sound_Effect(filename);
    if (m_BackgroundMusic != nullptr) {

      //
      //	Configure the sound and start playing it
      //
      m_BackgroundMusic->Set_Priority(1.0F);
      m_BackgroundMusic->Set_Runtime_Priority(1.0F);
      m_BackgroundMusic->Set_Loop_Count(INFINITE_LOOPS);
      m_BackgroundMusic->Set_Type(AudibleSoundClass::TYPE_MUSIC);
      m_BackgroundMusic->Cull_Sound(false);
      m_BackgroundMusic->Fade_In(fade_in_time);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Set_Background_Music
//
////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Set_Background_Music(const char *filename) {
  //
  //	Stop the background music
  //
  if (m_BackgroundMusic != nullptr) {
    m_BackgroundMusic->Stop();
    REF_PTR_RELEASE(m_BackgroundMusic);
  }

  m_BackgroundMusicName = filename;
  if (filename != nullptr) {

    //
    //	Create the sound
    //
    m_BackgroundMusic = Create_Sound_Effect(filename);
    if (m_BackgroundMusic != nullptr) {

      //
      //	Configure the sound and start playing it
      //
      m_BackgroundMusic->Set_Priority(1.0F);
      m_BackgroundMusic->Set_Runtime_Priority(1.0F);
      m_BackgroundMusic->Set_Loop_Count(INFINITE_LOOPS);
      m_BackgroundMusic->Set_Type(AudibleSoundClass::TYPE_MUSIC);
      m_BackgroundMusic->Cull_Sound(false);
      m_BackgroundMusic->Play();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Set_Active_Sound_Page
//
////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Set_Active_Sound_Page(SOUND_PAGE page) {
  if (page == m_CurrPage) {
    return;
  }

  //
  //	Pause any sounds that are playing in the old page
  //
  for (const auto &index : m_Playlist[m_CurrPage]) {
    index->Pause();
  }

  //
  //	Resume any sounds that are playing in the new page
  //
  for (auto &index : m_Playlist[page]) {
    index->Resume();
  }

  m_CurrPage = page;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Fade_Non_Dialog_In
//
////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Fade_Non_Dialog_In() {
  if (m_FadeType == FADE_IN || m_FadeType == FADE_NONE) {
    return;
  }

  m_FadeType = FADE_IN;
  m_FadeTimer = m_NonDialogFadeTime;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Fade_Non_Dialog_Out
//
////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Fade_Non_Dialog_Out() {
  if (m_FadeType == FADE_OUT || m_FadeType == FADED_OUT) {
    return;
  }

  m_FadeType = FADE_OUT;
  m_FadeTimer = m_NonDialogFadeTime;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Update_Fade
//
////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Update_Fade() {
  if (m_FadeType == FADE_NONE || m_FadeType == FADED_OUT) {
    return;
  }

  m_FadeTimer -= (WW3D::Get_Frame_Time() / 1000.0F);
  m_FadeTimer = max(m_FadeTimer, 0.0F);

  //
  //	Determine what percent we should ramp up or down to...
  //
  float percent = (m_FadeTimer / m_NonDialogFadeTime);
  percent = std::clamp(percent, 0.0F, 1.0F);

  //
  //	Invert the percent if we're fading out
  //
  if (m_FadeType == FADE_IN) {
    percent = 1.0F - percent;
  }

  //
  //	Determine what the current percent is
  //
  const float FADE_MAX = 0.6F;
  percent = (1.0F - FADE_MAX) + (percent * FADE_MAX);

  //
  //	Re-adjust the music and sound effect volumes
  //
  Internal_Set_Music_Volume(m_RealMusicVolume * percent);
  Internal_Set_Sound_Effects_Volume(m_RealSoundVolume * percent);

  //
  //	If we've done the fade, then return to the "no fade" stage
  //
  if (m_FadeTimer == 0) {
    if (m_FadeType == FADE_OUT) {
      m_FadeType = FADED_OUT;
    } else {
      m_FadeType = FADE_NONE;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Peek_2D_Sample
//
////////////////////////////////////////////////////////////////////////////////////////////
AudibleSoundClass *WWAudioClass::Peek_2D_Sample(size_t index) const {
  if (index > m_2DSampleHandles.size()) {
    return nullptr;
  }

  MMSLockClass lock;
  AudibleSoundClass *retval = nullptr;

  //
  // Try to get the sound object associated with this handle
  //
  HSAMPLE sample = m_2DSampleHandles[index];
  if (sample != nullptr) {
    retval = (AudibleSoundClass *)::AIL_sample_user_data(sample, INFO_OBJECT_PTR);
  }

  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Peek_3D_Sample
//
////////////////////////////////////////////////////////////////////////////////////////////
AudibleSoundClass *WWAudioClass::Peek_3D_Sample(size_t index) const {
  if (index > m_3DSampleHandles.size()) {
    return nullptr;
  }

  MMSLockClass lock;
  AudibleSoundClass *retval = nullptr;

  //
  // Try to get the sound object associated with this handle
  //
  H3DSAMPLE sample = m_3DSampleHandles[index];
  if (sample != nullptr) {
    retval = (AudibleSoundClass *)::AIL_3D_object_user_data(sample, INFO_OBJECT_PTR);
  }

  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Acquire_Virtual_Channel
//
////////////////////////////////////////////////////////////////////////////////////////////
bool WWAudioClass::Acquire_Virtual_Channel(AudibleSoundClass *sound_obj, int channel_index) {
  //
  //	Verify parameters
  //
  channel_index--;
  if (sound_obj == nullptr || channel_index < 0 || channel_index >= MAX_VIRTUAL_CHANNELS) {
    return false;
  }

  //
  //	Is there already a sound playing on this channel?
  //
  bool retval = true;
  if (m_VirtualChannels[channel_index] != nullptr) {
    AudibleSoundClass *curr_sound = m_VirtualChannels[channel_index];

    //
    //	If the new sound has overriding priority, then stop the sound
    // that's currently playing on this channel
    //
    if (sound_obj->Get_Priority() >= curr_sound->Get_Priority()) {
      m_VirtualChannels[channel_index] = nullptr;
      curr_sound->Stop();
      REF_PTR_RELEASE(curr_sound);
    } else {
      retval = false;
    }
  }

  //
  //	Store this sound in the virtual channel
  //
  if (retval) {
    m_VirtualChannels[channel_index] = sound_obj;
    sound_obj->Add_Ref();
  }

  return retval;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Release_Virtual_Channel
//
////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Release_Virtual_Channel(AudibleSoundClass *sound_obj, int channel_index) {
  //
  //	Verify parameters
  //
  channel_index--;
  if (sound_obj == nullptr || channel_index < 0 || channel_index >= MAX_VIRTUAL_CHANNELS) {
    return;
  }

  //
  //	Check to ensure this sound has control of the virtual channel
  //
  if (m_VirtualChannels[channel_index] == sound_obj) {

    //
    //	Free the channel
    //
    m_VirtualChannels[channel_index] = nullptr;
    REF_PTR_RELEASE(sound_obj);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Set_Speaker_Type
//
////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Set_Speaker_Type(int speaker_type) {
  m_SpeakerType = speaker_type;

  //
  //	Pass the new speaker type onto miles
  //
  if (m_Driver3D != 0) {
    ::AIL_set_3D_speaker_type(m_Driver3D, speaker_type);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Get_Speaker_Type
//
////////////////////////////////////////////////////////////////////////////////////////////
int WWAudioClass::Get_Speaker_Type() const { return m_SpeakerType; }

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Push_Active_Sound_Page
//
////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Push_Active_Sound_Page(SOUND_PAGE page) {
  m_PageStack.push_back(m_CurrPage);
  Set_Active_Sound_Page(page);
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Pop_Active_Sound_Page
//
////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Pop_Active_Sound_Page() {
  if (!m_PageStack.empty()) {
    SOUND_PAGE new_page = m_PageStack.back();
    m_PageStack.pop_back();
    Set_Active_Sound_Page(new_page);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Temp_Disable_Audio
//
////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Temp_Disable_Audio(bool onoff) {
  if (onoff) {
    m_CachedIsMusicEnabled = m_IsMusicEnabled;
    m_CachedIsDialogEnabled = m_IsDialogEnabled;
    m_CachedIsCinematicSoundEnabled = m_IsCinematicSoundEnabled;
    m_CachedAreSoundEffectsEnabled = m_AreSoundEffectsEnabled;
    Allow_Sound_Effects(false);
    Allow_Music(false);
    Allow_Dialog(false);
    Allow_Cinematic_Sound(false);
  } else {
    Allow_Sound_Effects(m_CachedAreSoundEffectsEnabled);
    Allow_Music(m_CachedIsMusicEnabled);
    Allow_Dialog(m_CachedIsDialogEnabled);
    Allow_Cinematic_Sound(m_CachedIsCinematicSoundEnabled);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
//	Load_Default_Volume
//
////////////////////////////////////////////////////////////////////////////////////////////
void WWAudioClass::Load_Default_Volume(int &defaultmusicvolume, int &defaultsoundvolume, int &defaultdialogvolume,
                                       int &defaultcinematicvolume) {
  constexpr int minsetting = 0;
  constexpr int maxsetting = 100;

  // IML: If the audio INI has not yet been loaded then do it now.
  if (AudioIni == nullptr) {
    AudioIni = new INIClass;
    if (!AudioIni->Load(WWAUDIO_INI_FILENAME)) {
      AudioIni->Load(WWAUDIO_INI_RELATIVE_PATHNAME);
    }
  }

  defaultmusicvolume =
      std::clamp(AudioIni->Get_Int(INI_DEFAULT_VOLUME_SECTION, INI_MUSIC_VOLUME_ENTRY, 31), minsetting, maxsetting);
  defaultsoundvolume =
      std::clamp(AudioIni->Get_Int(INI_DEFAULT_VOLUME_SECTION, INI_SOUND_VOLUME_ENTRY, 43), minsetting, maxsetting);
  defaultdialogvolume =
      std::clamp(AudioIni->Get_Int(INI_DEFAULT_VOLUME_SECTION, INI_DIALOG_VOLUME_ENTRY, 50), minsetting, maxsetting);
  defaultcinematicvolume = std::clamp(AudioIni->Get_Int(INI_DEFAULT_VOLUME_SECTION, INI_CINEMATIC_VOLUME_ENTRY, 100),
                                      minsetting, maxsetting);
}
