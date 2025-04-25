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
 *
 * DESCRIPTION
 *
 * PROGRAMMER
 *     Denzil E. Long, Jr.
 *
 * VERSION INFO
 *     $Author: Denzil_l $
 *     $Revision: 5 $
 *     $Modtime: 4/04/00 11:37a $
 *     $Archive: /Commando/Code/Scripts/ScriptPublisher.h $
 *
 ******************************************************************************/

#ifndef _SCRIPTPUBLISHER_H_
#define _SCRIPTPUBLISHER_H_

#include "slist.h"

class ScriptClass;

class ScriptPublisher {
public:
  // Add a subscriber to the publisher list
  void AddSubscriber(ScriptClass *subscriber);

  // Remove a subscriber from the publisher list
  void RemoveSubscriber(ScriptClass *subscriber);

  // Send subscribers a message
  void NotifySubscribers(int what, int param);

protected:
  // Protected to prevent direct instantiation or deletion
  ScriptPublisher();
  virtual ~ScriptPublisher();

private:
  SList<ScriptClass> mSubscribers;
};

#endif // _SCRIPTPUBLISHER_H_
