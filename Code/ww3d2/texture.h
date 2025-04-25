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
 *                 Project Name : WW3D                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/texture.h                              $*
 *                                                                                             *
 *                      $Author:: Jani_p                                                      $*
 *                                                                                             *
 *                     $Modtime:: 11/09/01 5:16p                                              $*
 *                                                                                             *
 *                    $Revision:: 44                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef TEXTURE_H
#define TEXTURE_H

#include "always.h"
#include "dxdefs.h"
#include "refcount.h"
#include "chunkio.h"
#include "surfaceclass.h"
#include "ww3dformat.h"
#include "wwstring.h"

class DX8Wrapper;
class TextureLoader;
class LoaderThreadClass;
class DX8TextureManagerClass;
class TextureLoadTaskClass;

/*************************************************************************
**                             TextureClass
**
** This is our texture class. For legacy reasons it contains some
** information beyond the D3D texture itself, such as texture addressing
** modes.
**
*************************************************************************/
class TextureClass : public RefCountClass {
  friend DX8Wrapper;
  friend TextureLoader;
  friend LoaderThreadClass;
  friend DX8TextureManagerClass;

public:
  enum PoolType { POOL_DEFAULT = 0, POOL_MANAGED, POOL_SYSTEMMEM };

  enum FilterType { FILTER_TYPE_NONE, FILTER_TYPE_FAST, FILTER_TYPE_BEST, FILTER_TYPE_DEFAULT, FILTER_TYPE_COUNT };

  enum TextureFilterMode { TEXTURE_FILTER_BILINEAR, TEXTURE_FILTER_TRILINEAR, TEXTURE_FILTER_ANISOTROPIC };

  enum TxtAddrMode { TEXTURE_ADDRESS_REPEAT = 0, TEXTURE_ADDRESS_CLAMP };

  enum MipCountType {
    MIP_LEVELS_ALL = 0, // generate all mipmap levels down to 1x1 size
    MIP_LEVELS_1,       // no mipmapping at all (just one mip level)
    MIP_LEVELS_2,
    MIP_LEVELS_3,
    MIP_LEVELS_4,
    MIP_LEVELS_5,
    MIP_LEVELS_6,
    MIP_LEVELS_7,
    MIP_LEVELS_8,
    MIP_LEVELS_10,
    MIP_LEVELS_11,
    MIP_LEVELS_12,
    MIP_LEVELS_MAX // This isn't to be used (use MIP_LEVELS_ALL instead), it is just an enum for creating static tables
                   // etc.
  };

  // Create texture with desired height, width and format.
  TextureClass(unsigned width, unsigned height, WW3DFormat format, MipCountType mip_level_count = MIP_LEVELS_ALL,
               PoolType pool = POOL_MANAGED, bool rendertarget = false);

  // Create texture from a file. If format is specified the texture is converted to that format.
  // Note that the format must be supported by the current device and that a texture can't exist
  // in the system with the same name in multiple formats.
  TextureClass(const char *name, const char *full_path = NULL, MipCountType mip_level_count = MIP_LEVELS_ALL,
               WW3DFormat texture_format = WW3D_FORMAT_UNKNOWN, bool allow_compression = true);

  // Create texture from a surface.
  TextureClass(SurfaceClass *surface, MipCountType mip_level_count = MIP_LEVELS_ALL);

  TextureClass(DX_IDirect3DTexture *d3d_texture);

  virtual ~TextureClass(void);

  // Names
  void Set_Texture_Name(const char *name);
  void Set_Full_Path(const char *path) { FullPath = path; }
  const StringClass &Get_Texture_Name(void) const { return Name; }
  const StringClass &Get_Full_Path(void) const {
    if (FullPath.Is_Empty())
      return Name;
    return FullPath;
  }

  unsigned Get_ID() const { return texture_id; } // Each textrure has a unique id

  // The number of Mip levels in the texture
  unsigned int Get_Mip_Level_Count(void);

  // Note! Width and Height may be zero and may change if texture uses mipmaps
  int Get_Width() { return Width; }
  int Get_Height() { return Height; }

  void Init();

  // Time, after which the texture is invalidated if not used. Set to zero to indicate infinite.
  // Time is in milliseconds.
  void Set_Inactivation_Time(unsigned time) { InactivationTime = time; }
  int Get_Inactivation_Time() const { return InactivationTime; }

  // Get the surface of one of the mipmap levels (defaults to highest-resolution one)
  SurfaceClass *Get_Surface_Level(unsigned int level = 0);
  DX_IDirect3DSurface *Get_D3D_Surface_Level(unsigned int level = 0);

  // Texture priority affects texture management and caching.
  unsigned int Get_Priority(void);
  unsigned int Set_Priority(unsigned int priority); // Returns previous priority

