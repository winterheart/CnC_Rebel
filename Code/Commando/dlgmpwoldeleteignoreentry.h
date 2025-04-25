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
 *                     $Archive:: /Commando/Code/Commando/dlgmpwoldeleteignoreentry.h       $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 8/17/01 10:41a                                              $*
 *                                                                                             *
 *                    $Revision:: 4                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __DLG_MP_WOL_DELETE_IGNORE_ENTRY_H
#define __DLG_MP_WOL_DELETE_IGNORE_ENTRY_H

#include "popupdialog.h"
#include "resource.h"
#include "WideString.h"

////////////////////////////////////////////////////////////////
//
//	MPWolDeleteIgnoreEntryPopupClass
//
////////////////////////////////////////////////////////////////
class MPWolDeleteIgnoreEntryPopupClass : public PopupDialogClass {
public:
  ////////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  ////////////////////////////////////////////////////////////////
  MPWolDeleteIgnoreEntryPopupClass(void);

  ////////////////////////////////////////////////////////////////
  //	Public methods
  ////////////////////////////////////////////////////////////////
  void On_Init_Dialog(void);
  void On_Command(int ctrl_id, int mesage_id, DWORD param);

  //
  //	Content control
  //
  void Set_User_Name(const WCHAR *user_name) { UserName = user_name; }

protected:
  ////////////////////////////////////////////////////////////////
  //	Protected methods
  ////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////
  //	Protected member data
  ////////////////////////////////////////////////////////////////
  WideStringClass UserName;
};

#endif //__DLG_MP_WOL_DELETE_IGNORE_ENTRY_H
