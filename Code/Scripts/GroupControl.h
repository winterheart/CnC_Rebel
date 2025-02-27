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
*     GroupControl.h
*
* DESCRIPTION
*     Group controller definitions
*
* PROGRAMMER
*     Denzil E. Long, Jr.
*
* VERSION INFO
*     $Author: Pat_p $
*     $Revision: 2 $
*     $Modtime: 4/26/00 10:32a $
*     $Archive: /Commando/Code/Scripts/GroupControl.h $
*
******************************************************************************/

#ifndef _GROUPCONTROL_H_
#define _GROUPCONTROL_H_

#include "scripts.h"
#include "slist.h"

class Group;

class GroupController
	{
	public:
		// Retrieve pointer to the GroupController
		static GroupController* Instance(void);

		GroupController();
		~GroupController();

		// Find a Group with the specified name.
		Group* FindGroup(const char* groupName);

		// Add a GameObject to the specified Group.
		bool AddToGroup(const char* groupName, GameObject* object);

		// Remove a GameObject from the specified Group,
		void RemoveFromGroup(const char* groupName, GameObject* object);

		// Send a Group a custom event.
		void SendGroupCustomEvent(const char* groupName, GameObject* from,
			int command, int data);

	protected:
		// Create a Group with the specified name.
		Group* FindOrCreateGroup(const char* groupName);

	private:
		// Instance pointer to GroupController
		static GroupController* _mInstance;

		// List of groups
		SList<Group> mGroups;
	};

#endif // _GROUPCONTROL_H_
