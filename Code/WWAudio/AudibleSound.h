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
 *                     $Archive:: /Commando/Code/WWAudio/AudibleSound.h                       $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 12/13/01 2:24p                                              $*
 *                                                                                             *
 *                    $Revision:: 25                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#pragma warning(push, 3)
#include "mss.h"
#pragma warning(pop)

#include "vector3.h"
#include "matrix3d.h"
#include "refcount.h"
#include "rawfile.h"
#include "soundsceneobj.h"
#include "vector.h"
#include "wwstring.h"
#include "definition.h"

/////////////////////////////////////////////////////////////////////////////////
// Forward declarations
/////////////////////////////////////////////////////////////////////////////////
class SoundBufferClass;
class RenderObjClass;
class LogicalSoundClass;
class AudibleSoundDefinitionClass;
class Sound3DClass;
class SoundPseudo3DClass;
class FilteredSoundClass;
class Listener3DClass;
class SoundHandleClass;

/////////////////////////////////////////////////////////////////////////////////
//
//	Typedefs
//
typedef unsigned long MILES_HANDLE;

typedef enum { INFO_OBJECT_PTR = 0, INFO_MAX } HANDLE_USER_INDEX;

/////////////////////////////////////////////////////////////////////////////////
//
//	Constants
//
/////////////////////////////////////////////////////////////////////////////////
const MILES_HANDLE INVALID_MILES_HANDLE = (MILES_HANDLE)-1;
const int INFINITE_LOOPS = 0;

/////////////////////////////////////////////////////////////////////////////////
//
//	AudibleSoundClass
//
//	Base class defining a common interface to all sound object types.
//
/////////////////////////////////////////////////////////////////////////////////
class AudibleSoundClass : public SoundSceneObjClass {
public:
  //////////////////////////////////////////////////////////////////////
  //	Friend classes
  //////////////////////////////////////////////////////////////////////
  friend class WWAudioClass;

  //////////////////////////////////////////////////////////////////////
  //	Public data types
  //////////////////////////////////////////////////////////////////////
  typedef enum { TYPE_MUSIC = 0, TYPE_SOUND_EFFECT, TYPE_DIALOG, TYPE_CINEMATIC, TYPE_COUNT } SOUND_TYPE;

  typedef enum { STATE_STOPPED = 0, STATE_PLAYING, STATE_PAUSED, STATE_COUNT } SOUND_STATE;

  //////////////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  //////////////////////////////////////////////////////////////////////
  AudibleSoundClass(const AudibleSoundClass &src);
  AudibleSoundClass();
  virtual ~AudibleSoundClass();

  //////////////////////////////////////////////////////////////////////
  //	Public operators
  //////////////////////////////////////////////////////////////////////
  const AudibleSoundClass &operator=(const AudibleSoundClass &src);

  //////////////////////////////////////////////////////////////////////
  //	Identification methods
  //////////////////////////////////////////////////////////////////////
  virtual SOUND_CLASSID Get_Class_ID() const { return CLASSID_2D; }
  virtual SOUND_TYPE Get_Type() const { return m_Type; }
  virtual void Set_Type(SOUND_TYPE type) { m_Type = type; }

  //////////////////////////////////////////////////////////////////////
  //	Conversion methods
  //////////////////////////////////////////////////////////////////////
  virtual AudibleSoundClass *As_AudibleSoundClass() { return this; }

  //////////////////////////////////////////////////////////////////////
  //	Update methods
  //////////////////////////////////////////////////////////////////////
  virtual bool On_Frame_Update(unsigned int milliseconds = 0);

  //////////////////////////////////////////////////////////////////////
  //	State control methods
  //////////////////////////////////////////////////////////////////////
  virtual bool Play(bool alloc_handle = true);
  virtual bool Pause();
  virtual bool Resume();
  virtual bool Stop(bool remove_from_playlist = true);
  virtual void Seek(unsigned long milliseconds);
  virtual SOUND_STATE Get_State() const { return m_State; }

  virtual void Fade_Out(int time_in_ms);
  virtual void Fade_In(int time_in_ms);

  // The timestamp represents when the sound started playing
  virtual unsigned long Get_Timestamp() const { return m_Timestamp; }

