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
 *                     $Archive:: /Commando/Code/Tools/LevelEdit/DefinitionUtils.h            $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 9/20/00 7:40p                                               $*
 *                                                                                             *
 *                    $Revision:: 6                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __DEFINITION_UTILS_H
#define __DEFINITION_UTILS_H

///////////////////////////////////////////////////////////////////////
// Forward declarations
///////////////////////////////////////////////////////////////////////
class DefinitionClass;
class PhysClass;


///////////////////////////////////////////////////////////////////////
//
//	Prototypes
//
///////////////////////////////////////////////////////////////////////
DefinitionClass *	Create_Physics_Definition (LPCTSTR base_class_name, bool is_temp = false);
DefinitionClass *	Create_Definition (int class_id);
void					Copy_Definition (DefinitionClass *src, DefinitionClass *dest, bool is_temp);
DefinitionClass *	Find_Physics_Definition (DefinitionClass *parent);

PhysClass *			Get_Phys_Obj_From_Definition (DefinitionClass *definition);

void					Build_Embedded_Definition_List (DEFINITION_LIST &list, DefinitionClass *parent);
void					Fix_Embedded_Definition_IDs (DefinitionClass *parent);


#endif //__DEFINITION_UTILS_H
