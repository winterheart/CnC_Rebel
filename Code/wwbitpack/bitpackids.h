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
 ***                            Confidential - Westwood Studios                              ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Commando                                                     *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwbitpack/bitpackids.h                       $*
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 10/14/01 11:15a                                             $*
 *                                                                                             *
 *                    $Revision:: 6                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef	BITPACKIDS_H
#define	BITPACKIDS_H

enum {
	/*
	//
	// 08/30/00 Use of pathfind extents for bitcompression decommissioned.
	// Flying vehicles and sea vehicles would have to use world extents
	// anyway.
	//

	//
	// Use these for objects restricted to pathfindable areas
	//
	BITPACK_PATHFIND_POSITION_X,
	BITPACK_PATHFIND_POSITION_Y,
	BITPACK_PATHFIND_POSITION_Z,
	*/

	//
	// Use these for objects restricted to world extents
	//
	BITPACK_WORLD_POSITION_X,
	BITPACK_WORLD_POSITION_Y,
	BITPACK_WORLD_POSITION_Z,

	BITPACK_ONE_TIME_BOOLEAN_BITS,
	BITPACK_CONTINUOUS_BOOLEAN_BITS,
	BITPACK_ANALOG_VALUES,

	BITPACK_HEALTH,
	BITPACK_SHIELD_STRENGTH,
	BITPACK_SHIELD_TYPE,

	BITPACK_CTF_TEAM_FLAG,

	BITPACK_HUMAN_STATE,
	BITPACK_HUMAN_SUB_STATE,

	BITPACK_VEHICLE_VELOCITY,
	BITPACK_VEHICLE_ANGULAR_VELOCITY,
	BITPACK_VEHICLE_QUATERNION,
	BITPACK_VEHICLE_LOCK_TIMER,

	BITPACK_DOOR_STATE,
	BITPACK_ELEVATOR_STATE,
	BITPACK_ELEVATOR_TOP_DOOR_STATE,
	BITPACK_ELEVATOR_BOTTOM_DOOR_STATE,

	BITPACK_BUILDING_RADIUS,

	BITPACK_BUILDING_STATE,

	BITPACK_CONTROL_MOVES_CS,
	BITPACK_CONTROL_MOVES_SC,

	BITPACK_PACKET_TYPE,
	BITPACK_PACKET_ID,

};

#endif	// BITPACKIDS_H
