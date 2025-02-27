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
 *                 Project Name : MathTest                                                     *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/Tests/mathtest/output.cpp                    $*
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 3/02/98 1:58p                                               $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "stdio.h"
#include "stdarg.h"

void Print(const char * format,...)
{
	va_list	va;
	va_start(va, format);
	vprintf(format, va);
	va_end(va);
}

void Print_Title(const char * title)
{
	Print("\n");
	Print("-------------------------------------------------------------------\n");
	Print("%s\n",title);
	Print("-------------------------------------------------------------------\n");
}

void Pass_Message(int num)
{
	Print("test %d passed.\n",num);
}

void Fail_Message(int num)
{
	Print("*** test %d failed! ***\n",num);
}
