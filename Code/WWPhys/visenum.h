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
 *                 Project Name : WWPhys                                                       *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwphys/visenum.h                             $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 9/28/00 11:22a                                              $*
 *                                                                                             *
 *                    $Revision:: 5                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef VISENUM_H
#define VISENUM_H

enum VisStatusType {
  VIS_STATUS_OK = 0,
  VIS_STATUS_NOT_TAKEN,
  VIS_STATUS_ERROR,
  VIS_STATUS_BACKFACE_LEAK,
  VIS_STATUS_BACKFACE_OVERFLOW,
};

enum VisDirBitsType {
  VIS_FORWARD_BIT = 0x0001,   // comptue visibility forward
  VIS_LEFT_BIT = 0x0002,      // compute visibility left
  VIS_BACKWARDS_BIT = 0x0004, // compute visibility behind
  VIS_RIGHT_BIT = 0x0008,     // compute visibility to the right
  VIS_UP_BIT = 0x0010,        // compute visibility up
  VIS_DOWN_BIT = 0x0020,      // compute visiblity down
  VIS_FORCE_ACCEPT = 0x0040,  // accept this sample no matter what!
  VIS_DONT_RECENTER = 0x0080, // don't recenter the view-plane
  VIS_ALL = VIS_FORWARD_BIT | VIS_LEFT_BIT | VIS_BACKWARDS_BIT | VIS_RIGHT_BIT | VIS_UP_BIT | VIS_DOWN_BIT,
};

enum VisDirType {
  // direction indices, most functions use these
  VIS_FORWARD = 0,
  VIS_LEFT,
  VIS_BACKWARDS,
  VIS_RIGHT,
  VIS_UP,
  VIS_DOWN,
  VIS_DIRECTIONS
};

const float VIS_NEAR_CLIP = 0.2f;
const float VIS_FAR_CLIP = 300.0f;

#endif
