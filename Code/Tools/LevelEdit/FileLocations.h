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
 *                     $Archive:: /Commando/Code/Tools/LevelEdit/FileLocations.h              $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 1/31/02 1:56p                                               $*
 *                                                                                             *
 *                    $Revision:: 24                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __FILE_LOCATIONS_H
#define __FILE_LOCATIONS_H

///////////////////////////////////////////////////////////////////////////////////////
//
//	Constants
//
///////////////////////////////////////////////////////////////////////////////////////
const TCHAR *const ALWAYS_INI_PATH = TEXT("INI\\Always.ini");
const TCHAR *const PRESET_INI_PATH = TEXT("INI\\GlobalPresetLib.INI");
const TCHAR *const PROPERTY_INI_PATH = TEXT("INI\\PropertyPresets.INI");
const TCHAR *const SERIAL_INI_PATH = TEXT("INI\\Serial.INI");
const TCHAR *const TRANS_INI_PATH = TEXT("INI\\TransitionPresets.INI");
const TCHAR *const UPDATE_INI_PATH = TEXT("INI\\UpdateInfo.INI");
const TCHAR *const TEMP_INI_PATH = TEXT("INI\\TempPresets.INI");
const TCHAR *const ALWAYS_INI_DIR = TEXT("ALWAYS\\INI");
const TCHAR *const ALWAYS_DEP_INI_PATH = TEXT("INI\\always_dep.ini");

const TCHAR *const OBJECTS_DDB_PATH = TEXT("presets\\objects.ddb");

const TCHAR *const TEMP_DB_PATH = TEXT("Presets\\temps20.ddb");
const TCHAR *const TEMP_DB_FILENAME = TEXT("temps20.ddb");
const TCHAR *const PRESETS_PATH = TEXT("Presets");

const TCHAR *const CONV_DB_PATH = TEXT("Presets\\conv10.cdb");
const TCHAR *const CONV_DB_FILENAME = TEXT("conv10.cdb");

const TCHAR *const STRINGS_DB_PATH = TEXT("Always\\TranslationDB\\strings.tdb");
const TCHAR *const STRINGS_DB_NAME = TEXT("strings.tdb");

const TCHAR *const WEATHER_DIR = TEXT("Always\\Weather");
const TCHAR *const SKY_DIR = TEXT("Always\\Sky");
const TCHAR *const DAZZLE_INI_PATH = TEXT("Always\\INI\\Dazzle.ini");
const TCHAR *const SHATTER_DIR = TEXT("Always\\Shatter");

const TCHAR *const COMMAND_ASSET_NAME = TEXT("C_HAVOC");
const TCHAR *const CHAR_ANIMS_PATH = TEXT("Always\\Characters\\Anims");
const TCHAR *const DEF_ASSET_PATH = TEXT("Projects\\Commando\\Assets");
const TCHAR *const SCRIPTS_PATH = TEXT("Scripts");

const TCHAR *const HUMAN_SKEL_PATH = TEXT("Characters\\s_a_human.w3d");

const TCHAR *const DEF_VSS_DB =
    TEXT("\\\\mobius\\project7\\projects\\renegade\\asset management\\asset database\\srcsafe.ini");
const TCHAR *const GLOBAL_TEXTURE_PATH = TEXT("\\\\mobius\\project7\\projects\\renegade\\art\\_source\\texturemaps");

const TCHAR *const LEVELS_ASSET_DIR = TEXT("Levels");

#endif //__FILE_LOCATIONS_H
