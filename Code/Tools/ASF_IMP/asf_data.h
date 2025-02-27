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

//----------------------------------------------------------------------------
// Axes
//----------------------------------------------------------------------------

enum Axis_Names
{
	ROTATE_X,
	ROTATE_Y,
	ROTATE_Z,
	TRANSLATE_X,
	TRANSLATE_Y,
	TRANSLATE_Z,
	TRANSLATE_LENGTH
};

//----------------------------------------------------------------------------
// ASF_Data_Chunk
//----------------------------------------------------------------------------

struct ASF_Data_Chunk
{
	ASF_Data_Chunk () : Number_of_axes (0) {}
	void add_axis ( Axis_Names new_axis )
	{
		if ( Number_of_axes < 7 )
		{
			Axis [Number_of_axes] = new_axis;
			++ Number_of_axes;
		}
	}

	unsigned	Number_of_axes;
	Axis_Names	Axis [ 7 ];
};

//----------------------------------------------------------------------------
// Position_Key_Scale_Chunk
//----------------------------------------------------------------------------

struct Position_Key_Scale_Chunk
{
	float Position_Key_Scale;
};
