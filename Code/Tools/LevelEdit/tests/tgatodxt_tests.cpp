/*
 * 	Command & Conquer Renegade(tm)
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

#include <filesystem>
#include <gtest/gtest.h>

#include "rawfile.h"
#include "realcrc.h"
#include "TGAToDXT.H"

TEST(REBEL, TGAToDXT_Convert) {

  std::vector<std::pair<std::filesystem::path, uint32_t>> files = {
    {"vga-rgb.tga", 0x1A1645CD},  // RGB 512 x 512 x 24 -> DXT1
    {"vga-rgba.tga", 0x47DE9A22}  // RGBA 512 x 512 x 32 - 8-bit alpha -> DXT5
  };
  std::filesystem::path temp = std::filesystem::temp_directory_path();

  for (const auto& file : files) {
    std::filesystem::path out_file = (temp / file.first).replace_extension(".dds");
    bool alpharemoved;
    bool result = _TGAToDXTConverter.Convert(file.first.string().c_str(), out_file.string().c_str(), nullptr, alpharemoved);
    EXPECT_FALSE(alpharemoved);
    EXPECT_TRUE(result);
    RawFileClass crc_file(out_file.string().c_str());
    int32_t size = crc_file.Size();
    unsigned char *buffer = new unsigned char[size];
    crc_file.Read(buffer, size);
    uint32_t crc = CRC_Memory(buffer, size);
    delete[] buffer;

    EXPECT_EQ(crc, file.second);
  }
}
