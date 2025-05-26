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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : LevelEdit
 **
 *                                                                                             *
 *                     $Archive:: /Commando/Code/Tools/LevelEdit/TGAToDXT.cpp       $*
 *                                                                                             *
 *                       Author:: Ian Leslie			                                            *
 *                                                                                             *
 *                     $Modtime:: 8/29/01 5:35p                                               $*
 *                                                                                             *
 *                    $Revision:: 4                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include <algorithm>

#include "StdAfx.h"
#include "crnlib.h"
#include "TGAToDXT.H"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Singletons.
TGAToDXTClass _TGAToDXTConverter;

///////////////////////////////////////////////////////////////////////////////
//
//	TGAToDXTClass
//
///////////////////////////////////////////////////////////////////////////////
TGAToDXTClass::TGAToDXTClass() : WriteTimePtr(nullptr), BufferSize(1024), BufferCount(0) {
  Buffer = new unsigned char[BufferSize];
  ASSERT(Buffer != nullptr);
}

///////////////////////////////////////////////////////////////////////////////
//
//	~TGAToDXTClass
//
///////////////////////////////////////////////////////////////////////////////
TGAToDXTClass::~TGAToDXTClass() {
  // Clean-up.
  delete[] Buffer;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Convert
//
///////////////////////////////////////////////////////////////////////////////
bool TGAToDXTClass::Convert(const char *inputpathname, const char *outputpathname, FILETIME *writetimeptr,
                            bool &redundantalpha) {
  WriteTimePtr = writetimeptr;
  redundantalpha = false;

  bool success = false;

  int width, height, channels;
  unsigned char *buffer = stbi_load(inputpathname, &width, &height, &channels, STBI_rgb_alpha);
  if (buffer) {
    // Check that the targa is in the right format.
    // In order to be valid it must adhere to the following:
    // 1. Pixel depth must be 24 or 32 (compressor has no support for lower bit depths).
    // (N.B.: WH: Actually, crunch/stb_image may support other TGA formats)
    // 2. Dimensions >= 4 (DDS block size is 4x4).
    // 3. Aspect ratio <= 1:8 (some H/W will not render textures above this ratio).
    // 4. Dimensions must be power of 2 (see below).
    bool validbitdepth = (channels == 3) || (channels == 4);
    bool validsize = (width >= 4) && (height >= 4);
    bool validaspect = static_cast<float>(std::max(width, width)) / static_cast<float>(std::min(width, height)) <= 8.0f;

    // Analyse the alpha channel and ignore it if it contains redundant data (ie. is either all black or all white).
    /*
    unsigned char *byte = buffer;
    if ((*(byte + 3) == 0x00) || (*(byte + 3) == 0xff)) {
      channels = 3;
    }
    */

    if (validbitdepth && validsize && validaspect) {
      crn_comp_params comp_params;
      comp_params.m_width = width;
      comp_params.m_height = width;
      comp_params.set_flag(cCRNCompFlagHierarchical, false);
      comp_params.m_file_type = cCRNFileTypeDDS;
      comp_params.m_format = channels == 3 ? cCRNFmtDXT1 : cCRNFmtDXT5;
      comp_params.m_pImages[0][0] = reinterpret_cast<crn_uint32 *>(buffer);

      crn_mipmap_params mip_params;
      // mip_params.m_gamma_filtering = true;
      mip_params.m_mode = cCRNMipModeGenerateMips;
      mip_params.m_min_mip_size = 4;

      uint32_t output_file_size;
      void *output_file_data = crn_compress(comp_params, mip_params, output_file_size);
      stbi_image_free(buffer);

      if (output_file_data) {
        DWORD bytecountwritten;

        HANDLE hfile =
            ::CreateFile(outputpathname, GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, 0L, nullptr);
        if (hfile != INVALID_HANDLE_VALUE) {
          LockFile(hfile, 0, 0, output_file_size, 0);
          WriteFile(hfile, output_file_data, output_file_size, &bytecountwritten, nullptr);
          UnlockFile(hfile, 0, 0, output_file_size, 0);

          // Stamp the write time (if one has been supplied).
          if (WriteTimePtr != nullptr) {
            SetFileTime(hfile, nullptr, nullptr, WriteTimePtr);
          }

          CloseHandle(hfile);
        }

        crn_free_block(output_file_data);
        success = true;
      }
    }
  }

  return success;
}
