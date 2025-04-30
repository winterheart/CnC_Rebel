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
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwlib/font.h                                 $*
 *                                                                                             *
 *                      $Author:: Byon_g                                                      $*
 *                                                                                             *
 *                     $Modtime:: 11/28/00 2:40p                                              $*
 *                                                                                             *
 *                    $Revision:: 3                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#pragma once

#ifndef FONT_H
#define FONT_H

#include "convert.h"
#include "point.h"
#include "trect.h"

class Surface;

/*
**	A font object represent the data that comprises the individual characters as well
**	as drawing text in the font to a surface. This is an abstract base class that is to be
**	derived into a concrete version.
*/
class FontClass {
public:
  virtual ~FontClass() = default;

  virtual int Char_Pixel_Width(char c) const = 0;
  virtual int String_Pixel_Width(char const *string) const = 0;
  virtual int Get_Width() const = 0;
  virtual int Get_Height() const = 0;
  virtual Point2D Print(char const *string, Surface &surface, Rect const &cliprect, Point2D const &point,
                        ConvertClass const &converter, unsigned char const *remap = NULL) const = 0;

  virtual int Set_XSpacing(int x) = 0;
  virtual int Set_YSpacing(int y) = 0;
};

#endif
