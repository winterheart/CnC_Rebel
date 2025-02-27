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
 *                     $Archive:: /Commando/Code/wwui/dialogparser.h           $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 10/25/01 3:53p                                              $*
 *                                                                                             *
 *                    $Revision:: 11                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __DIALOG_PARSER_H
#define __DIALOG_PARSER_H

#include "vector.h"
#include "bittype.h"
#include "widestring.h"


////////////////////////////////////////////////////////////////
//	Forward declarations
////////////////////////////////////////////////////////////////
class WideStringClass;


////////////////////////////////////////////////////////////////
//	Constants
////////////////////////////////////////////////////////////////
typedef enum
{
	BUTTON	= 0x0080,
	EDIT,
	STATIC,
	LIST_BOX,
	SCROLL_BAR,
	COMBOBOX,
	SLIDER,
	LIST_CTRL,
	TAB,
	MAP,
	VIEWER,
	HOTKEY,
	SHORTCUT_BAR,
	MERCHANDISE_CTRL,
	TREE_CTRL,
	PROGRESS_BAR,
	HEALTH_BAR
} CONTROL_TYPE;


////////////////////////////////////////////////////////////////
//	Structures
////////////////////////////////////////////////////////////////
typedef struct _ControlDefinitionStruct
{
	int					id;
	CONTROL_TYPE		type;
	uint32				style;
	int					x;
	int					y;
	int					cx;
	int					cy;
	WideStringClass	title;
	
	//
	//	Required by DynamicVectorClass
	//
	bool operator== (const _ControlDefinitionStruct &src) { return false; }
	bool operator!= (const _ControlDefinitionStruct &src) { return true; }

	_ControlDefinitionStruct (void)	:
		id (0),
		type (BUTTON),
		style (0),
		x (0),
		y (0),
		cx (0),
		cy (0)
		{}

} ControlDefinitionStruct;


////////////////////////////////////////////////////////////////
//
//	DialogParserClass
//
////////////////////////////////////////////////////////////////
class DialogParserClass
{
public:

	////////////////////////////////////////////////////////////////
	//	Static methods
	////////////////////////////////////////////////////////////////
	static void	Parse_Template (int res_id, int *dlg_width, int *dlg_height, WideStringClass *dlg_title, DynamicVectorClass<ControlDefinitionStruct> *control_list);
};


#endif //__DIALOG_PARSER_H

