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
 ***                            Confidential - Westwood Studios                              ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Commando                                                     *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/Commando/clientgoodbyeevent.h                     $*
 *                                                                                             *
 *                      $Author:: Tom_s                                                       $*
 *                                                                                             *
 *                     $Modtime:: 9/21/01 2:42p                                               $*
 *                                                                                             *
 *                    $Revision:: 2                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef __CLIENTGOODBYEEVENT_H__
#define __CLIENTGOODBYEEVENT_H__

#include "netevent.h"
#include "netclassids.h"

//-----------------------------------------------------------------------------
//
// A C->S mirrored object to represent client destruction
//
class cClientGoodbyeEvent : public cNetEvent {
public:
  cClientGoodbyeEvent(void);

  void Init(void);

  virtual void Export_Creation(BitStreamClass &packet);
  virtual void Import_Creation(BitStreamClass &packet);
  virtual uint32 Get_Network_Class_ID(void) const { return NETCLASSID_CLIENTGOODBYEEVENT; }

private:
  virtual void Act(void);

  int SenderId;
};

//-----------------------------------------------------------------------------

#endif // __CLIENTGOODBYEEVENT_H__
