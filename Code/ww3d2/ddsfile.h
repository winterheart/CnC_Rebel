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

#ifndef DDSFILE_H
#define DDSFILE_H

#if defined(_MSC_VER)
#pragma once
#endif

#include "always.h"
#include "dxdefs.h"
#include "ww3dformat.h"
#include "wwstring.h"

// ----------------------------------------------------------------------------
//
// This structure represents the old DX7 color key structure. It is needed
// LegacyDDSURFACEDESC which is needed when loading DDS files. DO NOT MODIFY!
//
// ----------------------------------------------------------------------------

struct LegacyDDCOLORKEY {
  unsigned ColorSpaceLowValue;
  unsigned ColorSpaceHighValue;
};

// ----------------------------------------------------------------------------
//
// This structure represents the old DX7 CAPS2 structure. It is needed
// LegacyDDSURFACEDESC which is needed when loading DDS files. DO NOT MODIFY!
//
// ----------------------------------------------------------------------------

struct LegacyDDSCAPS2 {
  unsigned Caps;
  unsigned Caps2;
  unsigned Caps3;
  unsigned Caps4;
};

// ----------------------------------------------------------------------------
//
// This structure represents the old DX7 pixel format structure. It is needed
// LegacyDDSURFACEDESC which is needed when loading DDS files. DO NOT MODIFY!
//
// ----------------------------------------------------------------------------

struct LegacyDDPIXELFORMAT {
  unsigned Size;
  unsigned Flags;
  unsigned FourCC;
  union {
    unsigned RGBBitCount;
    unsigned YUVBitCount;
    unsigned ZBufferBitDepth;
    unsigned AlphaBitDepth;
    unsigned LuminanceBitCount;
    unsigned BumpBitCount;
  };
  union {
    unsigned RBitMask;
    unsigned YBitMask;
    unsigned StencilBitDepth;
    unsigned LuminanceBitMask;
    unsigned BumpDuBitMask;
  };
  union {
    unsigned GBitMask;
    unsigned UBitMask;
    unsigned ZBitMask;
    unsigned BumpDvBitMask;
  };
  union {
    unsigned BBitMask;
    unsigned VBitMask;
    unsigned StencilBitMask;
    unsigned BumpLuminanceBitMask;
  };
  union {
    unsigned RGBAlphaBitMask;
    unsigned YUVAlphaBitMask;
    unsigned LuminanceAlphaBitMask;
    unsigned RGBZBitMask;
    unsigned YUVZBitMask;
  };
};

// ----------------------------------------------------------------------------
//
// This structure represents the old DX7 surface description structure.
// It is needed when loading DDS files. DO NOT MODIFY!
//
// ----------------------------------------------------------------------------

struct LegacyDDSURFACEDESC2 {
  unsigned Size;
  unsigned Flags;
  unsigned Height;
  unsigned Width;
  union {
    unsigned Pitch;
    unsigned LinearSize;
  };
  unsigned BackBufferCount;
  union {
    unsigned MipMapCount;
    unsigned RefreshRate;
  };
  unsigned AlphaBitDepth;
  unsigned Reserved;
  void *Surface;
  union {
    LegacyDDCOLORKEY CKDestOverlay;
    unsigned EmptyFaceColor;
  };
  LegacyDDCOLORKEY CKDestBlt;
  LegacyDDCOLORKEY CKSrcOverlay;
  LegacyDDCOLORKEY CKSrcBlt;
  LegacyDDPIXELFORMAT PixelFormat;
  LegacyDDSCAPS2 Caps;
  unsigned TextureStage;
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
  unsigned Width;
  unsigned Height;
  unsigned FullWidth;
  unsigned FullHeight;
  unsigned MipLevels;
  unsigned long DateTime;
  unsigned ReductionFactor;
  unsigned char *DDSMemory;
  WW3DFormat Format;
  unsigned *LevelSizes;
  unsigned *LevelOffsets;
  LegacyDDSURFACEDESC2 SurfaceDesc;
  char Name[256];

  static unsigned Calculate_DXTC_Surface_Size(unsigned width, unsigned height, WW3DFormat format);

public:
  // You can pass the name in .tga or .dds format, the class will automatically try and load .dds file.
  // Note that creating the object will only give you image info - call Load() to load the surfaces.
  DDSFileClass(const char *name, unsigned reduction_factor);
  ~DDSFileClass();

  unsigned Get_Width(unsigned level) const;
  unsigned Get_Height(unsigned level) const;
  unsigned Get_Full_Width() const { return FullWidth; }   // Get the width of level 0 of non-reduced texture
  unsigned Get_Full_Height() const { return FullHeight; } // Get the height of level 0 of non-reduced texture
  unsigned long Get_Date_Time() const { return DateTime; }

  unsigned Get_Mip_Level_Count() const { return MipLevels; }
  const unsigned char *Get_Memory_Pointer(unsigned level) const;
  unsigned Get_Level_Size(unsigned level) const;
  WW3DFormat Get_Format() const { return Format; }

  // Copy pixels to the destination surface.
  void Copy_Level_To_Surface(unsigned level, DX_IDirect3DSurface *d3d_surface);
  void Copy_Level_To_Surface(unsigned level, WW3DFormat dest_format, unsigned dest_width, unsigned dest_height,
                             unsigned char *dest_surface, unsigned dest_pitch);

  // Get pixel in A8R8G8B8 format. This isn't the fastest possible way of reading data from DDS.
  unsigned Get_Pixel(unsigned level, unsigned x, unsigned y) const;

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
  bool Is_Available() const { return !!LevelSizes; }
};

// ----------------------------------------------------------------------------

#endif