  //////////////////////////////////////////////////////////////////////
  //	Virtual channel support
  //////////////////////////////////////////////////////////////////////
  virtual int Get_Virtual_Channel() const { return m_VirtualChannel; }
  virtual void Set_Virtual_Channel(int channel) { m_VirtualChannel = channel; }

  //////////////////////////////////////////////////////////////////////
  //	Informational methods
  //////////////////////////////////////////////////////////////////////
  virtual LPCTSTR Get_Filename() const;
  virtual bool Is_Playing() const { return (Get_State() == STATE_PLAYING); }

  //////////////////////////////////////////////////////////////////////
  //	Pan control
  //////////////////////////////////////////////////////////////////////

  //
  //	Note:  Pan values are normalized values from 0 (hard left) to
  // 1.0F (hard right).  Dead center is 0.5F.
  //
  virtual float Get_Pan();
  virtual void Set_Pan(float pan = 0.5F);

  //////////////////////////////////////////////////////////////////////
  //	Volume control
  //////////////////////////////////////////////////////////////////////
  virtual float Get_Volume();
  virtual void Set_Volume(float volume = 1.0F);
  virtual void Update_Volume() { Set_Volume(m_Volume); }

  //////////////////////////////////////////////////////////////////////
  //	Loop control
  //////////////////////////////////////////////////////////////////////
  virtual int Get_Loop_Count() const { return m_LoopCount; }
  virtual int Get_Loops_Left() const;

  // Note:  Use the INFINITE_LOOPS constant for an infinite number of loops. (i.e. for use w/ music)
  virtual void Set_Loop_Count(int count = 1);

  //////////////////////////////////////////////////////////////////////
  //	Priority control
  //////////////////////////////////////////////////////////////////////
  virtual float Get_Priority() const { return m_Priority; }
  virtual float Peek_Priority() const { return m_Priority; }
  virtual void Set_Priority(float priority = 0.5F);

  virtual float Get_Runtime_Priority() const { return m_RuntimePriority; }
  virtual void Set_Runtime_Priority(float priority) { m_RuntimePriority = priority; }

  //////////////////////////////////////////////////////////////////////
  //	Playback rate control
  //////////////////////////////////////////////////////////////////////
  virtual int Get_Playback_Rate();
  virtual void Set_Playback_Rate(int rate_in_hz);

  virtual float Get_Pitch_Factor() { return m_PitchFactor; }
  virtual void Set_Pitch_Factor(float factor);

  //////////////////////////////////////////////////////////////////////
  //	Buffer position manipulation
  //////////////////////////////////////////////////////////////////////

  //
  //	Note:  The duration is in milliseconds.  The play position
  // can either be set as a normalized value from 0 to 1 or a millisecond
  // offset from the start of the sound.
  //
  virtual unsigned long Get_Duration() const { return m_Length; }
  virtual unsigned long Get_Play_Position() const { return m_CurrentPosition; }
  virtual void Set_Play_Position(float position) { Seek(position * m_Length); }
  virtual void Set_Play_Position(unsigned long milliseconds) { Seek(milliseconds); }

  virtual void Set_Start_Offset(float offset) { m_StartOffset = offset; }
  virtual float Get_Start_Offset() const { return m_StartOffset; }

  //////////////////////////////////////////////////////////////////////
  //	Position/direction methods
  //////////////////////////////////////////////////////////////////////
  virtual void Set_Position(const Vector3 &position);
  virtual Vector3 Get_Position() const { return m_Transform.Get_Translation(); }

  virtual void Set_Listener_Transform(const Matrix3D &tm) { m_ListenerTransform = tm; }
  virtual void Set_Transform(const Matrix3D &transform);
  virtual Matrix3D Get_Transform() const { return m_Transform; }

  //////////////////////////////////////////////////////////////////////
  //	Culling methods
  //////////////////////////////////////////////////////////////////////
  virtual void Cull_Sound(bool culled = true);
  virtual bool Is_Sound_Culled() const { return m_IsCulled; }

  //////////////////////////////////////////////////////////////////////
  //	Scene integration
  //////////////////////////////////////////////////////////////////////
  virtual void Add_To_Scene(bool start_playing = true);
  virtual void Remove_From_Scene();

