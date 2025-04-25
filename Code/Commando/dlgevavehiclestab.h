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
 *                 Project Name : Combat
 **
 *                                                                                             *
 *                     $Archive:: /Commando/Code/commando/dlgevavehiclestab.h      $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 5/02/01 2:28p                                               $*
 *                                                                                             *
 *                    $Revision:: 3                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __DLG_EVA_VEHICLES_TAB_H
#define __DLG_EVA_VEHICLES_TAB_H

#include "dlgevaviewertab.h"
#include "resource.h"

////////////////////////////////////////////////////////////////
//
//	EvaVehiclesTabClass
//
////////////////////////////////////////////////////////////////
class EvaVehiclesTabClass : public EvaViewerTabClass {
public:
  ////////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  ////////////////////////////////////////////////////////////////
  EvaVehiclesTabClass(void) : EvaViewerTabClass(IDD_ENCYCLOPEDIA_VEHICLES_TAB) {}

  ////////////////////////////////////////////////////////////////
  //	Public methods
  ////////////////////////////////////////////////////////////////

protected:
  ////////////////////////////////////////////////////////////////
  //	Protected methods
  ////////////////////////////////////////////////////////////////
  void On_Init_Dialog(void);
};

#endif //__DLG_EVA_VEHICLES_TAB_H
