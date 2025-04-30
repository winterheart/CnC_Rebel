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

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef DX8_MISSING_TEXTURE_H
#define DX8_MISSING_TEXTURE_H

#include "always.h"
#include "dxdefs.h"

class MissingTexture {
public:
  static void _Init();
  static void _Deinit();

  static DX_IDirect3DTexture *_Get_Missing_Texture();    // Return a reference to missing texture
  static DX_IDirect3DSurface *_Create_Missing_Surface(); // Create new surface which contain missing texture image
};

#endif // DX8_MISSING_TEXTURE