  //////////////////////////////////////////////////////////////////////
  //	Attenuation settings
  //////////////////////////////////////////////////////////////////////

  //
  //	This is the distance where the sound can not be heard any longer.  (its vol is 0)
  //
  virtual void Set_DropOff_Radius(float radius = 1);
  virtual float Get_DropOff_Radius() const { return m_DropOffRadius; }

  //////////////////////////////////////////////////////////////////////
  //	Update methods
  //////////////////////////////////////////////////////////////////////
  virtual void Set_Dirty(bool dirty = true) { m_bDirty = dirty; }
  virtual bool Is_Dirty() const { return m_bDirty; }

  //////////////////////////////////////////////////////////////////////
  //	Definition managmenent
  //////////////////////////////////////////////////////////////////////
  virtual void Set_Definition(AudibleSoundDefinitionClass *def) { m_Definition = def; }
  virtual AudibleSoundDefinitionClass *Get_Definition() { return m_Definition; }

  //////////////////////////////////////////////////////////////////////
  //	Conversion methods
  //////////////////////////////////////////////////////////////////////
  virtual void Re_Sync(AudibleSoundClass &src);
  virtual void Free_Conversion();
  virtual void Convert_To_Filtered();
  virtual AudibleSoundClass *As_Converted_Format();

  //////////////////////////////////////////////////////////////////////
  //	From PersistClass
  //////////////////////////////////////////////////////////////////////
  const PersistFactoryClass &Get_Factory() const;
  bool Save(ChunkSaveClass &csave);
  bool Load(ChunkLoadClass &cload);

protected:
  //////////////////////////////////////////////////////////////////////
  //	Protected methods
  //////////////////////////////////////////////////////////////////////
  virtual float Determine_Real_Volume() const;
  virtual void Internal_Set_Volume(float volume = 1.0F);
  virtual void Update_Fade();
  bool Verify_Playability();

  //////////////////////////////////////////////////////////////////////
  //	Handle information
  //////////////////////////////////////////////////////////////////////
  virtual SoundHandleClass *Get_Miles_Handle() const { return m_SoundHandle; }
  virtual void Set_Miles_Handle(MILES_HANDLE handle = INVALID_MILES_HANDLE);
  virtual void Free_Miles_Handle();
  virtual void Initialize_Miles_Handle();
  virtual void Allocate_Miles_Handle();

  //////////////////////////////////////////////////////////////////////
  //	Buffer information
  //////////////////////////////////////////////////////////////////////
  virtual SoundBufferClass *Get_Buffer() const;
  virtual SoundBufferClass *Peek_Buffer() const;
  virtual void Set_Buffer(SoundBufferClass *buffer);

  //////////////////////////////////////////////////////////////////////
  //	Loop methods
  //////////////////////////////////////////////////////////////////////
  virtual void Restart_Loop() {}
  virtual void Update_Play_Position();

  //////////////////////////////////////////////////////////////////////
  //	Event handling
  //////////////////////////////////////////////////////////////////////
  virtual void On_Loop_End();

  //////////////////////////////////////////////////////////////////////
  //	Protected constants
  //////////////////////////////////////////////////////////////////////
  typedef enum {
    FADE_NONE = 0,
    FADE_IN,
    FADE_OUT,
  } FADE_TYPE;

  //////////////////////////////////////////////////////////////////////
  //	Protected member data
  //////////////////////////////////////////////////////////////////////
  SoundHandleClass *m_SoundHandle;
  unsigned long m_Timestamp;
  SOUND_STATE m_State;
  SOUND_TYPE m_Type;
  FADE_TYPE m_FadeType;
  int m_FadeTimer;
  int m_FadeTime;
  int m_VirtualChannel;

  // Buffer information
  SoundBufferClass *m_Buffer;

  // Cached settings
  float m_RuntimePriority;
  float m_Priority;
  float m_Volume;
  float m_RealVolume;
  float m_Pan;
  int m_LoopCount;
  int m_LoopsLeft;

  // Offset and length information (in milliseconds)
  unsigned long m_Length;
  unsigned long m_CurrentPosition;
  float m_StartOffset;
  float m_PitchFactor;

  // 3D scene information
  Matrix3D m_ListenerTransform;
  Matrix3D m_Transform;
  Matrix3D m_PrevTransform;
  bool m_IsCulled;
  bool m_bDirty;
  float m_DropOffRadius;

