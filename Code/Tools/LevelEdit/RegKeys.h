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
 *                 Project Name : LevelEdit                                                    *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/Tools/LevelEdit/RegKeys.h               $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 1/24/02 11:52a                                              $*
 *                                                                                             *
 *                    $Revision:: 6                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __REGKEYS_H
#define __REGKEYS_H

////////////////////////////////////////////////////////////////////////////
//
//	Constants
//
////////////////////////////////////////////////////////////////////////////
const TCHAR *const CONFIG_KEY = TEXT("Config");
const TCHAR *const ASSET_DIR_VALUE = TEXT("Asset Tree");
const TCHAR *const VSSDB_VALUE = TEXT("VSS Database");
const TCHAR *const SHOW_WELCOME_VALUE = TEXT("Show Welcome");
const TCHAR *const CHECKIN_STYLE_VALUE = TEXT("Checkin Style");
const TCHAR *const LAST_EXPORT_DIR_VALUE = TEXT("Last export dir");
const TCHAR *const LAST_SAVE_DIR_VALUE = TEXT("Last save dir");
const TCHAR *const LAST_UPDATE_VALUE = TEXT("Last Asset Update");
const TCHAR *const TEMP_ID_VALUE = TEXT("TempID");
const TCHAR *const NODE_ID_START_VALUE = TEXT("NodeIDStart");
const TCHAR *const IMMEDIATE_CHECKIN_VALUE = TEXT("Immed Preset Checkin");
const TCHAR *const TEXTURE_COMPRESSION_VALUE = TEXT("Texture Compression");
const TCHAR *const CURRENT_PACKAGE_NAME = TEXT("Asset Package");

#endif //__REGKEYS_H
