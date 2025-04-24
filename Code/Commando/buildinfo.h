/*
**	Command & Conquer Renegade(tm)
**      Copyright 2025 CnC Rebel Developers.
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

#pragma once

#include <cstdint>
#include <string>

namespace REBEL {

class BuildInfo {
private:
  static uint32_t version_major;
  static uint32_t version_minor;
  static uint32_t version_patch;

  static const char * codename;
  static const char * hash;

public:

  /**
   * Get version components
   * @param major output variable for version_major
   * @param minor output variable for version_minor
   * @param patch output variable for version_patch
   */
  static void Get_Version(uint32_t &major, uint32_t &minor, uint32_t &patch);

  /**
   * Get packed version components for comparison.
   * @return collated version
   */
  static uint32_t Get_Version_Packed();

  /**
   * Get human-readable build info (version, codename and build hash)
   * @return formatted string result
   */
  static const char * Get_Build_Info_String();

  /**
   * Get hash
   * @return hash name
   */
  static const char * Get_Hash();

  /**
   * Get codename
   * @return codename
   */
  static const char * Get_Codename();

};

} // namespace REBEL