  // Conversion data
  AudibleSoundClass *m_pConvertedFormat;

  // Definition pointer
  AudibleSoundDefinitionClass *m_Definition;

  //	Logical sound information
  LogicalSoundClass *m_LogicalSound;
};

//////////////////////////////////////////////////////////////////////////////////
//
//	AudibleSoundDefinitionClass
//
//////////////////////////////////////////////////////////////////////////////////
class AudibleSoundDefinitionClass : public DefinitionClass {

public:
  /////////////////////////////////////////////////////////////////////
  //	Editable interface requirements
  /////////////////////////////////////////////////////////////////////
  DECLARE_EDITABLE(AudibleSoundDefinitionClass, DefinitionClass);

  //////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  //////////////////////////////////////////////////////////////
  AudibleSoundDefinitionClass();
  virtual ~AudibleSoundDefinitionClass() {}

  // From DefinitionClass
  virtual uint32 Get_Class_ID() const;

  // From PersistClass
  virtual const PersistFactoryClass &Get_Factory() const;
  virtual bool Save(ChunkSaveClass &csave);
  virtual bool Load(ChunkLoadClass &cload);
  virtual PersistClass *Create() const;
  virtual AudibleSoundClass *Create_Sound(int classid_hint) const;

  // Initialization
  virtual void Initialize_From_Sound(AudibleSoundClass *sound);

  // Accessors
  virtual const StringClass &Get_Filename() const { return m_Filename; }
  virtual const StringClass &Get_Display_Text() const { return m_DisplayText; }
  virtual float Get_Max_Vol_Radius() const { return m_MaxVolRadius; }
  virtual float Get_DropOff_Radius() const { return m_DropOffRadius; }
  virtual const Vector3 &Get_Sphere_Color() const { return m_AttenuationSphereColor; }
  virtual float Get_Volume() const { return m_Volume; }
  virtual float Get_Volume_Randomizer() const { return m_VolumeRandomizer; }
  virtual float Get_Start_Offset() const { return m_StartOffset; }
  virtual float Get_Pitch_Factor() const { return m_PitchFactor; }
  virtual float Get_Pitch_Factor_Randomizer() const { return m_PitchFactorRandomizer; }
  virtual int Get_Virtual_Channel() const { return m_VirtualChannel; }

  virtual void Set_Volume(float volume) { m_Volume = volume; }
  virtual void Set_Volume_Randomizer(float value) { m_VolumeRandomizer = value; }
  virtual void Set_Max_Vol_Radius(float radius) { m_MaxVolRadius = radius; }
  virtual void Set_DropOff_Radius(float radius) { m_DropOffRadius = radius; }
  virtual void Set_Start_Offset(float offset) { m_StartOffset = offset; }
  virtual void Set_Pitch_Factor(float factor) { m_PitchFactor = factor; }
  virtual void Set_Pitch_Factor_Randomizer(float value) { m_PitchFactorRandomizer = value; }
  virtual void Set_Virtual_Channel(int channel) { m_VirtualChannel = channel; }

  // Logical sound creation
  virtual LogicalSoundClass *Create_Logical();

protected:
  /////////////////////////////////////////////////////////////////////
  //	Private methods
  /////////////////////////////////////////////////////////////////////
  bool Save_Variables(ChunkSaveClass &csave) const;
  bool Load_Variables(ChunkLoadClass &cload);

  //////////////////////////////////////////////////////////////
  //	Private member data
  //////////////////////////////////////////////////////////////
  float m_Priority;
  float m_Volume;
  float m_VolumeRandomizer;
  float m_Pan;
  int m_LoopCount;
  int m_VirtualChannel;
  float m_DropOffRadius;
  float m_MaxVolRadius;
  bool m_Is3D;
  StringClass m_Filename;
  int m_Type;
  StringClass m_DisplayText;
  float m_StartOffset;
  float m_PitchFactor;
  float m_PitchFactorRandomizer;

  int m_LogicalTypeMask;
  float m_LogicalNotifyDelay;
  float m_LogicalDropOffRadius;
  bool m_CreateLogical;

  // Misc UI info
  Vector3 m_AttenuationSphereColor;
};
