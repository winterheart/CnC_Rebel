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
// Filename:     msgstatlist.h
// Project:
// Author:       Tom Spencer-Smith
// Date:
// Description:  Collection of message stats for all message types
//
//-----------------------------------------------------------------------------
#pragma once

#ifndef MSGSTATLIST_H
#define MSGSTATLIST_H

#include "msgstat.h"

//-----------------------------------------------------------------------------
class cMsgStatList {
public:
  cMsgStatList(const cMsgStatList &source) = delete;            // disallow
  cMsgStatList &operator=(const cMsgStatList &source) = delete; // disallow

  cMsgStatList();
  ~cMsgStatList();

  enum { ALL_MESSAGES = -1 };

  void Init(int num_stats);

  void Increment_Num_Msg_Sent(int message_type, int increment = 1) const;
  void Increment_Num_Byte_Sent(int message_type, int increment) const;
  void Increment_Num_Msg_Recd(int message_type, int increment = 1) const;
  void Increment_Num_Byte_Recd(int message_type, int increment) const;

  DWORD Get_Num_Msg_Sent(int message_type) const;
  DWORD Get_Num_Byte_Sent(int message_type) const;
  DWORD Get_Num_Msg_Recd(int message_type) const;
  DWORD Get_Num_Byte_Recd(int message_type) const;

  DWORD Compute_Avg_Num_Byte_Sent(int message_type) const;
  DWORD Compute_Avg_Num_Byte_Recd(int message_type) const;

  cMsgStat &Get_Stat(int message_type) const;
  int Get_Num_Stats() const { return NumStats; }

  void Set_Name(int message_type, LPCSTR name) const;
  LPCSTR Get_Name(int message_type) const;

private:
  cMsgStat *PStat;
  int NumStats;
};

//-----------------------------------------------------------------------------

#endif // MSGSTATLIST_H
