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
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwlib/ffactory.cpp                           $*
 *                                                                                             *
 *                      $Author:: Jani_p                                                      $*
 *                                                                                             *
 *                     $Modtime:: 8/24/01 11:50a                                              $*
 *                                                                                             *
 *                    $Revision:: 17                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#include <cassert>

#include "ffactory.h"
#include "rawfile.h"
#include "bufffile.h"

/*
** Statics
** NOTE: If _TheFileFactory is ever changed to point to an object of a different class which does
** not derive from SimpleFileFactoryClass, _TheSimpleFileFactory should be set to NULL.
*/
SimpleFileFactoryClass _DefaultFileFactory;
FileFactoryClass *_TheFileFactory = &_DefaultFileFactory;
SimpleFileFactoryClass *_TheSimpleFileFactory = &_DefaultFileFactory;

SimpleFileFactoryClass _DefaultWritingFileFactory;
FileFactoryClass *_TheWritingFileFactory = &_DefaultWritingFileFactory;

/*
**
*/
file_auto_ptr::file_auto_ptr(FileFactoryClass *fac, const char *filename) : _Ptr(nullptr), _Fac(fac) {
  assert(_Fac);
  _Ptr = _Fac->Get_File(filename);
  if (_Ptr == nullptr) {
    _Ptr = new BufferedFileClass();
  }
}

file_auto_ptr::~file_auto_ptr() { _Fac->Return_File(_Ptr); }

/*
** RawFileFactoryClass implementation
*/
FileClass *RawFileFactoryClass::Get_File(char const *filename) { return new RawFileClass(filename); }

void RawFileFactoryClass::Return_File(FileClass *file) { delete file; }

/*
** SimpleFileFactoryClass implementation
*/

void SimpleFileFactoryClass::Get_Sub_Directory(std::vector<std::filesystem::path> &new_dir) const {
  // BEGIN SERIALIZATION

  new_dir = SubDirectory;
  // END SERIALIZATION
}

void SimpleFileFactoryClass::Set_Sub_Directory(const std::vector<std::filesystem::path> &sub_directory) {
  // BEGIN SERIALIZATION

  SubDirectory = sub_directory;
  // END SERIALIZATION
}

void SimpleFileFactoryClass::Prepend_Sub_Directory(const std::filesystem::path &sub_directory) {

  // BEGIN SERIALIZATION

  // StringClass makes no guarantees on the atomicity of concatenation.
  // Just to be safe, we lock before executing the concatenation code.
  // (NH, 04/23/01)

  std::lock_guard lock(Mutex);
  SubDirectory.insert(SubDirectory.begin(), sub_directory);

  // END SERIALIZATION
}

void SimpleFileFactoryClass::Append_Sub_Directory(const std::filesystem::path& sub_directory) {
  // BEGIN SERIALIZATION

  // We are doing various dependent operations on SubDirectory.
  // Just to be safe, we lock before this section.
  // (NH, 04/23/01)

  std::lock_guard lock(Mutex);

  SubDirectory.push_back(sub_directory);
  // END SERIALIZATION
}

/*
**
*/
FileClass *SimpleFileFactoryClass::Get_File(char const *filename) {
  std::filesystem::path new_name;
  RawFileClass *file = new BufferedFileClass(); // new RawWritingFileClass();
  assert(file);

  //
  //	Do we need to find the path for this file request?
  //
  if (std::filesystem::path(filename).is_relative()) {

    // BEGIN SERIALIZATION

    if (!SubDirectory.empty()) {

      //
      // SubDirectory may contain a semicolon seperated search path...
      // If the file doesn't exist, we'll set the path to the last dir in
      // the search path.  Therefore, newly created files will always go in the
      // last dir in the search path.
      //

      for (const auto& itm : SubDirectory) {
        new_name = itm / filename;
        file->Set_Name(new_name.string().c_str());
        if (file->Open()) {
          file->Close();
          break;
        }
      }
    }

    // END SERIALIZATION
  }

  file->Set_Name(new_name.string().c_str()); // Call Set_Name to force an allocated name
  return file;
}

void SimpleFileFactoryClass::Return_File(FileClass *file) { delete file; }
