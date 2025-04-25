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

/******************************************************************************
 *
 * FILE
 *     Common.cpp
 *
 * DESCRIPTION
 *     Programmer Inserted Common Scripting Functions
 *
 * PROGRAMMER
 *     Programming Team
 *
 * VERSION INFO
 *     $Author: Rich_d $
 *     $Revision: 14 $
 *     $Modtime: 6/13/00 11:46a $
 *     $Archive: /Commando/Code/Scripts/Common.cpp $
 *
 ******************************************************************************/

#include "common.h"

/******************************************************************************
 *
 * NAME
 *     RandomVector3
 *
 * DESCRIPTION
 *     Generate a random vector.
 *
 * INPUTS
 *     xRange - Maximum X extent.
 *     yRange - Maximum Y extent.
 *     zRange - Maximum Z extent.
 *
 * RESULTS
 *     Vector - Randomized vector
 *
 ******************************************************************************/

Vector3 RandomVector3(float xRange, float yRange, float zRange) {
  float x = Commands->Get_Random(-xRange, xRange);
  float y = Commands->Get_Random(-yRange, yRange);
  float z = Commands->Get_Random(-zRange, zRange);

  return Vector3(x, y, z);
}
