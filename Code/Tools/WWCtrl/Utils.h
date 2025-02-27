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

//////////////////////////////////////////////////////////////////////////////////////////
//
//	Utils.H
//
//

#ifndef __UTILS_H
#define __UTILS_H


/////////////////////////////////////////////////////////////////////////////
//
// Prototypes
//
void		Frame_Rect (UCHAR *pbits, const RECT &rect, COLORREF color, int scanline_size);
void		Draw_Vert_Line (UCHAR *pbits, int x, int y, int len, COLORREF color, int scanline_size);
void		Draw_Horz_Line (UCHAR *pbits, int x, int y, int len, COLORREF color, int scanline_size);
void		Draw_Sunken_Rect (UCHAR *pbits, const RECT &rect, int scanline_size);
void		Draw_Raised_Rect (UCHAR *pbits, const RECT &rect, int scanline_size);

#endif //__UTILS_H

