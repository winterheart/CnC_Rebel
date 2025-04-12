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
 *                     $Archive:: /Commando/Code/wwui/dialogbutton.h           $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 6/08/01 9:41a                                               $*
 *                                                                                             *
 *                    $Revision:: 5                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __DIALOG_BUTTON_H
#define __DIALOG_BUTTON_H

#include "dialogcontrol.h"
#include "vector3.h"
#include "render2dsentence.h"


////////////////////////////////////////////////////////////////
//
//	DialogButtonClass
//
////////////////////////////////////////////////////////////////
class DialogButtonClass : public DialogControlClass
{
public:

	////////////////////////////////////////////////////////////////
	//	Public constructors/destructors
	////////////////////////////////////////////////////////////////
	DialogButtonClass (void);
	virtual ~DialogButtonClass (void)	{}

	////////////////////////////////////////////////////////////////
	//	Public methods
	////////////////////////////////////////////////////////////////

	//
	//	From DialogControlClass
	//
	void					Render (void);

protected:

	////////////////////////////////////////////////////////////////
	//	Protected methods
	////////////////////////////////////////////////////////////////
	void					On_LButton_Down (const Vector2 &mouse_pos);
	void					On_LButton_Up (const Vector2 &mouse_pos);
	void					On_Mouse_Move (const Vector2 &mouse_pos);
	void					On_Set_Cursor (const Vector2 &mouse_pos);
	void					On_Create (void);
	void					On_Kill_Focus (DialogControlClass *focus);
	bool					On_Key_Down (uint32 key_id, uint32 key_data);

	void					Create_Bitmap_Button (void);
	void					Create_Component_Button (void);
	void					Create_Component_Button2 (void);
	void					Create_Text_Renderers (void);


	////////////////////////////////////////////////////////////////
	//	Protected constants
	////////////////////////////////////////////////////////////////
	enum
	{
		UP				= 0,
		DOWN,
		STATE_MAX
	};

	////////////////////////////////////////////////////////////////
	//	Protected member data
	////////////////////////////////////////////////////////////////
	Render2DSentenceClass	TextRenderers[STATE_MAX];
	Render2DClass				ButtonRenderers[STATE_MAX];
	bool							WasButtonPressedOnMe;
	bool							IsMouseOverMe;
};


#endif //__DIALOG_BUTTON_H
