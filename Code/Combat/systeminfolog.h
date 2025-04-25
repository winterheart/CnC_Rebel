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
 *                 Project Name : Combat
 **
 *                                                                                             *
 *                     $Archive:: /Commando/Code/Combat/systeminfolog.h          $*
 *                                                                                             *
 *                       Author:: Jani Penttinen                                               *
 *                                                                                             *
 *                     $Modtime:: 12/04/01 11:00a                                             $*
 *                                                                                             *
 *                    $Revision:: 4                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#include "always.h"
#include "wwstring.h"

#ifndef __SYSTEM_INFO_LOG_H
#define __SYSTEM_INFO_LOG_H

class SystemInfoLog {
public:
  static void Set_Current_Level(const char *level_name);
  static void Set_State_Loading();
  static void Set_State_Playing();
  static void Set_State_Exiting();
  static void Reset_State();
  static void Record_Loading_Time(unsigned time_in_seconds);
  static void Record_Frame();

  static void Get_Log(StringClass &string);
  static void Get_Compact_Log(StringClass &string);

private:
  static void Get_Final_String(StringClass &string);
};

// This stuff should go to the playerinfolog...
class PlayerDataClass;

class PlayerInfoLog {
public:
  static void Append_To_Log(PlayerDataClass *data);
  static void Set_Current_Map_Name(const char *map_name);
  static void Get_Compact_Log(StringClass &string);

  static void Report_Tally_Size(int type, int size);
};

#endif
