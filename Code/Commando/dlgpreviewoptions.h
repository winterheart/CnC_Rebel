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
 *                     $Archive:: /Commando/Code/commando/dlgpreviewoptions.h       $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 5/21/01 11:02a                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __DLGOPTIONSPREVIEW_H
#define __DLGOPTIONSPREVIEW_H

#include "menudialog.h"
#include "resource.h"

////////////////////////////////////////////////////////////////
//
//	PreviewOptionsMenuClass
//
////////////////////////////////////////////////////////////////
class PreviewOptionsMenuClass : public MenuDialogClass {
public:
  ////////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  ////////////////////////////////////////////////////////////////
  PreviewOptionsMenuClass(void);

  ////////////////////////////////////////////////////////////////
  //	Public methods
  ////////////////////////////////////////////////////////////////
  void On_Init_Dialog(void);
  void On_Command(int ctrl_id, int mesage_id, DWORD param);

private:
  ////////////////////////////////////////////////////////////////
  //	Private methods
  ////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////
  //	Private member data
  ////////////////////////////////////////////////////////////////
};

#endif //__DLGOPTIONSPREVIEW_H
