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
 *                 Project Name : WWMath                                                       *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwmath/colmathfrustum.h                      $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Jani_p                                                      $*
 *                                                                                             *
 *                     $Modtime:: 5/04/01 8:25p                                               $*
 *                                                                                             *
 *                    $Revision:: 3                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   CollisionMath::Overlap_Test -- test a frustum and an AABox for overlap                    *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef COLMATHFRUSTUM_H
#define COLMATHFRUSTUM_H

#include "always.h"
#include "aabox.h"
#include "vector3.h"
#include "lineseg.h"
#include "frustum.h"

/*
** Inline collision functions dealing with frustums
*/

/***********************************************************************************************
 * CollisionMath::Overlap_Test -- test a frustum and an AABox for overlap                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/29/2000  gth : Created.                                                                 *
 *=============================================================================================*/
inline CollisionMath::OverlapType CollisionMath::Overlap_Test(const FrustumClass &frustum, const AABoxClass &box,
                                                              int &planes_passed) {
  int mask = 0;

  // TODO: doesn't catch all cases...
  for (int i = 0; i < 6; i++) {

    int plane_bit = (1 << i);

    // only check this plane if we have to
    if ((planes_passed & plane_bit) == 0) {

      int result = CollisionMath::Overlap_Test(frustum.Planes[i], box);
      if (result == OUTSIDE) {

        return OUTSIDE;
      } else if (result == INSIDE) {
        planes_passed |= plane_bit;
      }
      mask |= result;

    } else {

      mask |= INSIDE;
    }
  }

  if (mask == INSIDE) {
    return INSIDE;
  }
  return OVERLAPPED;
}

#endif
