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
 *                 Project Name : leveledit                                                    *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/Tools/LevelEdit/editoronlydefinition.h       $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 9/19/01 3:07p                                                $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __EDITORONLYDEFINITION_H
#define __EDITORONLYDEFINITION_H

#include "definition.h"
#include "vector.h"
#include "wwstring.h"
#include "editorchunkids.h"

//////////////////////////////////////////////////////////////////////
//
//	EditorOnlyDefinitionClass
//
//////////////////////////////////////////////////////////////////////
class EditorOnlyDefinitionClass : public DefinitionClass {
public:
  /////////////////////////////////////////////////////////////////////
  //	Editable interface requirements
  /////////////////////////////////////////////////////////////////////
  DECLARE_EDITABLE(EditorOnlyDefinitionClass, DefinitionClass);

  //////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  //////////////////////////////////////////////////////////////
  EditorOnlyDefinitionClass(void);
  virtual ~EditorOnlyDefinitionClass(void);

  //
  // Inherited
  //
  virtual uint32 Get_Class_ID(void) const { return CLASSID_EDITOR_ONLY_OBJECTS; }
  virtual const PersistFactoryClass &Get_Factory(void) const;
  virtual bool Save(ChunkSaveClass &csave);
  virtual bool Load(ChunkLoadClass &cload);
  virtual PersistClass *Create(void) const;

  //
  // Accessors
  //
  virtual const char *Get_Model_Name(void) const { return ModelName; }

private:
  /////////////////////////////////////////////////////////////////////
  //	Private methods
  /////////////////////////////////////////////////////////////////////
  bool Save_Variables(ChunkSaveClass &csave);
  bool Load_Variables(ChunkLoadClass &cload);

  //////////////////////////////////////////////////////////////
  //	Private member data
  //////////////////////////////////////////////////////////////
  StringClass ModelName;
};

#endif //__EDITORONLYDEFINITION_H
