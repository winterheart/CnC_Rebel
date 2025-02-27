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
 *                     $Archive:: /Commando/Code/Tools/LevelEdit/NodeTypes.h                  $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 9/19/01 2:36p                                               $*
 *                                                                                             *
 *                    $Revision:: 13                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __NODETYPES_H
#define __NODETYPES_H


///////////////////////////////////////////////////
//
//	Typedefs and structs
//
typedef enum
{
	NODE_TYPE_UNKNOWN = 0,
	NODE_TYPE_TERRAIN,
	NODE_TYPE_TERRAIN_SECTION,
	NODE_TYPE_TILE,
	NODE_TYPE_OBJECT,
	NODE_TYPE_ZONE,
	NODE_TYPE_WAYPATH,
	NODE_TYPE_WAYPOINT,
	NODE_TYPE_LIGHT,
	NODE_TYPE_TRANSITION,
	NODE_TYPE_TRANSITION_CHARACTER,
	NODE_TYPE_SOUND,
	NODE_TYPE_VIS,
	NODE_TYPE_SPAWNER,
	NODE_TYPE_VIS_POINT,
	NODE_TYPE_PATHFIND_START,
	NODE_TYPE_DUMMY_OBJECT,
	NODE_TYPE_COVER_SPOT,
	NODE_TYPE_COVER_ATTACK_POINT,
	NODE_TYPE_DAMAGE_ZONE,
	NODE_TYPE_BUILDING,
	NODE_TYPE_SPAWN_POINT,
	NODE_TYPE_BUILDING_CHILD_NODE,
	NODE_TYPE_EDITOR_ONLY_OBJ,
	NODE_TYPE_COUNT
} NODE_TYPE;


#endif //__NODETYPES_H
