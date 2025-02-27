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
 *                     $Archive:: /Commando/Code/Tools/LevelEdit/StringPicker.h               $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 1/22/01 3:09p                                               $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __STRINGPICKER_H
#define __STRINGPICKER_H

#include "picker.h"


/////////////////////////////////////////////////////////////////////////
//	Forward declarations
/////////////////////////////////////////////////////////////////////////
class PresetClass;


/////////////////////////////////////////////////////////////////////////
//
//	StringPickerClass
//
/////////////////////////////////////////////////////////////////////////
class StringPickerClass : public PickerClass
{
public:

	//////////////////////////////////////////////////////////
	//	Public constructors/destructors
	//////////////////////////////////////////////////////////
	StringPickerClass (void);
	virtual ~StringPickerClass (void);

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
	void				Set_Entry (int entry_id);
	int				Get_Entry (void) const					{ return m_EntryID; }

protected:

	//////////////////////////////////////////////////////////
	//	Protected member data
	//////////////////////////////////////////////////////////
	int				m_EntryID;
};


#endif //__STRINGPICKER_H

