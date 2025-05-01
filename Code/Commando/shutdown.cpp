/*
 * 	Command & Conquer Renegade(tm)
 * 	Copyright 2025 Electronic Arts Inc.
 * 	Copyright 2025 CnC: Rebel Developers.
 *
 * 	This program is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License as published by
 * 	the Free Software Foundation, either version 3 of the License, or
 * 	(at your option) any later version.
 *
 * 	This program is distributed in the hope that it will be useful,
 * 	but WITHOUT ANY WARRANTY; without even the implied warranty of
 * 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * 	GNU General Public License for more details.
 *
 * 	You should have received a copy of the GNU General Public License
 * 	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/***********************************************************************************************
 ***                            Confidential - Westwood Studios                              ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Commando                                                     *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/Commando/shutdown.cpp                        $*
 *                                                                                             *
 *                      $Author:: Steve_t                                                     $*
 *                                                                                             *
 *                     $Modtime:: 10/16/02 11:11a                                             $*
 *                                                                                             *
 *                    $Revision:: 104                                                         $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "shutdown.h"
#include "wwmath.h"
#include "wwsaveload.h"
#include "ww3d.h"
#include "WWAudio.H"
#include "wwphys.h"
#include "debug.h"
#include "assets.h"
#include "ffactorylist.h"
#include "input.h"
#include "inputconfigmgr.h"
#include "gamemode.h"
#include "miscutil.h"
#include "refcount.h"
#include "cnetwork.h"
#include "_globals.h"
#include "systemsettings.h"
#include "diagnostics.h"
#include "translatedb.h"
#include "pathmgr.h"
#include "renegadedialogmgr.h"
#include "campaign.h"
#include "diaglog.h"
#include "binkmovie.h"
#include "init.h"
#include "serverfps.h"
#include "encyclopediamgr.h"
#include "playermanager.h"
#include "teammanager.h"
#include "bandwidthgraph.h"
#include "skinpackagemgr.h"
#include "modpackagemgr.h"

#include "dx8wrapper.h"
#include "pscene.h"
#include "netutil.h"
#include "registry.h"
#include "specialbuilds.h"
#include <windows.h>
#include <lmcons.h> // UNLEN
extern SimpleFileFactoryClass RenegadeBaseFileFactory;

#define SYSTEM_INFO_LOG_DISABLE "SystemInfoLogDisable"

// These are copy-pasted from WWConfig
// extern const char *KEY_NAME_SETTINGS;
extern const char *VALUE_NAME_DYN_LOD;
extern const char *VALUE_NAME_STATIC_LOD;
extern const char *VALUE_NAME_DYN_SHADOWS;
const char *VALUE_NAME_PRELIT_MODE = "Prelit_Mode";
extern const char *VALUE_NAME_SHADOW_MODE;
extern const char *VALUE_NAME_STATIC_SHADOWS;
extern const char *VALUE_NAME_TEXTURE_RES;
const char *VALUE_NAME_SURFACE_EFFECT = "Surface_Effect_Detail";
extern const char *VALUE_NAME_PARTICLE_DETAIL;
const char *VALUE_NAME_TEXTURE_FILTER_MODE = "Texture_Filter_Mode";

/*
**
*/
void Debug_Refs(void);

