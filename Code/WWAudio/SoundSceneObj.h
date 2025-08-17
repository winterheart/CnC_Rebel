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
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WWAudio                                                      *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/WWAudio/SoundSceneObj.h        $*
 *																														     *
 *							  $Modtime:: 11/02/01 11:57a $*
 *                                                                                             *
 *                    $Revision:: 13                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include <mutex>

#include "Refcount.h"
#include "WWAudio.h"
#include "BitType.h"
#include "persist.h"
#include "persistfactory.h"
#include "multilist.h"

/////////////////////////////////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////////////////////////////////
class SoundCullObjClass;
class SoundSceneClass;
class RenderObjClass;
class Vector3;
class Matrix3D;
class LogicalListenerClass;
class LogicalSoundClass;
class Sound3DClass;
class SoundPseudo3DClass;
class FilteredSoundClass;
class Listener3DClass;
class AudibleSoundClass;

/////////////////////////////////////////////////////////////////////////////////
//	Constants
/////////////////////////////////////////////////////////////////////////////////
const uint32 SOUND_OBJ_DEFAULT_ID = 0;
const uint32 SOUND_OBJ_START_ID = 1000000000;

/////////////////////////////////////////////////////////////////////////////////
//
//	SoundSceneObjClass
//
//	Abstract base class to defines an interface for any sound
// object that will be inserted in the culling system.
//
/////////////////////////////////////////////////////////////////////////////////
class SoundSceneObjClass : public MultiListObjectClass, public PersistClass, public RefCountClass {
public:
  //////////////////////////////////////////////////////////////////////
  //	Public friends
  //////////////////////////////////////////////////////////////////////
  friend class SoundSceneClass;
  friend class WWAudioClass;
  friend class HandleMgrClass;

  //////////////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  //////////////////////////////////////////////////////////////////////
  SoundSceneObjClass();
  SoundSceneObjClass(const SoundSceneObjClass &src);
  virtual ~SoundSceneObjClass();

  //////////////////////////////////////////////////////////////////////
  //	Public operators
  //////////////////////////////////////////////////////////////////////
  const SoundSceneObjClass &operator=(const SoundSceneObjClass &src);

  //////////////////////////////////////////////////////////////////////
  //	Public methods
  //////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////
  //	Conversion methods
  //////////////////////////////////////////////////////////////////////
  virtual Sound3DClass *As_Sound3DClass() { return nullptr; }
  virtual SoundPseudo3DClass *As_SoundPseudo3DClass() { return nullptr; }
  virtual FilteredSoundClass *As_FilteredSoundClass() { return nullptr; }
  virtual Listener3DClass *As_Listener3DClass() { return nullptr; }
  virtual AudibleSoundClass *As_AudibleSoundClass() { return nullptr; }

  //////////////////////////////////////////////////////////////////////
  //	Identification methods
  //////////////////////////////////////////////////////////////////////
  virtual uint32 Get_ID() const { return m_ID; }
  virtual void Set_ID(uint32 id);

  //////////////////////////////////////////////////////////////////////
  //	Update methods
  //////////////////////////////////////////////////////////////////////
  virtual bool On_Frame_Update(unsigned int milliseconds = 0);

  //////////////////////////////////////////////////////////////////////
  //	Event handling
  //////////////////////////////////////////////////////////////////////
  virtual void On_Event(AudioCallbackClass::EVENTS event, uint32 param1 = 0, uint32 param2 = 0);
  virtual void Register_Callback(AudioCallbackClass::EVENTS events, AudioCallbackClass *callback);
  virtual void Remove_Callback();

  //////////////////////////////////////////////////////////////////////
  //	Position/direction methods
  //////////////////////////////////////////////////////////////////////
  virtual void Set_Position(const Vector3 &position) = 0;
  virtual Vector3 Get_Position() const = 0;

  virtual void Set_Listener_Transform(const Matrix3D &tm) {};
  virtual void Set_Transform(const Matrix3D &transform) = 0;
  virtual Matrix3D Get_Transform() const = 0;

  //////////////////////////////////////////////////////////////////////
  //	Culling methods
  //////////////////////////////////////////////////////////////////////
  virtual void Cull_Sound(bool culled = true) = 0;
  virtual bool Is_Sound_Culled() const = 0;

  //////////////////////////////////////////////////////////////////////
  //	User data methods
  //////////////////////////////////////////////////////////////////////
  virtual void Set_User_Data(RefCountClass *user_obj = nullptr, uint32 user = 0) {
    REF_PTR_SET(m_UserObj, user_obj);
    m_UserData = user;
  }
  virtual uint32 Get_User_Data() const { return m_UserData; }
  virtual RefCountClass *Peek_User_Obj() const { return m_UserObj; }

