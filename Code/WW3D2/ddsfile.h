/*
 * 	Command & Conquer Renegade(tm)
 * 	Copyright 2025 Electronic Arts Inc.
 * 	Copyright 2025 CnC: Rebel Developers.
 *
 * 	This program is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License as published by
 * 	the Free Software Foundation, either version 3 of the License, or
 * 	(at your option) any later version.
 *
 * 	This program is distributed in the hope that it will be useful,
 * 	but WITHOUT ANY WARRANTY; without even the implied warranty of
 * 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * 	GNU General Public License for more details.
 *
 * 	You should have received a copy of the GNU General Public License
 * 	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifndef DDSFILE_H
#define DDSFILE_H

#include <cstdint>
#include <filesystem>
#include <vector>

#include "always.h"
#include "dxdefs.h"
#include "ww3dformat.h"

struct DDS_PIXELFORMAT {
  uint32_t dwSize;
  uint32_t dwFlags;
  uint32_t dwFourCC;
  uint32_t dwRGBBitCount;
  uint32_t dwRBitMask;
  uint32_t dwGBitMask;
  uint32_t dwBBitMask;
  uint32_t dwABitMask;
};

struct DDS_HEADER {
  uint32_t dwSize;
  uint32_t dwFlags;
  uint32_t dwHeight;
  uint32_t dwWidth;
  uint32_t dwPitchOrLinearSize;
  uint32_t dwDepth;
  uint32_t dwMipMapCount;
  uint32_t dwReserved1[11];
  DDS_PIXELFORMAT ddspf;
  uint32_t dwCaps1;
  uint32_t dwCaps2;
  uint32_t dwReserved2[3];
};

// ----------------------------------------------------------------------------
//
// Utility class for loading DDS files. Simply create an instance of the class
// locally, call Load() and use the copy functions to retrieve the surface.
// The class handles conversion of the surface to equal compressed formats
// and all non-compressed formats. the compressed DXTn formats can't be cross-
// converted except for DXT1 which can be converted to DXT2 (this feature is
// needed as the NVidia cards have problems with DXT1).
//
// ----------------------------------------------------------------------------

class DDSFileClass {
  uint32_t Width;
  uint32_t Height;
  uint32_t FullWidth;
  uint32_t FullHeight;
  uint32_t MipLevels;
  unsigned long DateTime;
  uint32_t ReductionFactor;
  unsigned char *DDSMemory;
  WW3DFormat Format;
  std::vector<uint32_t> LevelSizes;
  std::vector<uint32_t> LevelOffsets;
  DDS_HEADER SurfaceDesc;
  std::filesystem::path Name;

public:
  // You can pass the name in .tga or .dds format, the class will automatically try and load .dds file.
  // Note that creating the object will only give you image info - call Load() to load the surfaces.
  DDSFileClass(const char *name, unsigned reduction_factor);
  ~DDSFileClass();

  uint32_t Get_Width(unsigned level) const;
  uint32_t Get_Height(unsigned level) const;
  uint32_t Get_Full_Width() const { return FullWidth; }   // Get the width of level 0 of non-reduced texture
  uint32_t Get_Full_Height() const { return FullHeight; } // Get the height of level 0 of non-reduced texture
  unsigned long Get_Date_Time() const { return DateTime; }

  uint32_t Get_Mip_Level_Count() const { return MipLevels; }
  const unsigned char *Get_Memory_Pointer(unsigned level) const;
  uint32_t Get_Level_Size(unsigned level) const;
  WW3DFormat Get_Format() const { return Format; }

  // Copy pixels to the destination surface.
  void Copy_Level_To_Surface(unsigned level, DX_IDirect3DSurface *d3d_surface);
  void Copy_Level_To_Surface(unsigned level, WW3DFormat dest_format, unsigned dest_width, unsigned dest_height,
                             unsigned char *dest_surface, unsigned dest_pitch);

  // Get pixel in A8R8G8B8 format. This isn't the fastest possible way of reading data from DDS.
  uint32_t Get_Pixel(unsigned level, unsigned x, unsigned y) const;

  // Uncompress one 4x4 block from the compressed image.
  // Returns: true if block contained alpha, false is not
  // Note: Destination can't be DXT or paletted surface!
  bool Get_4x4_Block(unsigned char *dest_ptr,  // Destination surface pointer
                     unsigned dest_pitch,      // Destination surface pitch, in bytes
                     WW3DFormat dest_format,   // Destination surface format, A8R8G8B8 is fastest
                     unsigned level,           // DDS mipmap level to copy from
                     unsigned source_x,        // DDS x offset to copy from, must be aligned by 4!
                     unsigned source_y) const; // DDS y offset to copy from, must be aligned by 4!

  bool Load();
  bool Is_Available() const { return !LevelSizes.empty(); }

  static uint32_t Calculate_DXTC_Surface_Size(unsigned width, unsigned height, WW3DFormat format);
};

// ----------------------------------------------------------------------------

#endif