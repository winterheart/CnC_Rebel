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
 *                 Project Name : LevelEdit                                                    *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/Tools/LevelEdit/PresetPicker.h               $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 6/16/00 4:11p                                               $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __PRESETPICKER_H
#define __PRESETPICKER_H

#include "picker.h"


/////////////////////////////////////////////////////////////////////////
//	Forward declarations
/////////////////////////////////////////////////////////////////////////
class PresetClass;


/////////////////////////////////////////////////////////////////////////
//
//	PresetPickerClass
//
/////////////////////////////////////////////////////////////////////////
class PresetPickerClass : public PickerClass
{
public:

	//////////////////////////////////////////////////////////
	//	Public constructors/destructors
	//////////////////////////////////////////////////////////
	PresetPickerClass (void);
	virtual ~PresetPickerClass (void);

	//////////////////////////////////////////////////////////
	//	Public methods
	//////////////////////////////////////////////////////////

	//
	//	Base class overrides
	//
	void				On_Pick (void);

	//
	//	Selection management
	//
	void				Set_Preset (PresetClass *preset);
	PresetClass *	Get_Preset (void) const					{ return m_Preset; }

	//
	//	Content management
	//
	void				Set_Class_ID (int class_id)			{ m_ClassID = class_id; }
	void				Set_Icon_Index (int index)				{ m_IconIndex = index; }

protected:

	//////////////////////////////////////////////////////////
	//	Protected member data
	//////////////////////////////////////////////////////////
	PresetClass *	m_Preset;
	int				m_ClassID;
	int				m_IconIndex;
};


#endif //__PRESETPICKER_H