  //////////////////////////////////////////////////////////////////////
  //	Attached object methods
  //////////////////////////////////////////////////////////////////////
  virtual void Attach_To_Object(RenderObjClass *render_obj, int bone_index = -1);
  virtual void Attach_To_Object(RenderObjClass *render_obj, const char *bone_name);
  virtual RenderObjClass *Peek_Parent_Object() { return m_AttachedObject; }
  virtual int Get_Parent_Bone() { return m_AttachedBone; }
  virtual void Apply_Auto_Position();

  //////////////////////////////////////////////////////////////////////
  //	Scene integration
  //////////////////////////////////////////////////////////////////////
  virtual void Add_To_Scene(bool start_playing = true) = 0;
  virtual void Remove_From_Scene() = 0;
  virtual bool Is_In_Scene() const { return m_Scene != nullptr; }

  //////////////////////////////////////////////////////////////////////
  //	Attenuation settings
  //////////////////////////////////////////////////////////////////////

  //
  //	This is the distance where the sound can not be heard any longer.  (its vol is 0)
  //
  virtual void Set_DropOff_Radius(float radius = 1) = 0;
  virtual float Get_DropOff_Radius() const = 0;

  //////////////////////////////////////////////////////////////////////
  //	From PersistClass
  //////////////////////////////////////////////////////////////////////
  bool Save(ChunkSaveClass &csave);
  bool Load(ChunkLoadClass &cload);

protected:
  //////////////////////////////////////////////////////////////////////
  //	Handle information
  //////////////////////////////////////////////////////////////////////
  virtual SoundCullObjClass *Peek_Cullable_Wrapper() const { return m_PhysWrapper; }
  virtual void Set_Cullable_Wrapper(SoundCullObjClass *obj) { m_PhysWrapper = obj; }

  //////////////////////////////////////////////////////////////////////
  //	Sound object managment
  //////////////////////////////////////////////////////////////////////
  static void Register_Sound_Object(SoundSceneObjClass *sound_obj);
  static void Unregister_Sound_Object(SoundSceneObjClass *sound_obj);
  static bool Find_Sound_Object(uint32 id_to_find, int *index);

  //////////////////////////////////////////////////////////////////////
  //	Protected member data
  //////////////////////////////////////////////////////////////////////
  SoundSceneClass *m_Scene;
  SoundCullObjClass *m_PhysWrapper;
  AudioCallbackClass *m_pCallback;
  AudioCallbackClass::EVENTS m_RegisteredEvents;
  uint32 m_ID;

  RenderObjClass *m_AttachedObject;
  int m_AttachedBone;
  uint32 m_UserData;
  RefCountClass *m_UserObj;

  static DynamicVectorClass<SoundSceneObjClass *> m_GlobalSoundList;
  static uint32 m_NextAvailableID;
  static std::recursive_mutex m_IDListMutex;
};

//////////////////////////////////////////////////////////////////////////////
//
//	On_Event
//
//////////////////////////////////////////////////////////////////////////////
__inline void SoundSceneObjClass::On_Event(AudioCallbackClass::EVENTS event, uint32 param1, uint32 param2) {
  if ((m_pCallback != nullptr) && (m_RegisteredEvents & event)) {

    switch (event) {
    case AudioCallbackClass::EVENT_SOUND_STARTED:
      m_pCallback->On_Sound_Started(this);
      break;

    case AudioCallbackClass::EVENT_SOUND_ENDED:
      m_pCallback->On_Sound_Ended(this);
      break;

    case AudioCallbackClass::EVENT_LOGICAL_HEARD:
      m_pCallback->On_Logical_Heard((LogicalListenerClass *)param1, (LogicalSoundClass *)param2);
      break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//	Register_Callback
//////////////////////////////////////////////////////////////////////////////
__inline void SoundSceneObjClass::Register_Callback(AudioCallbackClass::EVENTS events, AudioCallbackClass *callback) {
  //
  //	Unregister the old callback
  //
  if (m_pCallback != nullptr) {
    m_pCallback->On_UnRegistered(this);
  }

  m_RegisteredEvents = events;
  m_pCallback = callback;

  //
  //	Register the new callbcak
  //
  if (m_pCallback != nullptr) {
    m_pCallback->On_Registered(this);
  }
}

//////////////////////////////////////////////////////////////////////////////
//	Remove_Callback
//////////////////////////////////////////////////////////////////////////////
__inline void SoundSceneObjClass::Remove_Callback() {
  m_pCallback = nullptr;
  m_RegisteredEvents = AudioCallbackClass::EVENT_NONE;
}
