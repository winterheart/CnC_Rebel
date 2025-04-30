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
 *                     $Archive:: /Commando/Code/wwlib/ramfile.h                              $*
 *                                                                                             *
 *                      $Author:: Ian_l                                                       $*
 *                                                                                             *
 *                     $Modtime:: 10/31/01 2:02p                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef RAMFILE_H
#define RAMFILE_H

#include "wwfile.h"

class RAMFileClass : public FileClass {
public:
  RAMFileClass(void *buffer, int len);
  virtual ~RAMFileClass();

  virtual char const *File_Name() const { return ("UNKNOWN"); }
  virtual char const *Set_Name(char const *) { return (File_Name()); }
  virtual int Create();
  virtual int Delete();
  virtual bool Is_Available(int forced = false);
  virtual bool Is_Open() const;
  virtual int Open(char const *filename, int access = READ);
  virtual int Open(int access = READ);
  virtual int Read(void *buffer, int size);
  virtual int Seek(int pos, int dir = SEEK_CUR);
  virtual int Size();
  virtual int Write(void const *buffer, int size);
  virtual void Close();
  virtual unsigned long Get_Date_Time() { return (0); }
  virtual bool Set_Date_Time(unsigned long) { return (true); }
  virtual void Error(int, int = false, char const * = nullptr) {}
  virtual void Bias(int start, int length = -1);

  operator char const *() { return File_Name(); }

private:
  /*
  **	Pointer to the buffer that the "file" will reside in.
  */
  char *Buffer;

  /*
  **	The maximum size of the buffer. The file occupying the buffer
  **	may be smaller than this size.
  */
  int MaxLength;

  /*
  **	The number of bytes in the sub-file occupying the buffer.
  */
  int Length;

  /*
  **	The current file position offset within the buffer.
  */
  int Offset;

  /*
  **	The file was opened with this access mode.
  */
  int Access;

  /*
  **	Is the file currently open?
  */
  bool IsOpen;

  /*
  **	Was the file buffer allocated during construction of this object?
  */
  bool IsAllocated;
};

#endif
