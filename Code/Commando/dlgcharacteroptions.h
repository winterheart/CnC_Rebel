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
 *                     $Archive:: /Commando/Code/commando/dlgcharacteroptions.h      $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 1/07/02 10:32a                                              $*
 *                                                                                             *
 *                    $Revision:: 3                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __DLGOPTIONSCHARACTER_H
#define __DLGOPTIONSCHARACTER_H

#include "menudialog.h"
#include "resource.h"

////////////////////////////////////////////////////////////////
//
//	CharacterOptionsMenuClass
//
////////////////////////////////////////////////////////////////
class CharacterOptionsMenuClass : public MenuDialogClass {
public:
  ////////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  ////////////////////////////////////////////////////////////////
  CharacterOptionsMenuClass(void);
  ~CharacterOptionsMenuClass(void);

  ////////////////////////////////////////////////////////////////
  //	Public methods
  ////////////////////////////////////////////////////////////////

  //
  //	Inherited
  //
  void On_Init_Dialog(void);
  void On_Command(int ctrl_id, int mesage_id, DWORD param);
  void On_ComboBoxCtrl_Sel_Change(ComboBoxCtrlClass *combo_ctrl, int ctrl_id, int old_sel, int new_sel);

private:
  ////////////////////////////////////////////////////////////////
  //	Private methods
  ////////////////////////////////////////////////////////////////
  void Fill_Character_Combobox(void);

  void On_Character_Selected(int index);

  void Display_Model(const char *model_name);
  void Display_Default_Model(int definition_id);

  void Ensure_Definitions_Are_Loaded(void);

  ////////////////////////////////////////////////////////////////
  //	Private member data
  ////////////////////////////////////////////////////////////////
  bool UnloadDefs;
};

#endif //__DLGOPTIONSCHARACTER_H
