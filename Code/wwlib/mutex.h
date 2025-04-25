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

#ifndef MUTEX_H
#define MUTEX_H

#if defined(_MSC_VER)
#pragma once
#endif

#include <cassert>
#include "always.h"
#include "thread.h"

// Always use mutex or critical section when accessing the same data from multiple threads!

// ----------------------------------------------------------------------------
//
// Mutex class is an expensive way of synchronization! Use critical sections
// (below) for all synchronization. Use mutexes for inter-process locking.
//
// ----------------------------------------------------------------------------

class MutexClass {
  void *handle;
  unsigned locked;

  // Lock and unlock are private so that you can't use them directly. Use LockClass as a sentry instead!
  // Lock returns true if lock was succesful, false otherwise
  bool Lock(int time);
  void Unlock();

public:
  // Name can (and usually should) be NULL. Use name only if you wish to create a globally unique mutex
  MutexClass(const char *name = NULL);
  ~MutexClass();

  enum { WAIT_INFINITE = -1 };

  class LockClass {
    MutexClass &mutex;
    bool failed;

  public:
    // In order to lock a mutex create a local instance of LockClass with mutex as a parameter.
    // Time is in milliseconds, INFINITE means infinite wait.
    LockClass(MutexClass &m, int time = MutexClass::WAIT_INFINITE);
    ~LockClass();

    // Returns true if the lock failed
    bool Failed() { return failed; }

  private:
    LockClass &operator=(const LockClass &) { return (*this); }
  };
  friend class LockClass;
};

// ----------------------------------------------------------------------------
//
// Critical sections are faster than mutex classes and they should be used
// for all synchronization.
//
// ----------------------------------------------------------------------------

class CriticalSectionClass {
  void *handle;
  unsigned locked;

  // Lock and unlock are private so that you can't use them directly. Use LockClass as a sentry instead!
  void Lock();
  void Unlock();

public:
  // Name can (and usually should) be NULL. Use name only if you wish to create a globally unique mutex
  CriticalSectionClass();
  ~CriticalSectionClass();

  class LockClass {
    CriticalSectionClass &CriticalSection;

  public:
    // In order to lock a mutex create a local instance of LockClass with mutex as a parameter.
    LockClass(CriticalSectionClass &c);
    ~LockClass();

  private:
    LockClass &operator=(const LockClass &) { return (*this); }
  };
  friend class LockClass;
};

// ----------------------------------------------------------------------------
//
// Fast critical section is really fast version of CriticalSection. The downside
// of it is that it can't be locked multiple times from the same thread.
//
// ----------------------------------------------------------------------------

class FastCriticalSectionClass {
  volatile unsigned Flag;

  void Thread_Safe_Set_Flag() {
    volatile unsigned &nFlag = Flag;

#define ts_lock _emit 0xF0
    assert(((unsigned)&nFlag % 4) == 0);

// clang-format off
    __asm mov ebx, [nFlag]
    __asm ts_lock
    __asm bts dword ptr[ebx], 0
    __asm jc The_Bit_Was_Previously_Set_So_Try_Again
// clang-format on
    return;

  The_Bit_Was_Previously_Set_So_Try_Again:
    ThreadClass::Switch_Thread();
// clang-format off
    __asm mov ebx, [nFlag]
    __asm ts_lock
    __asm bts dword ptr[ebx], 0
    __asm jc The_Bit_Was_Previously_Set_So_Try_Again
// clang-format on
  }

  WWINLINE void Thread_Safe_Clear_Flag() { Flag = 0; }

public:
  // Name can (and usually should) be NULL. Use name only if you wish to create a globally unique mutex
  FastCriticalSectionClass() : Flag(0) {}

  class LockClass {
    FastCriticalSectionClass &CriticalSection;

  public:
    LockClass(FastCriticalSectionClass &critical_section) : CriticalSection(critical_section) {
      CriticalSection.Thread_Safe_Set_Flag();
    }

    ~LockClass() { CriticalSection.Thread_Safe_Clear_Flag(); }

  private:
    LockClass &operator=(const LockClass &) { return (*this); }
  };

  friend class LockClass;
};

#endif
