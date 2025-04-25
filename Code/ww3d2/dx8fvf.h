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
 *                 Project Name : ww3d                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/dx8fvf.h                               $*
 *                                                                                             *
 *              Original Author:: Jani Penttinen                                               *
 *                                                                                             *
 *                      $Author:: Jani_p                                                      $*
 *                                                                                             *
 *                     $Modtime:: 3/29/01 12:44a                                              $*
 *                                                                                             *
 *                    $Revision:: 5                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef DX8_FVF_H
#define DX8_FVF_H

#include "always.h"
#include "dxdefs.h"
#ifdef WWDEBUG
#include "wwdebug.h"
#endif

class StringClass;

enum {
  DX8_FVF_XYZ = D3DFVF_XYZ,
  DX8_FVF_XYZN = D3DFVF_XYZ | D3DFVF_NORMAL,
  DX8_FVF_XYZNUV1 = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1,
  DX8_FVF_XYZNUV2 = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2,
  DX8_FVF_XYZNDUV1 = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_DIFFUSE,
  DX8_FVF_XYZNDUV2 = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2 | D3DFVF_DIFFUSE,
  DX8_FVF_XYZDUV1 = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_DIFFUSE,
  DX8_FVF_XYZDUV2 = D3DFVF_XYZ | D3DFVF_TEX2 | D3DFVF_DIFFUSE,
  DX8_FVF_XYZUV1 = D3DFVF_XYZ | D3DFVF_TEX1,
  DX8_FVF_XYZUV2 = D3DFVF_XYZ | D3DFVF_TEX2
};

// ----------------------------------------------------------------------------
//
// Util structures for vertex buffer handling. Cast the void pointer returned
// by the vertex buffer to one of these structures.
//
// ----------------------------------------------------------------------------

struct VertexFormatXYZ {
  float x;
  float y;
  float z;
};

struct VertexFormatXYZNUV1 {
  float x;
  float y;
  float z;
  float nx;
  float ny;
  float nz;
  float u1;
  float v1;
};

struct VertexFormatXYZNUV2 {
  float x;
  float y;
  float z;
  float nx;
  float ny;
  float nz;
  float u1;
  float v1;
  float u2;
  float v2;
};

struct VertexFormatXYZN {
  float x;
  float y;
  float z;
  float nx;
  float ny;
  float nz;
};

struct VertexFormatXYZNDUV1 {
  float x;
  float y;
  float z;
  float nx;
  float ny;
  float nz;
  unsigned diffuse;
  float u1;
  float v1;
};

struct VertexFormatXYZNDUV2 {
  float x;
  float y;
  float z;
  float nx;
  float ny;
  float nz;
  unsigned diffuse;
  float u1;
  float v1;
  float u2;
  float v2;
};

struct VertexFormatXYZDUV1 {
  float x;
  float y;
  float z;
  unsigned diffuse;
  float u1;
  float v1;
};

struct VertexFormatXYZDUV2 {
  float x;
  float y;
  float z;
  unsigned diffuse;
  float u1;
  float v1;
  float u2;
  float v2;
};

struct VertexFormatXYZUV1 {
  float x;
  float y;
  float z;
  float u1;
  float v1;
};

struct VertexFormatXYZUV2 {
  float x;
  float y;
  float z;
  float u1;
  float v1;
  float u2;
  float v2;
};

// FVF info class can be created for any legal FVF. It constructs information
// of offsets to various elements in the vertex buffer.

class FVFInfoClass {
  unsigned FVF;
  unsigned fvf_size;

  unsigned location_offset;
  unsigned normal_offset;
  unsigned blend_offset;
  unsigned texcoord_offset[D3DDP_MAXTEXCOORD];
  unsigned diffuse_offset;
  unsigned specular_offset;

public:
  FVFInfoClass(unsigned FVF);

  inline unsigned Get_Location_Offset() const { return location_offset; }
  inline unsigned Get_Normal_Offset() const { return normal_offset; }
#ifdef WWDEBUG
  inline unsigned Get_Tex_Offset(unsigned int n) const {
    WWASSERT(n < D3DDP_MAXTEXCOORD);
    return texcoord_offset[n];
  }
#else
  inline unsigned Get_Tex_Offset(unsigned int n) const { return texcoord_offset[n]; }
#endif

  inline unsigned Get_Diffuse_Offset() const { return diffuse_offset; }
  inline unsigned Get_Specular_Offset() const { return specular_offset; }
  inline unsigned Get_FVF() const { return FVF; }
  inline unsigned Get_FVF_Size() const { return fvf_size; }

  void Get_FVF_Name(StringClass &fvfname) const; // For debug purposes
};

#endif
