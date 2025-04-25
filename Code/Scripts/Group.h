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

/******************************************************************************
 *
 * FILE
 *     Group.h
 *
 * DESCRIPTION
 *     Group definitions
 *
 * PROGRAMMER
 *     Denzil E. Long, Jr.
 *
 * VERSION INFO
 *     $Author: Denzil_l $
 *     $Revision: 1 $
 *     $Modtime: 4/17/00 9:42a $
 *     $Archive: /Commando/Code/Scripts/Group.h $
 *
 ******************************************************************************/

#ifndef _GROUP_H_
#define _GROUP_H_

#include "scripts.h"
#include "vector.h"

// Group event identifiers
typedef enum {
  GROUP_MEMBER_DAMAGED = 1,
  GROUP_MEMBER_KILLED,
  GROUP_MEMBER_HEARD,
  GROUP_MEMBER_SAW,
} GroupEvent;

// Group event information.
//
// A pointer to this structure is sent as a data parameter when the custom
// event SCMD_GROUP_EVENT is sent to an object.
typedef struct GroupEventInfoTag {
  const char *GroupName;
  GroupEvent Event;

  union {
    GameObject *Object;
    const CombatSound *Sound;
  };
} GroupEventInfo;

class GroupController;

class Group {
public:
  // Retrieve Team name
  const char *GetName(void) const;

  // Add a GameObject to the team.
  void AddMember(GameObject *object);

  // Remove a GameObject from the team.
  void RemoveMember(GameObject *object);

  // Check if a GameObject is a member of the team.
  bool IsMember(GameObject *object) const;

  // Get the number of members in the team.
  int MemberCount(void) const;

  // Get a team member.
  GameObject *GetMember(int index);

  // Send a command to all the members of the team.
  void SendCustomEvent(GameObject *from, int event, int data);

protected:
  // Only the TeamController can create and delete Teams
  friend class GroupController;
  Group(const char *name);
  ~Group();

private:
  char mName[64];
  DynamicVectorClass<GameObject *> mMembers;
};

#endif // _GROUP_H_
