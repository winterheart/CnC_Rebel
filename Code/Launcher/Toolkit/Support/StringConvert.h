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

/******************************************************************************
*
* FILE
*     $Archive: /Commando/Code/Launcher/Toolkit/Support/StringConvert.h $
*
* DESCRIPTION
*     ANSI <-> Unicode string conversions
*
* PROGRAMMER
*     Denzil E. Long, Jr.
*     $Author: Denzil_l $
*
* VERSION INFO
*     $Modtime: 8/18/00 10:07a $
*     $Revision: 1 $
*
******************************************************************************/

#ifndef STRINGCONVERT_H
#define STRINGCONVERT_H

#include "UTypes.h"

class UString;

Char* UStringToANSI(const UString& string, Char* buffer, UInt bufferLength);
Char* UnicodeToANSI(const WChar* string, Char* buffer, UInt bufferLength);

#endif // STRINGCONVERT_H
