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

#include <format>
#include "buildinfo_gen.h"
#include "BuildInfo.h"

namespace REBEL {

uint32_t BuildInfo::version_major = REBEL_VERSION_MAJOR;
uint32_t BuildInfo::version_minor = REBEL_VERSION_MINOR;
uint32_t BuildInfo::version_patch = REBEL_VERSION_PATCH;

const char *BuildInfo::codename = REBEL_CODENAME;
const char *BuildInfo::hash = REBEL_HASH;

void BuildInfo::Get_Version(uint32_t &major, uint32_t &minor, uint32_t &patch) {
  major = version_major;
  minor = version_minor;
  patch = version_patch;
}

uint32_t BuildInfo::Get_Version_Packed() { return (version_major << 16) | version_minor; }

const char *BuildInfo::Get_Build_Info_String() {
  return std::format("v{0}.{1:03d}.{2}  \"{3}\" (build {4})", version_major, version_minor, version_patch, codename,
                     hash)
      .c_str();
}

const char *BuildInfo::Get_Hash() { return hash; }

const char *BuildInfo::Get_Codename() { return codename; }

} // namespace REBEL
