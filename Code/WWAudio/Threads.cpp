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
 *                     $Archive:: /Commando/Code/WWAudio/Threads.cpp $Modtime:: 7/17/99 3:32p $*
 *                                                                                             *
 *                    $Revision:: 9                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include <process.h>

#include "Threads.h"
#include "refcount.h"
#include "Utils.h"
#include "systimer.h"

///////////////////////////////////////////////////////////////////////////////////////////
//	Static member initialization
///////////////////////////////////////////////////////////////////////////////////////////
WWAudioThreadsClass::DELAYED_RELEASE_INFO *WWAudioThreadsClass::m_ReleaseListHead = nullptr;
CriticalSectionClass WWAudioThreadsClass::m_ListMutex;
HANDLE WWAudioThreadsClass::m_hDelayedReleaseThread = (HANDLE)-1;
HANDLE WWAudioThreadsClass::m_hDelayedReleaseEvent = (HANDLE)-1;
CriticalSectionClass WWAudioThreadsClass::m_CriticalSection;
bool WWAudioThreadsClass::m_IsFlushing = false;

///////////////////////////////////////////////////////////////////////////////////////////
//
//	WWAudioThreadsClass
//
///////////////////////////////////////////////////////////////////////////////////////////
WWAudioThreadsClass::WWAudioThreadsClass() = default;

///////////////////////////////////////////////////////////////////////////////////////////
//
//	~WWAudioThreadsClass
//
///////////////////////////////////////////////////////////////////////////////////////////
WWAudioThreadsClass::~WWAudioThreadsClass() = default;

///////////////////////////////////////////////////////////////////////////////////////////
//
//	Create_Delayed_Release_Thread
//
///////////////////////////////////////////////////////////////////////////////////////////
HANDLE WWAudioThreadsClass::Create_Delayed_Release_Thread(LPVOID param) {
  //
  //	If the thread isn't already running, then
  //
  if (m_hDelayedReleaseThread == (HANDLE)-1) {
    m_hDelayedReleaseEvent = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
    m_hDelayedReleaseThread = (HANDLE)::_beginthread(Delayed_Release_Thread_Proc, 0, param);
  }

  return m_hDelayedReleaseThread;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//	End_Delayed_Release_Thread
//
///////////////////////////////////////////////////////////////////////////////////////////
void WWAudioThreadsClass::End_Delayed_Release_Thread(DWORD timeout) {
  //
  //	If the thread is running, then wait for it to finish
  //
  if (m_hDelayedReleaseThread != (HANDLE)-1) {
    ::SetEvent(m_hDelayedReleaseEvent);
    ::WaitForSingleObject(m_hDelayedReleaseThread, timeout);

    m_hDelayedReleaseEvent = (HANDLE)-1;
    m_hDelayedReleaseThread = (HANDLE)-1;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//	Add_Delayed_Release_Object
//
///////////////////////////////////////////////////////////////////////////////////////////
void WWAudioThreadsClass::Add_Delayed_Release_Object(RefCountClass *object, DWORD delay) {
  if (m_IsFlushing) {
    REF_PTR_RELEASE(object);
  } else {

    //
    //	Make sure we have a thread running that will handle
    // the operation for us.
    //
    if (m_hDelayedReleaseThread == (HANDLE)-1) {
      Create_Delayed_Release_Thread();
    }

    //
    //	Wait for the release thread to finish using the
    // list pointer
    //
    {
      CriticalSectionClass::LockClass lock(m_ListMutex);

      //
      //	Create a new delay-information structure and
      //	add it to our list
      //
      DELAYED_RELEASE_INFO *info = new DELAYED_RELEASE_INFO;
      info->object = object;
      info->time = TIMEGETTIME() + delay;
      info->next = m_ReleaseListHead;
      info->prev = nullptr;

      if (info->next != nullptr) {
        info->next->prev = info;
      }

      m_ReleaseListHead = info;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//	Flush_Delayed_Release_Objects
//
///////////////////////////////////////////////////////////////////////////////////////////
void WWAudioThreadsClass::Flush_Delayed_Release_Objects() {
  CriticalSectionClass::LockClass lock(m_ListMutex);
  m_IsFlushing = true;

  //
  //	Loop through all the objects in our delay list, and
  // free them now.
  //
  DELAYED_RELEASE_INFO *info = nullptr;
  DELAYED_RELEASE_INFO *next = nullptr;
  for (info = m_ReleaseListHead; info != nullptr; info = next) {
    next = info->next;

    //
    //	Free the object
    //
    REF_PTR_RELEASE(info->object);
    SAFE_DELETE(info);
  }

  m_ReleaseListHead = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//	Delayed_Release_Thread_Proc
//
///////////////////////////////////////////////////////////////////////////////////////////
void __cdecl WWAudioThreadsClass::Delayed_Release_Thread_Proc(LPVOID /*param*/) {
  const DWORD base_timeout = 2000;
  DWORD timeout = base_timeout + rand() % 1000;

  //
  //	Keep looping forever until we are singalled to quit (or an error occurs)
  //
  while (::WaitForSingleObject(m_hDelayedReleaseEvent, timeout) == WAIT_TIMEOUT) {

    {
      CriticalSectionClass::LockClass lock(m_ListMutex);

      //
      //	Loop through all the objects in our delay list, and
      // free any that have expired.
      //
      DWORD current_time = TIMEGETTIME();
      DELAYED_RELEASE_INFO *curr = nullptr;
      DELAYED_RELEASE_INFO *prev = nullptr;
      DELAYED_RELEASE_INFO *next = nullptr;
      for (curr = m_ReleaseListHead; curr != nullptr; curr = next) {
        next = curr->next;
        prev = curr->prev;

        //
        //	If the time has expired, free the object
        //
        if (current_time >= curr->time) {

          //
          //	Unlink the object
          //
          if (curr == m_ReleaseListHead) {
            m_ReleaseListHead = next;
          }

          if (prev != nullptr) {
            prev->next = next;
          }

          if (next != nullptr) {
            next->prev = prev;
          }

          //
          //	Free the object
          //
          REF_PTR_RELEASE(curr->object);
          SAFE_DELETE(curr);
        }
      }
    }

    //
    //	To avoid 'periodic' releases, randomize our timeout
    //
    timeout = base_timeout + rand() % 1000;
  }

  Flush_Delayed_Release_Objects();
}

/*
///////////////////////////////////////////////////////////////////////////////////////////
//
//	Begin_Modify_List
//
///////////////////////////////////////////////////////////////////////////////////////////
bool
WWAudioThreadsClass::Begin_Modify_List ()
{
        bool retval = false;

        //
        //	Wait for up to one second to modify the list object
        //
        if (m_ListMutex != nullptr) {
                retval = (::WaitForSingleObject (m_ListMutex, 1000) == WAIT_OBJECT_0);
                WWASSERT (retval);
        }

        return retval;
}


///////////////////////////////////////////////////////////////////////////////////////////
//
//	End_Modify_List
//
///////////////////////////////////////////////////////////////////////////////////////////
void
WWAudioThreadsClass::End_Modify_List ()
{
        //
        //	Release this thread's hold on the mutex object.
        //
        if (m_ListMutex != nullptr) {
                ::ReleaseMutex (m_ListMutex);
        }

        return ;
}
*/