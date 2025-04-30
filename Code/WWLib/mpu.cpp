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
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwlib/mpu.cpp                                $*
 *                                                                                             *
 *                      $Author:: Denzil_l                                                    $*
 *                                                                                             *
 *                     $Modtime:: 8/23/01 5:07p                                               $*
 *                                                                                             *
 *                    $Revision:: 4                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   Get_CPU_Rate -- Fetch the rate of CPU ticks per second.                                   *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include <cassert>
#include <cmath>

#include "always.h"
#include "win.h"
#include "mpu.h"

typedef union {
  LARGE_INTEGER LargeInt;
  struct QuadPart {
    unsigned long LowPart;
    unsigned long HighPart;
  } QuadPart;
} QuadValue;

/***********************************************************************************************
 * Get_CPU_Rate -- Fetch the rate of CPU ticks per second.                                     *
 *                                                                                             *
 *    This routine will query the CPU to determine how many clock per second it is.            *
 *                                                                                             *
 * INPUT:   high  -- Reference to the location that will be filled with the upper 32 bits      *
 *                   of the result.                                                            *
 *                                                                                             *
 * OUTPUT:  Returns with the lower 32 bits of the result.                                      *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/20/1997 JLB : Created.                                                                 *
 *=============================================================================================*/
unsigned long Get_CPU_Rate(unsigned long &high) {
  union {
    LARGE_INTEGER LargeInt;
    struct {
      unsigned long LowPart;
      unsigned long HighPart;
    } QuadPart;
  } value;

  if (QueryPerformanceFrequency(&value.LargeInt)) {
    high = value.QuadPart.HighPart;
    return (value.QuadPart.LowPart);
  }
  high = 0;
  return (0);
}

unsigned long Get_CPU_Clock(unsigned long &high) {
  int h;
  int l;
  __asm {
		_emit 0Fh
		_emit 31h
		mov	[h],edx
		mov	[l],eax
  }
  high = h;
  return (l);
}

/*
**
** Cut and paste job from an intel example.
**
**
**
**
**
**
*/

#define ASM_RDTSC _asm _emit 0x0f _asm _emit 0x31

// Max # of samplings to allow before giving up and returning current average.
#define MAX_TRIES 20
#define ROUND_THRESHOLD 6

// # of MHz to allow samplings to deviate from average of samplings.
#define TOLERANCE 1

static unsigned long TSC_Low;
static unsigned long TSC_High;

void RDTSC() {
  _asm
  {
        ASM_RDTSC;
        mov     TSC_Low, eax
        mov     TSC_High, edx
  }
}

int Get_RDTSC_CPU_Speed() {
  LARGE_INTEGER t0, t1;
  int freq = 0;                 // Most current freq. calc.
  int freq2 = 0;                // 2nd most current freq. calc.
  int freq3 = 0;                // 3rd most current freq. calc.
  int total;                    // Sum of previous three freq. calc.
  int tries = 0;                // Number of times a calculation has been
                                // made on this call
  int total_cycles = 0, cycles; // Clock cycles elapsed during test
  int stamp0, stamp1;           // Time Stamp for beginning and end of test
  int total_ticks = 0, ticks;   // Microseconds elapsed during test
  LARGE_INTEGER count_freq;     // Hi-Res Performance Counter frequency

  if (!QueryPerformanceFrequency(&count_freq))
    return (0);

  HANDLE process = GetCurrentProcess();
  DWORD processPri = GetPriorityClass(process);
  SetPriorityClass(process, REALTIME_PRIORITY_CLASS);

  HANDLE thread = GetCurrentThread();
  int threadPri = GetThreadPriority(thread);
  SetThreadPriority(thread, THREAD_PRIORITY_TIME_CRITICAL);

  /*
  ** On processors supporting the TSC opcode, compare elapsed time on the
  ** High-Resolution Counter with elapsed cycles on the Time Stamp Counter.
  */

  do {
    /*
    ** This do loop runs up to 20 times or until the average of the previous
    ** three calculated frequencies is within 1 MHz of each of the individual
    ** calculated frequencies.   This resampling increases the accuracy of the
    ** results since outside factors could affect this calculation.
    */

    tries++; // Increment number of times sampled
             //   on this call to cpuspeed

    freq3 = freq2; // Shift frequencies back to make
    freq2 = freq;  //   room for new frequency measurement

    /*
    ** Get high-resolution performance counter time
    */
    QueryPerformanceCounter(&t0);

    t1.LowPart = t0.LowPart; // Set Initial time
    t1.HighPart = t0.HighPart;

    /*
    ** Loop until 50 ticks have passed since last read of hi-res counter.
    ** This accounts for overhead later.
    */
    while ((DWORD)t1.LowPart - (DWORD)t0.LowPart < 50) {
      QueryPerformanceCounter(&t1);
    }

    ASM_RDTSC;
    _asm mov stamp0, EAX

                         t0.LowPart = t1.LowPart; // Reset Initial Time
    t0.HighPart = t1.HighPart;

    /*
    ** Loop until 1000 ticks have passed since last read of hi-res counter.
    ** This allows for elapsed time for sampling.
    */
    while ((DWORD)t1.LowPart - (DWORD)t0.LowPart < 1000) {
      QueryPerformanceCounter(&t1);
    }

    ASM_RDTSC;
    _asm mov stamp1, EAX

                         cycles = stamp1 - stamp0; // # of cycles passed between reads

    double bigticks = (double)((DWORD)t1.LowPart - (DWORD)t0.LowPart);
    assert((bigticks * 100000.0) > bigticks);
    bigticks = bigticks * 100000.0; // Convert ticks to hundred
                                    //   thousandths of a tick
    ticks = (DWORD)(bigticks / (double)(count_freq.LowPart / 10));
    // Hundred Thousandths of a
    //   Ticks / ( 10 ticks/second )
    //   = microseconds (us)
    total_ticks += ticks;
    total_cycles += cycles;
    if ((ticks % count_freq.LowPart) > (count_freq.LowPart / 2))
      ticks++; // Round up if necessary

    freq = cycles / ticks; // MHz = cycles / us

    if (cycles % ticks > ticks / 2)
      freq++; // Round up if necessary

    total = (freq + freq2 + freq3); // Total last three frequency calcs

  } while ((tries < 3) ||
           (tries < 20) && ((abs(3 * freq - total) > 3 * TOLERANCE) || (abs(3 * freq2 - total) > 3 * TOLERANCE) ||
                            (abs(3 * freq3 - total) > 3 * TOLERANCE)));

  SetThreadPriority(thread, threadPri);
  SetPriorityClass(process, processPri);

  /*
  ** Try one more significant digit.
  */
  freq3 = (total_cycles * 10) / total_ticks;
  freq2 = (total_cycles * 100) / total_ticks;

  if (freq2 - (freq3 * 10) >= ROUND_THRESHOLD)
    freq3++;

  int norm_freq = total_cycles / total_ticks;

  freq = norm_freq * 10;
  if ((freq3 - freq) >= ROUND_THRESHOLD)
    norm_freq++;

  return (norm_freq);
}
