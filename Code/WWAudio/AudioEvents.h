/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
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
 *                     $Archive:: /Commando/Code/WWAudio/AudioEvents.h                        $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 11/02/01 11:56a                                             $*
 *                                                                                             *
 *                    $Revision:: 4                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __AUDIO_EVENTS_H
#define __AUDIO_EVENTS_H

#include "simplevec.h"
#include "bittype.h"
#include "vector.h"


/////////////////////////////////////////////////////////////////////////////////
//	Forward declarations
/////////////////////////////////////////////////////////////////////////////////
class SoundSceneObjClass;
class LogicalListenerClass;
class LogicalSoundClass;
class AudibleSoundClass;
class StringClass;


/////////////////////////////////////////////////////////////////////////////////
//
//	Global callbacks (C Style)
//
/////////////////////////////////////////////////////////////////////////////////

//
// Callback declarations.  These functions are called when a registered event occurs
// in the sound library/
//
typedef void (_stdcall  *LPFNSOSCALLBACK)		(SoundSceneObjClass *sound_obj, uint32 user_param);
typedef void (_stdcall  *LPFNEOSCALLBACK)		(SoundSceneObjClass *sound_obj, uint32 user_param);
typedef void (_stdcall  *LPFNHEARDCALLBACK)	(LogicalListenerClass *listener, LogicalSoundClass *sound_obj, uint32 user_param);
typedef void (_stdcall  *LPFNTEXTCALLBACK)	(AudibleSoundClass *sound_obj, const StringClass &text, uint32 user_param);


/////////////////////////////////////////////////////////////////////////////////
//
//	Object callbacks (C++ Style)
//
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//
//	AudioCallbackClass
//
//	To use this callback mechanism, simply derive from this class and override
// the methods you want notifications of.  These methods will be called when
// the event occurs.
//
/////////////////////////////////////////////////////////////////////////////////
class AudioCallbackClass
{

public:

	/////////////////////////////////////////////////////////////////////////////////
	//	Event identifiers
	/////////////////////////////////////////////////////////////////////////////////
	typedef enum
	{
		EVENT_NONE					= 0x0000,
		EVENT_SOUND_STARTED		= 0x0001,
		EVENT_SOUND_ENDED			= 0x0002,
		EVENT_LOGICAL_HEARD		= 0x0004
	} EVENTS;

	/////////////////////////////////////////////////////////////////////////////////
	//	Public constructors/destructors
	/////////////////////////////////////////////////////////////////////////////////
	AudioCallbackClass (void);
	virtual ~AudioCallbackClass (void);

	/////////////////////////////////////////////////////////////////////////////////
	//	Overrideables (callback-methods)
	/////////////////////////////////////////////////////////////////////////////////
	virtual void	On_Sound_Started (SoundSceneObjClass *sound_obj)	{ }
	virtual void	On_Sound_Ended (SoundSceneObjClass *sound_obj)		{ }
	virtual void	On_Logical_Heard (LogicalListenerClass *listener, LogicalSoundClass *sound_obj)	{ }

	/////////////////////////////////////////////////////////////////////////////////
	//	Housekeeping
	/////////////////////////////////////////////////////////////////////////////////
	void				On_Registered (SoundSceneObjClass *sound);
	void				On_UnRegistered (SoundSceneObjClass *sound);
	void				Remove_All_Callbacks (void);

	/////////////////////////////////////////////////////////////////////////////////
	//	Private member data
	/////////////////////////////////////////////////////////////////////////////////
	DynamicVectorClass<SoundSceneObjClass *>	SoundList;
};


/////////////////////////////////////////////////////////////////////////////////
//
//	Internal implementation
//
/////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
//
//	AudioCallbackListClass
//
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//	Protected structures
/////////////////////////////////////////////////////////////////////////////////
template <class T>
struct AUDIO_CALLBACK_STRUCT
{
	T					callback_ptr;
	uint32			user_data;		

	AUDIO_CALLBACK_STRUCT (void)
		:	callback_ptr (NULL), user_data (0)	{}
	
	AUDIO_CALLBACK_STRUCT (T _ptr, uint32 _data)
		:	callback_ptr (_ptr), user_data (_data) {}

};


/////////////////////////////////////////////////////////////////////////////////
//	Protected structures
/////////////////////////////////////////////////////////////////////////////////
template <class T>
class AudioCallbackListClass : public SimpleDynVecClass< AUDIO_CALLBACK_STRUCT<T> >
{
public:

	/////////////////////////////////////////////////////////////////////////////////
	//	Public constructors/destructors
	/////////////////////////////////////////////////////////////////////////////////
	AudioCallbackListClass (void)					{ }
	virtual ~AudioCallbackListClass (void)		{ }

	/////////////////////////////////////////////////////////////////////////////////
	//	Public methods
	/////////////////////////////////////////////////////////////////////////////////
	void			Add_Callback (T pointer, uint32 user_data);
	T				Get_Callback (int index, uint32 *user_data);
	void			Remove_Callback (T pointer);
};


/////////////////////////////////////////////////////////////////////////////////
//	Add_Callback
/////////////////////////////////////////////////////////////////////////////////
template <class T> void
AudioCallbackListClass<T>::Add_Callback (T pointer, uint32 user_data)
{
	this->Add ( AUDIO_CALLBACK_STRUCT<T> (pointer, user_data));
}


/////////////////////////////////////////////////////////////////////////////////
//	Get_Callback
/////////////////////////////////////////////////////////////////////////////////
template <class T> T
AudioCallbackListClass<T>::Get_Callback (int index, uint32 *user_data)
{
	if (user_data != NULL) {
		(*user_data) = this->Vector[index].user_data;
	}

	return this->Vector[index].callback_ptr;
}

/////////////////////////////////////////////////////////////////////////////////
//	Remove_Callback
/////////////////////////////////////////////////////////////////////////////////
template <class T> void
AudioCallbackListClass<T>::Remove_Callback (T pointer)
{
	for (int index = 0; index < this->ActiveCount; index ++) {
		if (this->Vector[index].callback_ptr == pointer) {
			this->Delete (index);
			break;
		}
	}

}


#endif //__AUDIO_EVENTS_H

