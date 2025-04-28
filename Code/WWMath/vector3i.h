/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**	Copyright 2025 CnC Rebel Developers.
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
 *                     $Archive:: /Commando/Code/wwmath/vector3i.h                            $*
 *                                                                                             *
 *                       Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                     $Modtime:: 11/24/01 5:24p                                              $*
 *                                                                                             *
 *                    $Revision:: 5                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#ifndef VECTOR3I_H
#define VECTOR3I_H

#include "always.h"

class Vector3i {
public:
  int I;
  int J;
  int K;

  WWINLINE Vector3i();
  WWINLINE Vector3i(int i, int j, int k);

  WWINLINE bool operator==(const Vector3i &v) const;
  WWINLINE bool operator!=(const Vector3i &v) const;
  WWINLINE const int &operator[](int n) const;
  WWINLINE int &operator[](int n);
};

WWINLINE Vector3i::Vector3i() {}

WWINLINE Vector3i::Vector3i(int i, int j, int k) {
  I = i;
  J = j;
  K = k;
}

WWINLINE bool Vector3i::operator==(const Vector3i &v) const { return (I == v.I && J == v.J && K == v.K); }

WWINLINE bool Vector3i::operator!=(const Vector3i &v) const { return !(I == v.I && J == v.J && K == v.K); }

WWINLINE const int &Vector3i::operator[](int n) const { return ((int *)this)[n]; }

WWINLINE int &Vector3i::operator[](int n) { return ((int *)this)[n]; }

// ----------------------------------------------------------------------------

class Vector3i16 {
public:
  unsigned short I;
  unsigned short J;
  unsigned short K;

  WWINLINE Vector3i16();
  WWINLINE Vector3i16(unsigned short i, unsigned short j, unsigned short k);

  WWINLINE bool operator==(const Vector3i &v) const;
  WWINLINE bool operator!=(const Vector3i &v) const;
  WWINLINE const unsigned short &operator[](int n) const;
  WWINLINE unsigned short &operator[](int n);
};

WWINLINE Vector3i16::Vector3i16() {}

WWINLINE Vector3i16::Vector3i16(unsigned short i, unsigned short j, unsigned short k) {
  I = i;
  J = j;
  K = k;
}

WWINLINE bool Vector3i16::operator==(const Vector3i &v) const { return (I == v.I && J == v.J && K == v.K); }

WWINLINE bool Vector3i16::operator!=(const Vector3i &v) const { return !(I == v.I && J == v.J && K == v.K); }

WWINLINE const unsigned short &Vector3i16::operator[](int n) const { return ((unsigned short *)this)[n]; }

WWINLINE unsigned short &Vector3i16::operator[](int n) { return ((unsigned short *)this)[n]; }

#endif