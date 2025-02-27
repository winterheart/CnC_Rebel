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
*
* DESCRIPTION
*
* PROGRAMMER
*     Denzil E. Long, Jr.
*
* VERSION INFO
*     $Author: Byon_g $
*     $Revision: 5 $
*     $Modtime: 10/30/00 6:49p $
*     $Archive: /Commando/Code/Scripts/ScriptFactory.h $
*
******************************************************************************/

#ifndef _SCRIPTFACTORY_H_
#define _SCRIPTFACTORY_H_

class ScriptImpClass;
class ScriptRegistrar;

class ScriptFactory
	{
	public:
		virtual ~ScriptFactory();

		// Retrieve the name of this ScriptFactory
		const char* GetName(void);

		// Retrieve the parameter description for this ScriptFactory
		const char* GetParamDescription(void);

		// Create and instance of this Script
		virtual ScriptImpClass* Create(void) = 0;

	protected:
		friend class ScriptRegistrar;

		ScriptFactory(const char* name, const char* param);

		// Retrieve next node
		ScriptFactory* GetNext(void) const;

		// Set next node
		void SetNext(ScriptFactory* link);

	private:
		ScriptFactory* mNext;
		const char * ScriptName;
		const char * ParamDescription;
	};

#endif // _SCRIPTFACTORY_H_
