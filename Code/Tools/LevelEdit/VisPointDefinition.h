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
 *                 Project Name : LevelEdit                                                    *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/Tools/LevelEdit/VisPointDefinition.h    $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 10/20/99 3:55p                                               $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __VIS_POINT_DEFINITION_H
#define __VIS_POINT_DEFINITION_H

#include "definition.h"
#include "vector.h"
#include "wwstring.h"
#include "editorchunkids.h"

//////////////////////////////////////////////////////////////////////////////////
//
//	VisPointDefinitionClass
//
//////////////////////////////////////////////////////////////////////////////////
class VisPointDefinitionClass : public DefinitionClass {

public:
  /////////////////////////////////////////////////////////////////////
  //	Editable interface requirements
  /////////////////////////////////////////////////////////////////////
  DECLARE_EDITABLE(VisPointDefinitionClass, DefinitionClass);

  //////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  //////////////////////////////////////////////////////////////
  VisPointDefinitionClass(void);
  virtual ~VisPointDefinitionClass(void);

  // From DefinitionClass
  virtual uint32 Get_Class_ID(void) const { return CLASSID_VIS_POINT_DEF; }

  // From PersistClass
  virtual const PersistFactoryClass &Get_Factory(void) const;
  virtual bool Save(ChunkSaveClass &csave);
  virtual bool Load(ChunkLoadClass &cload);
  virtual PersistClass *Create(void) const;

private:
};

#endif //__VIS_POINT_DEFINITION_H
