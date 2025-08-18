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
 ***                            Confidential - Westwood Studios                              ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Commando                                                     *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/Combat/ffactorylist.h                        $*
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 6/20/02 2:07p                                               $*
 *                                                                                             *
 *                    $Revision:: 8                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#ifndef ALWAYS_H
#include "always.h"
#endif

#ifndef SIMPLEVEC_H
#include "simplevec.h"
#endif

#ifndef FFACTORY_H
#include "ffactory.h"
#endif

/*
**
*/
class FileFactoryListClass : public FileFactoryClass {

public:
  FileFactoryListClass();
  ~FileFactoryListClass();

  void Add_FileFactory(FileFactoryClass *factory, const char *name);
  void Remove_FileFactory(FileFactoryClass *factory);
  FileFactoryClass *Remove_FileFactory();

  void Set_Search_Start(const char *name);
  void Reset_Search_Start() { SearchStartIndex = 0; }

  void Add_Temp_FileFactory(FileFactoryClass *factory);
  FileFactoryClass *Remove_Temp_FileFactory();
  FileFactoryClass *Peek_Temp_FileFactory() { return TempFactory; }

  virtual FileClass *Get_File(char const *filename);
  virtual void Return_File(FileClass *file);

  static FileFactoryListClass *Get_Instance() { return Instance; }

  int Get_Factory_Count() const { return FactoryList.Count(); }
  FileFactoryClass *Get_Factory(int index) { return FactoryList[index]; }

private:
  FileFactoryClass *TempFactory;
  SimpleDynVecClass<FileFactoryClass *> FactoryList;
  DynamicVectorClass<StringClass> FactoryNameList;
  int SearchStartIndex;

  static FileFactoryListClass *Instance;
};