/*
**
*/
void Game_Shutdown(void) {
  BINKMovie::Shutdown();

  CampaignManager::Shutdown();

  SystemSettings::Shutdown();
  CombatManager::Shutdown();

  // Analyze_Soldier_Bandwidth();

  cNetwork::Onetime_Shutdown();

  cServerFps::Destroy_Instance();

  cPlayerManager::Onetime_Shutdown();
  cTeamManager::Onetime_Shutdown();
  cGameData::Onetime_Shutdown();
  cBandwidthGraph::Onetime_Shutdown();

  DebugManager::Set_Display_Handler(NULL);

  GameModeManager::Destroy_All();
  EncyclopediaMgrClass::Shutdown();
  RenegadeDialogMgrClass::Shutdown();

  // Free the sound library
  if (WWAudioClass::Get_Instance() != NULL) {
    // WWAudioClass::Get_Instance ()->Shutdown ();
    delete WWAudioClass::Get_Instance();
  }

  // GameSettings::Shutdown();

  SkinPackageMgrClass::Shutdown();
  ModPackageMgrClass::Shutdown();
  TranslateDBClass::Shutdown();

  //
  //	Shutdown the input control system
  //
  InputConfigMgrClass::Shutdown();
  Input::Save_Registry(APPLICATION_SUB_KEY_NAME_CONTROLS);
  Input::Shutdown();

  DiagLogClass::Shutdown();

  //	CommandoAssetManager::Shutdown();
  WW3D::_Invalidate_Textures();
  WWASSERT(WW3DAssetManager::Get_Instance());
  WW3DAssetManager::Delete_This();
  //	if ( WW3DAssetManager::Get_Instance() ) {
  //		delete WW3DAssetManager::Get_Instance();
  //	}

  cDiagnostics::Close();
  // cHelpText::Close();

  PhysicsSceneClass *scene = PhysicsSceneClass::Get_Instance();
  scene->Set_Max_Simultaneous_Shadows(0);

  PathMgrClass::Shutdown();
  WWMath::Shutdown();
  WWSaveLoad::Shutdown();
  WW3D::Shutdown();
  WWPhys::Shutdown();

  //	WW3DAssetManager::Get_Instance()->Free_Assets();
  Debug_Refs();

  DebugManager::Save_Registry_Settings(APPLICATION_SUB_KEY_NAME_DEBUG);

  WSA_CHECK(WSACleanup());

  /*
  ** Remove any old file factories still lying around.
  */
  if (FileFactoryListClass::Get_Instance() != NULL) {
    FileFactoryListClass::Get_Instance()->Remove_FileFactory(&RenegadeBaseFileFactory);
  }
  while (FileFactoryListClass::Get_Instance() != NULL) {
    FileFactoryClass *factory = FileFactoryListClass::Get_Instance()->Remove_FileFactory();
    if (factory != NULL) {
      WWDEBUG_SAY(("Removing pesky old file factory\n"));
      delete factory;
    } else {
      break;
    }
  }

  RegistryClass registry(APPLICATION_SUB_KEY_NAME_DEBUG);
  if (registry.Is_Valid()) {
    registry.Set_Int(VALUE_NAME_APPLICATION_CRASH_VERSION, 0);
  }

  DebugManager::Shutdown();
}

/*
**
*/
void Debug_Refs(void) {
#ifndef NDEBUG
  //	Debug_Say(("Detecting Active Refs...\r\n"));
  RefCountNodeClass *first = RefCountClass::ActiveRefList.First();
  RefCountNodeClass *node = first;
  while (node->Is_Valid()) {
    RefCountClass *obj = node->Get();
    ActiveRefStruct *ref = &(obj->ActiveRefInfo);

    bool display = true;
    int count = 0;
    RefCountNodeClass *search = first;
    while (search->Is_Valid()) {

      if (search == node) { // if this is not the first one
        if (count != 0) {
          display = false;
          break;
        }
      }

      RefCountClass *search_obj = search->Get();
      ActiveRefStruct *search_ref = &(search_obj->ActiveRefInfo);

      if (ref->File && search_ref->File && !strcmp(search_ref->File, ref->File) && (search_ref->Line == ref->Line)) {
        count++;
      } else if ((ref->File == NULL) && (search_ref->File == NULL)) {
        count++;
      }

      search = search->Next();
    }

    if (display) {
      Debug_Say(("%d Active Ref: %s %d %p\n", count, ref->File, ref->Line, obj));

      static int num_printed = 0;
      if (++num_printed > 20) {
        Debug_Say(("And Many More......\n"));
        break;
      }
    }

    node = node->Next();
  }
//	Debug_Say(("Done.\r\n"));
#endif
}