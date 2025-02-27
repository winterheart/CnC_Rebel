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
*     $Archive: /Commando/Code/Tests/BitPackTest/Code/TypeEncoder.h $
*
* DESCRIPTION
*
* PROGRAMMER
*     Denzil E. Long, Jr.
*
* VERSION INFO
*     $Author: Denzil_l $
*     $Revision: 2 $
*     $Modtime: 5/31/00 9:23a $
*
****************************************************************************/

#ifndef _TYPEENCODER_H_
#define _TYPEENCODER_H_

#include "bitpacker.h"

class TypeEncoder : public BitPacker
	{
	public:
		typedef enum
			{
			X_POSITION = 0,
			Y_POSITION,
			Z_POSITION,
			MAX_ENCODERTYPES
			} EncoderType;

		// Set the type precision based on a desired resolution
		static void SetTypePrecision(EncoderType type, float min, float max,
			float resolution);

		// Set the type precision based on desired bit width.
		static void SetTypePrecision(EncoderType type, float min, float max,
			unsigned int bitPrecision);

		TypeEncoder(void* buffer, unsigned int size);
		~TypeEncoder();

		// Retrieve a boolean value (1 bit)
		bool GetBool(void);

		// Write a boolean value (1 bit)
		bool PutBool(bool value);

		// Retrieve an integer
		int GetInt(unsigned int bitPrecision);

		// Write an integer with specified bit precision
		bool PutInt(int value, unsigned int bitPrecision);

		// Retrieve a floating point value
		float GetFloat(float min, float max, float resolution);

		// Write a floating point value
		bool PutFloat(float value, float min, float max, float resolution);

		// Retrieve a value of specified type
		float GetType(EncoderType type);

		// Write a value of specified type
		bool PutType(EncoderType type, float value);

	private:
		// Calculate the number of bits required to encode a value. (Internal use)
		static unsigned int CalcBitPrecision(float min, float max, float resolution);

		// Calculate the minimum resolution possible with given bit width.(Internal use)
		static float CalcResolution(float min, float max, unsigned int bitPrecision);

		typedef struct
			{
			EncoderType Type;
			float MinExtent;
			float MaxExtent;
			float Resolution;
			unsigned int BitPrecision;
			} EncoderTypeEntry;

		static EncoderTypeEntry _mEncoderTypes[MAX_ENCODERTYPES];
	};

#endif // _TYPEENCODER_H_
