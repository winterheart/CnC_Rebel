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
 *                     $Archive:: /Commando/Code/Tools/LevelEdit/nodetemplate.h      $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 4/18/01 9:08a                                               $*
 *                                                                                             *
 *                    $Revision:: 3                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __NODE_TEMPLATE_H
#define __NODE_TEMPLATE_H

#include "node.h"

//////////////////////////////////////////////////////////////////////////////////
//
//	NodeTemplateClass
//
//////////////////////////////////////////////////////////////////////////////////
class NodeTemplateClass {
public:
  //////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  //////////////////////////////////////////////////////////////
  NodeTemplateClass(void);
  ~NodeTemplateClass(void);

private:
  //////////////////////////////////////////////////////////////
  //	Private member data
  //////////////////////////////////////////////////////////////
  uint32 DefinitionID;
  Matrix3D Transform;
};

#endif //__NODE_TEMPLATE_H
