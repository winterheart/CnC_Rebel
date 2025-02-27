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
 *                     $Archive:: /Commando/Code/Tools/LevelEdit/excel.h        $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 7/26/01 3:34p                                               $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#if defined(_MSC_VER)
#pragma once
#endif


#ifndef __EXCEL_H
#define __EXCEL_H

#include "widestring.h"
#include "wwstring.h"


/////////////////////////////////////////////////////////////////////////
//	Forward declarations
/////////////////////////////////////////////////////////////////////////
class _Application;
class Workbooks;
class _Worksheet;
class _Workbook;
class Range;


/////////////////////////////////////////////////////////////////////////
//
//	ExcelClass
//
/////////////////////////////////////////////////////////////////////////
class ExcelClass
{
public:

	//////////////////////////////////////////////////////////
	//	Public methods
	//////////////////////////////////////////////////////////

	//
	//	Initialization
	//
	static bool		Initialize (void);
	static void		Shutdown (void);

	//
	//	Workbook access
	//
	static void		New_Workbook (const char *template_filename);
	static void		Open_Workbook (const char *filename);
	static void		Save_Workbook (const char *filename);
	static void		Close_Workbook (void);

	//
	//	Cell access
	//
	static bool		Get_String (int row, int col, WideStringClass &value);
	static bool		Set_String (int row, int col, const WideStringClass &value);

	static bool		Get_Int (int row, int col, int &value);
	static bool		Set_Int (int row, int col, int value);

private:

	//////////////////////////////////////////////////////////
	//	Private methods
	//////////////////////////////////////////////////////////
	static void		Select_Active_Sheet (void);
	static bool		Get_Cell (int row, int col, VARIANT &result);
	static bool		Set_Cell (int row, int col, const VARIANT &data);

	//////////////////////////////////////////////////////////
	//	Private member data
	//////////////////////////////////////////////////////////
	static _Application *	Application;
	static Workbooks *		WorkbooksObj;
	static _Worksheet *		WorksheetObj;
	static _Workbook *		WorkbookObj;
	static Range *				RangeObj;
	static StringClass		CurrPath;
};


#endif //__EXCEL_H
