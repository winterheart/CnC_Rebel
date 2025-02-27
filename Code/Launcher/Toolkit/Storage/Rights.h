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

/****************************************************************************
*
* FILE
*     $Archive: /Commando/Code/Launcher/Toolkit/Storage/Rights.h $
*
* DESCRIPTION
*     Access privilege definitions.
*
* PROGRAMMER
*     Denzil E. Long, Jr.
*     $Author: Denzil_l $
*
* VERSION INFO
*     $Modtime: 9/23/00 6:19p $
*     $Revision: 1 $
*
****************************************************************************/

#ifndef RIGHTS_H
#define RIGHTS_H

// Access rights
typedef enum
	{
	Rights_ReadOnly = 0,
	Rights_WriteOnly,
	Rights_ReadWrite,
	} ERights;

#endif // RIGHTS_H
