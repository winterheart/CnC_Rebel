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
 *                 Project Name : wwlib                                                        *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwlib/rcfile.cpp                             $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 7/09/99 1:37p                                               $*
 *                                                                                             *
 *                    $Revision:: 5                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include <cstdlib>

#include "rcfile.h"

const char *RESOURCE_FILE_TYPE_NAME = "File";

ResourceFileClass::ResourceFileClass(HMODULE hmodule, char const *filename)
    : ResourceName(nullptr), hModule(nullptr), FileBytes(nullptr), FilePtr(nullptr), EndOfFile(nullptr) {
  Set_Name(filename);
  HRSRC hresource = FindResource(hmodule, ResourceName, RESOURCE_FILE_TYPE_NAME);

  if (hresource) {
    HGLOBAL hglob = LoadResource(hmodule, hresource);
    if (hglob) {
      FileBytes = (unsigned char *)LockResource(hglob);
      if (FileBytes) {
        FilePtr = FileBytes;
        EndOfFile = FileBytes + SizeofResource(hmodule, hresource);
      }
    }
  }
}

ResourceFileClass::~ResourceFileClass(void) {
  if (ResourceName)
    free(ResourceName);
}

char const *ResourceFileClass::Set_Name(char const *filename) {
  if (ResourceName) {
    free(ResourceName);
    ResourceName = nullptr;
  }
  if (filename) {
    ResourceName = strdup(filename);
  }
  return ResourceName;
}

int ResourceFileClass::Read(void *buffer, int size) {
  if (!FilePtr)
    return 0;

  if (FilePtr + size > EndOfFile) {
    size = EndOfFile - FilePtr;
  }
  memcpy(buffer, FilePtr, size);
  FilePtr += size;
  return size;
}

int ResourceFileClass::Seek(int pos, int dir) {
  switch (dir) {
  case SEEK_SET:
    FilePtr = FileBytes + pos;
    break;

  case SEEK_CUR:
    FilePtr = FilePtr + pos;
    break;

  case SEEK_END:
    FilePtr = EndOfFile + pos;
    break;
  }

  if (FilePtr > EndOfFile) {
    FilePtr = EndOfFile;
  }
  if (FilePtr < FileBytes) {
    FilePtr = FileBytes;
  }

  return FilePtr - FileBytes;
}

int ResourceFileClass::Size() { return EndOfFile - FileBytes; }

void ResourceFileClass::Error(int /*error*/, int /*canretry*/, char const * /*filename*/) {}
