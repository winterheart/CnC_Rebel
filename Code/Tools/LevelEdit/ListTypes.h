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
 *                     $Archive:: /Commando/Code/Tools/LevelEdit/ListTypes.h                  $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 7/06/00 5:11p                                               $*
 *                                                                                             *
 *                    $Revision:: 9                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __LISTTYPES_H
#define __LISTTYPES_H

#include "UniqueList.H"

//////////////////////////////////////////////////////////////////////////
//	Typedefs and structs
//////////////////////////////////////////////////////////////////////////
typedef UniqueListClass<class GroupMgrClass *> GROUP_LIST;
typedef UniqueListClass<class NodeClass *> NODE_LIST;

typedef DynamicVectorClass<CString> STRING_LIST;
typedef DynamicVectorClass<class EditScriptClass *> SCRIPT_LIST;

typedef DynamicVectorClass<class DefinitionClass *> DEFINITION_LIST;
typedef DynamicVectorClass<class PresetClass *> PRESET_LIST;
typedef DynamicVectorClass<class PresetListNode *> PRESET_NODE_LIST;

typedef DynamicVectorClass<class ZoneParameterClass *> ZONE_PARAM_LIST;

#endif //__LISTTYPES_H
