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
 *                     $Archive:: /Commando/Code/Commando/cstextobj.h                           $*
 *                                                                                             *
 *                      $Author:: Tom_s                                                       $*
 *                                                                                             *
 *                     $Modtime:: 9/21/01 2:42p                                               $*
 *                                                                                             *
 *                    $Revision:: 4                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef __CSTEXTOBJ_H__
#define __CSTEXTOBJ_H__

#include "netevent.h"
#include "netclassids.h"
#include "wwstring.h"

#include "sctextobj.h"

//-----------------------------------------------------------------------------
//
// A C->S mirrored object for ingame text communications.
//
class cCsTextObj : public cNetEvent {
public:
  cCsTextObj(void);

  void Init(WideStringClass &text, TextMessageEnum type, int sender_id, int recipient);

  virtual void Export_Creation(BitStreamClass &packet);
  virtual void Import_Creation(BitStreamClass &packet);

  virtual uint32 Get_Network_Class_ID(void) const { return NETCLASSID_CSTEXTOBJ; }

private:
  virtual void Act(void);

  int SenderId;
  TextMessageEnum Type;
  WideStringClass Text;
  int Recipient;
};

//-----------------------------------------------------------------------------

#endif // __CSTEXTOBJ_H__