  // Filter and MIPmap settings:
  FilterType Get_Min_Filter(void) const { return TextureMinFilter; }
  FilterType Get_Mag_Filter(void) const { return TextureMagFilter; }
  FilterType Get_Mip_Mapping(void) const { return MipMapFilter; }
  void Set_Min_Filter(FilterType filter) { TextureMinFilter = filter; }
  void Set_Mag_Filter(FilterType filter) { TextureMagFilter = filter; }
  void Set_Mip_Mapping(FilterType mipmap);

  // Texture address mode
  TxtAddrMode Get_U_Addr_Mode(void) const { return UAddressMode; }
  TxtAddrMode Get_V_Addr_Mode(void) const { return VAddressMode; }
  void Set_U_Addr_Mode(TxtAddrMode mode) { UAddressMode = mode; }
  void Set_V_Addr_Mode(TxtAddrMode mode) { VAddressMode = mode; }

  // Debug utility functions for returning the texture memory usage
  unsigned Get_Texture_Memory_Usage() const;
  bool Is_Initialized() const { return Initialized; }
  bool Is_Lightmap() const { return IsLightmap; }
  bool Is_Procedural() const { return IsProcedural; }

  static int _Get_Total_Locked_Surface_Size();
  static int _Get_Total_Texture_Size();
  static int _Get_Total_Lightmap_Texture_Size();
  static int _Get_Total_Procedural_Texture_Size();
  static int _Get_Total_Locked_Surface_Count();
  static int _Get_Total_Texture_Count();
  static int _Get_Total_Lightmap_Texture_Count();
  static int _Get_Total_Procedural_Texture_Count();

  // This needs to be called after device has been created
  static void _Init_Filters(TextureFilterMode texture_filter);

  static void _Set_Default_Min_Filter(FilterType filter);
  static void _Set_Default_Mag_Filter(FilterType filter);
  static void _Set_Default_Mip_Filter(FilterType filter);

  // This utility function processes the texture reduction (used during rendering)
  void Invalidate();

  DX_IDirect3DTexture *Peek_DX8_Texture() { return D3DTexture; }

  bool Is_Missing_Texture();

  // Support for self managed textures
  bool Is_Dirty() {
    WWASSERT(Pool == POOL_DEFAULT);
    return Dirty;
  };
  void Clean() { Dirty = false; };

  unsigned Get_Reduction() const;
  WW3DFormat Get_Texture_Format() const { return TextureFormat; }
  bool Is_Compression_Allowed() const { return IsCompressionAllowed; }

  // Inactivate textures that haven't been used in a while. Pass zero to use textures'
  // own inactive times (default). In urgent need to free up texture memory, try
  // calling with relatively small (just few seconds) time override to free up everything
  // but the currently used textures.
  static void Invalidate_Old_Unused_Textures(unsigned inactive_time_override);

private:
  // Apply this texture's settings into D3D
  void Apply(unsigned int stage);
  void Load_Locked_Surface();

  // Apply a Null texture's settings into D3D
  static void Apply_Null(unsigned int stage);

  // State not contained in the Direct3D texture object:
  FilterType TextureMinFilter;
  FilterType TextureMagFilter;
  FilterType MipMapFilter;
  TxtAddrMode UAddressMode;
  TxtAddrMode VAddressMode;

  // Direct3D texture object
  DX_IDirect3DTexture *D3DTexture;
  bool Initialized;

  // Name
  StringClass Name;
  StringClass FullPath;

  // Unique id
  unsigned texture_id;

  // NOTE: Since "texture wrapping" (NOT TEXTURE WRAP MODE - THIS IS
  // SOMETHING ELSE) is a global state that affects all texture stages,
  // and this class only affects its own stage, we will not worry about
  // it for now. Later (probably when we implement world-oriented
  // environment maps) we will consider where to put it.

  // For debug purposes the texture sets this true if it is a lightmap texture
  bool IsLightmap;
  bool IsProcedural;
  bool IsCompressionAllowed;

  unsigned InactivationTime;         // In milliseconds
  unsigned ExtendedInactivationTime; // This is set by the engine, if needed
  unsigned LastInactivationSyncTime;
  unsigned LastAccessed;
  WW3DFormat TextureFormat;

  int Width;
  int Height;

  // Support for self-managed textures

  PoolType Pool;
  bool Dirty;

public:
  MipCountType MipLevelCount;

private:
  friend class TextureLoadTaskClass;
  TextureLoadTaskClass *TextureLoadTask;

  // kind of a crazy merge point not sure if the public should have
  // been above the ThumbnailLoadTask or not.
  TextureLoadTaskClass *ThumbnailLoadTask;

public:
  // Background texture loader will call this when texture has been loaded
  void Apply_New_Surface(DX_IDirect3DTexture *tex,
                         bool initialized); // If the parameter is true, the texture will be flagged as initialised
};

// Utility functions for loading and saving texture descriptions from/to W3D files
TextureClass *Load_Texture(ChunkLoadClass &cload);
void Save_Texture(TextureClass *texture, ChunkSaveClass &csave);

#endif // TEXTURE_H
