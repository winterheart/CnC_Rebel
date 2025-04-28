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
 *                 Project Name : LevelEdit                                                    *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/WWAudio/AudioSaveLoad.cpp                    $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 9/08/01 10:41a                                              $*
 *                                                                                             *
 *                    $Revision:: 7                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"
#include "audiosaveload.h"
#include "persist.h"
#include "persistfactory.h"
#include "definition.h"
#include "soundchunkids.h"
#include "chunkio.h"
#include "SoundScene.h"
#include "wwmemlog.h"

///////////////////////////////////////////////////////////////////////
// Global singleton instance
///////////////////////////////////////////////////////////////////////
StaticAudioSaveLoadClass _StaticAudioSaveLoadSubsystem;
DynamicAudioSaveLoadClass _DynamicAudioSaveLoadSubsystem;

///////////////////////////////////////////////////////////////////////
//	Constants
///////////////////////////////////////////////////////////////////////
enum { CHUNKID_STATIC_SCENE = 0x10291220, CHUNKID_DYNAMIC_SCENE, CHUNKID_DYNAMIC_VARIABLES };

enum {
  VARID_INCLUDE_FILE = 0x01,
  VARID_CAMERA_TM,
  VARID_BACK_COLOR,
  VARID_LOGICAL_LISTENER_GLOBAL_SCALE,
  VARID_BACKGROUND_MUSIC_NAME
};

///////////////////////////////////////////////////////////////////////
//
//	Chunk_ID
//
///////////////////////////////////////////////////////////////////////
uint32 StaticAudioSaveLoadClass::Chunk_ID() const { return CHUNKID_STATIC_SAVELOAD; }

///////////////////////////////////////////////////////////////////////
//
//	Contains_Data
//
///////////////////////////////////////////////////////////////////////
bool StaticAudioSaveLoadClass::Contains_Data() const { return true; }

///////////////////////////////////////////////////////////////////////
//
//	Save
//
///////////////////////////////////////////////////////////////////////
bool StaticAudioSaveLoadClass::Save(ChunkSaveClass &csave) {
  WWMEMLOG(MEM_SOUND);

  bool retval = true;

  //
  //	Save the static sounds
  //
  SoundSceneClass *scene = WWAudioClass::Get_Instance()->Get_Sound_Scene();
  if (scene != nullptr) {
    csave.Begin_Chunk(CHUNKID_STATIC_SCENE);
    scene->Save_Static(csave);
    csave.End_Chunk();
  }

  return retval;
}

///////////////////////////////////////////////////////////////////////
//
//	Load
//
///////////////////////////////////////////////////////////////////////
bool StaticAudioSaveLoadClass::Load(ChunkLoadClass &cload) {
  WWMEMLOG(MEM_SOUND);

  bool retval = true;
  while (cload.Open_Chunk()) {
    switch (cload.Cur_Chunk_ID()) {

    //
    //	Load the static scene information
    //
    case CHUNKID_STATIC_SCENE: {
      SoundSceneClass *scene = WWAudioClass::Get_Instance()->Get_Sound_Scene();
      if (scene != nullptr) {
        scene->Load_Static(cload);
      }
    } break;
    }

    cload.Close_Chunk();
  }

  return retval;
}

//*******************************************************************//
//*
//*	Start of DynamicAudioSaveLoadClass
//*
//*******************************************************************//

///////////////////////////////////////////////////////////////////////
//
//	Chunk_ID
//
///////////////////////////////////////////////////////////////////////
uint32 DynamicAudioSaveLoadClass::Chunk_ID() const { return CHUNKID_DYNAMIC_SAVELOAD; }

///////////////////////////////////////////////////////////////////////
//
//	Contains_Data
//
///////////////////////////////////////////////////////////////////////
bool DynamicAudioSaveLoadClass::Contains_Data() const { return true; }

///////////////////////////////////////////////////////////////////////
//
//	Save
//
///////////////////////////////////////////////////////////////////////
bool DynamicAudioSaveLoadClass::Save(ChunkSaveClass &csave) {
  bool retval = true;

  //
  //	Save the static sounds
  //
  SoundSceneClass *scene = WWAudioClass::Get_Instance()->Get_Sound_Scene();
  if (scene != nullptr) {

    csave.Begin_Chunk(CHUNKID_DYNAMIC_VARIABLES);
    float global_scale = LogicalListenerClass::Get_Global_Scale();
    StringClass filename = WWAudioClass::Get_Instance()->Get_Background_Music_Name();

    WRITE_MICRO_CHUNK(csave, VARID_LOGICAL_LISTENER_GLOBAL_SCALE, global_scale);
    WRITE_MICRO_CHUNK_WWSTRING(csave, VARID_BACKGROUND_MUSIC_NAME, filename);
    csave.End_Chunk();

    csave.Begin_Chunk(CHUNKID_DYNAMIC_SCENE);
    scene->Save_Dynamic(csave);
    csave.End_Chunk();
  }

  return retval;
}

///////////////////////////////////////////////////////////////////////
//
//	Load
//
///////////////////////////////////////////////////////////////////////
bool DynamicAudioSaveLoadClass::Load(ChunkLoadClass &cload) {
  bool retval = true;
  while (cload.Open_Chunk()) {
    switch (cload.Cur_Chunk_ID()) {

    case CHUNKID_DYNAMIC_VARIABLES: {
      //
      //	Read all the variables from their micro-chunks
      //
      while (cload.Open_Micro_Chunk()) {
        switch (cload.Cur_Micro_Chunk_ID()) {

        //
        //	Load the global scale for logical listeners
        //
        case VARID_LOGICAL_LISTENER_GLOBAL_SCALE: {
          float global_scale = 1.0F;
          LOAD_MICRO_CHUNK(cload, global_scale);
          LogicalListenerClass::Set_Global_Scale(global_scale);
          break;
        }

        //
        //	Load the background music name
        //
        case VARID_BACKGROUND_MUSIC_NAME: {
          StringClass filename;
          LOAD_MICRO_CHUNK_WWSTRING(cload, filename);
          WWAudioClass::Get_Instance()->Set_Background_Music(filename);
          break;
        }
        }

        cload.Close_Micro_Chunk();
      }
    } break;

    //
    //	Load the static scene information
    //
    case CHUNKID_DYNAMIC_SCENE: {
      SoundSceneClass *scene = WWAudioClass::Get_Instance()->Get_Sound_Scene();
      if (scene != nullptr) {
        scene->Load_Dynamic(cload);
      }
    } break;
    }

    cload.Close_Chunk();
  }

  return retval;
}