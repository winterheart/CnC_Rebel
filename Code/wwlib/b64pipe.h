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
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                     $Archive:: /G/wwlib/b64pipe.h                                          $*
 *                                                                                             *
 *                      $Author:: Eric_c                                                      $*
 *                                                                                             *
 *                     $Modtime:: 4/02/99 11:58a                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef B64PIPE_H
#define B64PIPE_H

#include "pipe.h"

/*
**	This class performs Base64 encoding/decoding to the data that is piped through. Note that
**	encoded data will grow in size by about 30%. The reverse occurs when decoding.
*/
class Base64Pipe : public Pipe {
public:
  typedef enum CodeControl { ENCODE, DECODE } CodeControl;

  Base64Pipe(CodeControl control) : Control(control), Counter(0) {}

  virtual int Flush(void);
  virtual int Put(void const *source, int slen);

private:
  /*
  **	Indicates if this is for encoding or decoding of Base64 data.
  */
  CodeControl Control;

  /*
  **	The counter of the number of accumulated bytes pending for processing.
  */
  int Counter;

  /*
  **	Buffer that holds the Base64 coded bytes. This will be the staging buffer if
  **	this is for a decoding process. Otherwise, it will be used as a scratch buffer.
  */
  char CBuffer[4];

  /*
  **	Buffer that holds the plain bytes. This will be the staging buffer if this
  **	is for an encoding process. Otherwise, it will be used as a scratch buffer.
  */
  char PBuffer[3];

  /*
  **	Explicitly disable the copy constructor and the assignment operator.
  */
  Base64Pipe(Base64Pipe &rvalue);
  Base64Pipe &operator=(Base64Pipe const &pipe);
};

#endif
