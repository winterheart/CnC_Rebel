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
 *                 Project Name : Combat																		  *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwui/tooltipmgr.h          $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 4/09/01 12:08p                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __TOOLTIP_MGR_H
#define __TOOLTIP_MGR_H

#include "vector2.h"
#include "vector3.h"
#include "bittype.h"
#include "rect.h"


////////////////////////////////////////////////////////////////
//	Forward declarations
////////////////////////////////////////////////////////////////
class ToolTipClass;
class DialogControlClass;


////////////////////////////////////////////////////////////////
//
//	ToolTipMgrClass
//
////////////////////////////////////////////////////////////////
class ToolTipMgrClass
{
public:

	////////////////////////////////////////////////////////////////
	//	Public methods
	////////////////////////////////////////////////////////////////

	//
	//	Library management
	//
	static void		Initialize (void);
	static void		Shutdown (void);

	//
	//	Rendering
	//
	static void		Render (void);

	//
	//	Tooltip control
	//
	static void		Reset (void);
	static void		Update (const Vector2 &mouse_pos);

private:

	////////////////////////////////////////////////////////////////
	//	Private member data
	////////////////////////////////////////////////////////////////
	static ToolTipClass *		ToolTip;
	static int						ToolTipDelay;
	static int						DefaultToolTipDelay;
	static bool						ToolTipDisplayed;
	static Vector2					LastMousePos;
	static int						PauseTime;
	static DialogControlClass *CurrentControl;
};


#endif //__TOOLTIP_MGR_H
