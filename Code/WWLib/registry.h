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
 *                 Project Name : Commando / G Library                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwlib/registry.h                             $*
 *                                                                                             *
 *                      $Author:: Steve_t                                                     $*
 *                                                                                             *
 *                     $Modtime:: 11/21/01 3:42p                                              $*
 *                                                                                             *
 *                    $Revision:: 12                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#ifndef REGISTRY_H
#define REGISTRY_H

#ifndef ALWAYS_H
#include "always.h"
#endif

#include "vector.h"
#include "wwstring.h"
#include "widestring.h"

class INIClass;

/*
**
*/
class RegistryClass {
public:
  static bool Exists(const HKEY root, const char *sub_key);
  static bool Exists(const char *sub_key);

  // Constructor & Destructor
  RegistryClass(const HKEY root, const char *sub_key, bool create = true);
  RegistryClass(const char *sub_key, bool create = true);
  ~RegistryClass();

  bool Is_Valid() { return IsValid; }

  // Int data type access
  int Get_Int(const char *name, int def_value = 0);
  void Set_Int(const char *name, int value);

  // Bool data type access
  bool Get_Bool(const char *name, bool def_value = false);
  void Set_Bool(const char *name, bool value);

  // Float data type access
  float Get_Float(const char *name, float def_value = 0.0f);
  void Set_Float(const char *name, float value);

  // String data type access
  char *Get_String(const char *name, char *value, int value_size, const char *default_string = nullptr);
  void Get_String(const char *name, StringClass &string, const char *default_string = nullptr);
  void Set_String(const char *name, const char *value);

  // Wide string data type access
  void Get_String(const WCHAR *name, WideStringClass &string, const WCHAR *default_string = nullptr);
  void Set_String(const WCHAR *name, const WCHAR *value);

  // Binary data type access
  void Get_Bin(const char *name, void *buffer, int buffer_size);
  int Get_Bin_Size(const char *name);
  void Set_Bin(const char *name, const void *buffer, int buffer_size);

  // Value enumeration support
  void Get_Value_List(DynamicVectorClass<StringClass> &list);

  // Delete support
  void Delete_Value(const char *name);
  void Deleta_All_Values();

  // Read only.
  static void Set_Read_Only(bool set) { IsLocked = set; }

  //
  // Bulk registry operations. BE VERY VERY CAREFUL USING THESE
  //
  static void Delete_Registry_Tree(HKEY root, char *path);
  static void Delete_Registry_Tree(char *path);
  static void Load_Registry(const char *filename, HKEY root, const char *old_path, const char *new_path);
  static void Load_Registry(const char *filename, char *old_path, char *new_path);
  static void Save_Registry(const char *filename, HKEY root, const char *path);
  static void Save_Registry(const char *filename, char *path);

  // Migrate entries from src to dst location
  static bool Migrate_Registry(HKEY src_root, const char *src_path, HKEY dst_root, const char *dst_path);

private:
  static void Delete_Registry_Values(HKEY key);
  static void Save_Registry_Tree(HKEY root, const char *path, INIClass *ini);
  static void Save_Registry_Values(HKEY key, const char *path, INIClass *ini);

  int Key;
  bool IsValid;

  //
  // Use this to make the registry 'read only'. Useful for running multiple copies of the app.
  //
  static bool IsLocked;
};

#endif // REGISTRY_H