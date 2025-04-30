/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**	Copyright 2025 CnC Rebel Developers.
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
 *                 Project Name : WWSaveLoad                                                   *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwsaveload/definitionfactory.h               $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 2/22/01 6:18p                                               $*
 *                                                                                             *
 *                    $Revision:: 9                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "always.h"
#include "bittype.h"
#include "definitionclassids.h"

// Forward declarations
class DefinitionClass;

//////////////////////////////////////////////////////////////////////////////////
//
//	DefinitionFactoryClass
//
//	Definition factories act as virtual constructors for object definitions.  They
//	are responsible for creating new definitions for a particular class of objects.
//
//////////////////////////////////////////////////////////////////////////////////
class DefinitionFactoryClass {
public:
  //////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  //////////////////////////////////////////////////////////////
  DefinitionFactoryClass();
  virtual ~DefinitionFactoryClass();

  //////////////////////////////////////////////////////////////
  //	Public methods
  //////////////////////////////////////////////////////////////
  virtual DefinitionClass *Create() const = 0;
  virtual const char *Get_Name() const = 0;
  virtual uint32 Get_Class_ID() const = 0;
  virtual bool Is_Displayed() const = 0;

protected:
  //////////////////////////////////////////////////////////////
  //	Protected member data
  //////////////////////////////////////////////////////////////
  DefinitionFactoryClass *m_NextFactory;
  DefinitionFactoryClass *m_PrevFactory;

  //////////////////////////////////////////////////////////////
  //	Friends
  //////////////////////////////////////////////////////////////
  friend class DefinitionFactoryMgrClass;
};
