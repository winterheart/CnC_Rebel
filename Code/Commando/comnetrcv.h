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
 *                     $Archive:: /Commando/Code/Commando/comnetrcv.h                          $*
 *                                                                                             *
 *                      $Author:: Steve_t                                                     $*
 *                                                                                             *
 *                     $Modtime:: 9/28/01 5:01p                                               $*
 *                                                                                             *
 *                    $Revision:: 57                                                         $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#if defined(_MSV_VER)
#pragma once
#endif

#ifndef	COMNETRCV_H
#define	COMNETRCV_H

#include "always.h"

class cPacket;

/*
** There functions will be called when corresponding packet types are receicved
*/
class	CombatNetworkReceiver {

public:
	// This may not fit here, but...
	// Server Update function allows the Host to generate any state update packets it wishes.
	virtual bool Server_Update_Dynamic_Objects(bool is_urgent = false)	= 0;
	virtual void Server_Send_Delete_Notifications(void)						= 0;
	virtual bool Client_Update_Dynamic_Objects(bool is_urgent = false)	= 0;
};

#endif // COMNETRCV_H

