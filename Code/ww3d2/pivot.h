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

/* $Header: /Commando/Code/ww3d2/pivot.h 1     1/22/01 3:36p Greg_h $ */
/***********************************************************************************************
 ***                            Confidential - Westwood Studios                              ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Commando / G 3D Library                                      *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/pivot.h                                $*
 *                                                                                             *
 *                       Author:: Greg_h                                                       *
 *                                                                                             *
 *                     $Modtime:: 1/08/01 10:04a                                              $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef PIVOT_H
#define PIVOT_H

#include "always.h"
#include "vector3.h"
#include "matrix3d.h"
#include "quat.h"
#include "w3d_file.h"

/*

        PivotClass

        Each node of the hierarchy tree is represented by a
        PivotClass.

*/

struct PivotClass {
public:
  PivotClass(void);
  ~PivotClass(void) {}

  char Name[W3D_NAME_LEN];
  int Index;

  PivotClass *Parent;

  // Base configuration of this pivot
  Matrix3D BaseTransform; // base-pose transform (relative to parent).

  Matrix3D Transform; // computed transform for this pivot
  bool IsVisible;     // result of the visibility channel

  // User control.  When a pivot is 'captured' animation data is ignored and the
  // user data is used to control the pivot.
  bool IsCaptured;
  Matrix3D CapTransform;
  bool WorldSpaceTranslation;

  void Capture_Update(void);
};

#endif