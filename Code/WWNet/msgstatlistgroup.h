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

//
// Filename:     msgstatlistgroup.h
// Project:
// Author:       Tom Spencer-Smith
// Date:
// Description:  Collection of msgstatlists. The server will need one
//               of these to sum send and receive data to multiple clients.
//
//-----------------------------------------------------------------------------
#pragma once

#ifndef MSGSTATLISTGROUP_H
#define MSGSTATLISTGROUP_H

#include "msgstatlist.h"

//-----------------------------------------------------------------------------
class cMsgStatListGroup {
public:
  cMsgStatListGroup(const cMsgStatListGroup &source) = delete;            // disallow
  cMsgStatListGroup &operator=(const cMsgStatListGroup &source) = delete; // disallow

  cMsgStatListGroup();
  ~cMsgStatListGroup();

  void Init(int num_lists, int num_stats);

  enum { ALL_LISTS = -1 };
  enum { ALL_MESSAGES = -1 };

  void Increment_Num_Msg_Sent(int list_num, int message_type, int increment = 1) const;
  void Increment_Num_Byte_Sent(int list_num, int message_type, int increment) const;
  void Increment_Num_Msg_Recd(int list_num, int message_type, int increment = 1) const;
  void Increment_Num_Byte_Recd(int list_num, int message_type, int increment) const;

  DWORD Get_Num_Msg_Sent(int list_num, int message_type) const;
  DWORD Get_Num_Byte_Sent(int list_num, int message_type) const;
  DWORD Get_Num_Msg_Recd(int list_num, int message_type) const;
  DWORD Get_Num_Byte_Recd(int list_num, int message_type) const;

  DWORD Compute_Avg_Num_Byte_Sent(int list_num, int message_type) const;
  DWORD Compute_Avg_Num_Byte_Recd(int list_num, int message_type) const;

  cMsgStatList *Get_Stat_List(int list_num) const;

  void Set_Name(int message_type, LPCSTR name) const;
  // LPCSTR	Get_Name(int message_type) const;

private:
  cMsgStatList *PStatList;
  int NumLists;
};

//-----------------------------------------------------------------------------

#endif // MSGSTATLISTGROUP_H
