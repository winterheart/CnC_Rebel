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
 *                     $Archive:: /Commando/Code/Commando/donateevent.h                           $*
 *                                                                                             *
 *                      $Author:: Tom_s                                                       $*
 *                                                                                             *
 *                     $Modtime:: 12/06/01 5:13p                                              $*
 *                                                                                             *
 *                    $Revision:: 1                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef __DONATEEVENT_H__
#define __DONATEEVENT_H__

#include "netevent.h"
#include "netclassids.h"

//-----------------------------------------------------------------------------
//
// A C->S mirrored object for money donations to teammates.
//
class cDonateEvent : public cNetEvent {
public:
  cDonateEvent(void);

  void Init(int amount, int recipient_id);

  virtual void Export_Creation(BitStreamClass &packet);
  virtual void Import_Creation(BitStreamClass &packet);

  virtual uint32 Get_Network_Class_ID(void) const { return NETCLASSID_DONATEEVENT; }

  static const int Get_Minimum_Acceptable_Donation(void) { return MinimumAcceptableDonation; }

private:
  virtual void Act(void);

  int SenderId;
  int Amount;
  int RecipientId;
  static const int MinimumAcceptableDonation;
};

//-----------------------------------------------------------------------------

#endif // __DONATEEVENT_H__
