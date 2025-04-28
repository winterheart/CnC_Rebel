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
 *                     $Archive:: /Commando/Code/wwsaveload/parameterlist.h                   $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 10/06/99 2:52p                                              $*
 *                                                                                             *
 *                    $Revision:: 9                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "always.h"
#include "vector.h"
#include "parameter.h"
#include "wwdebug.h"

//////////////////////////////////////////////////////////////////////////////////
//
//	ParameterListClass
//
//////////////////////////////////////////////////////////////////////////////////
class ParameterListClass : public DynamicVectorClass<ParameterClass *> {
public:
  /////////////////////////////////////////////////////////////////////
  // Public constructurs/destructors
  /////////////////////////////////////////////////////////////////////
  ~ParameterListClass();

  /////////////////////////////////////////////////////////////////////
  // Public methods
  /////////////////////////////////////////////////////////////////////
  void Add(void *data, const char *param_name, ParameterClass::Type type);
  void Add(ParameterClass *parameter);

protected:
  /////////////////////////////////////////////////////////////////////
  // Protected methods
  /////////////////////////////////////////////////////////////////////
  void Free_Parameters();

private:
  /////////////////////////////////////////////////////////////////////
  // Private member data
  /////////////////////////////////////////////////////////////////////
  DynamicVectorClass<ParameterClass *> m_Parameters;
};

/////////////////////////////////////////////////////////////////////
// ~ParameterListClass
/////////////////////////////////////////////////////////////////////
inline ParameterListClass::~ParameterListClass() { Free_Parameters(); }

/////////////////////////////////////////////////////////////////////
// Add
/////////////////////////////////////////////////////////////////////
inline void ParameterListClass::Add(void *data, const char *param_name, ParameterClass::Type type) {
  //
  //	Create a new parameter object
  //
  ParameterClass *new_param = ParameterClass::Construct(type, data, param_name);

  //
  //	Add the new paramter object to our list
  //
  WWASSERT(new_param != nullptr);
  if (new_param != nullptr) {
    DynamicVectorClass<ParameterClass *>::Add(new_param);
  }
}

/////////////////////////////////////////////////////////////////////
// Add
/////////////////////////////////////////////////////////////////////
inline void ParameterListClass::Add(ParameterClass *new_param) {
  //
  //	Add the new paramter object to our list
  //
  if (new_param != nullptr) {
    DynamicVectorClass<ParameterClass *>::Add(new_param);
  }
}

/////////////////////////////////////////////////////////////////////
// Free_Parameters
/////////////////////////////////////////////////////////////////////
inline void ParameterListClass::Free_Parameters() {
  for (int index = 0; index < Count(); index++) {
    ParameterClass *param = Vector[index];

    //
    //	Free the parameter object
    //
    delete param;
  }

  m_Parameters.Delete_All();
}
