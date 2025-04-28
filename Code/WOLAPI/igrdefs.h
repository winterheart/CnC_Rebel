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

#ifndef _IGRDEFS_H
#define _IGRDEFS_H

//
// Option Bits for Options key
//
#define IGR_NO_AUTO_LOGIN 0x01
#define IGR_NO_STORE_NICKS 0x02
#define IGR_NO_RUN_REG_APP 0x04

#define IGR_ALL IGR_NO_AUTO_LOGIN | IGR_NO_STORE_NICKS | IGR_NO_RUN_REG_APP
#define IGR_NONE 0x00

#endif // _IGDDEFS_H
