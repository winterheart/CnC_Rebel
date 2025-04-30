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
 *                     $Archive:: /Commando/Code/Commando/dlgmpwoladdignoreentry.cpp   $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 11/30/01 12:11p                                             $*
 *                                                                                             *
 *                    $Revision:: 6                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "DlgMPWolAddIgnoreEntry.h"
#include "WOLBuddyMgr.h"
#include <WWUi\EditCtrl.h>
#include <WWDebug\WWDebug.h>

bool MPWolAddIgnoreEntry::DoDialog(const WCHAR *defaultUser) {
  MPWolAddIgnoreEntry *dialog = new MPWolAddIgnoreEntry(defaultUser);

  if (dialog) {
    dialog->Start_Dialog();
    dialog->Release_Ref();
  }

  return (dialog != NULL);
}

////////////////////////////////////////////////////////////////
//
//	MPWolAddIgnoreEntryPopupClass
//
////////////////////////////////////////////////////////////////
MPWolAddIgnoreEntry::MPWolAddIgnoreEntry(const WCHAR *defaultUser)
    : PopupDialogClass(IDD_MP_WOL_ADD_IGNORE_ENTRY), mDefaultUser(defaultUser) {
  WWDEBUG_SAY(("MPWolAddIgnoreEntry Instantiated\n"));
}

MPWolAddIgnoreEntry::~MPWolAddIgnoreEntry() { WWDEBUG_SAY(("MPWolAddIgnoreEntry Destroyed\n")); }

////////////////////////////////////////////////////////////////
//
//	On_Init_Dialog
//
////////////////////////////////////////////////////////////////
void MPWolAddIgnoreEntry::On_Init_Dialog(void) {
  mDefaultUser.Trim();
  bool hasName = (mDefaultUser.Get_Length() > 0);
  Enable_Dlg_Item(IDC_ADD_BUTTON, hasName);

  if (hasName) {
    Set_Dlg_Item_Text(IDC_IGNORE_USER_EDIT, mDefaultUser);
  }

  PopupDialogClass::On_Init_Dialog();
}

////////////////////////////////////////////////////////////////
//
//	On_Command
//
////////////////////////////////////////////////////////////////
void MPWolAddIgnoreEntry::On_Command(int ctrl_id, int message_id, DWORD param) {
  switch (ctrl_id) {
  case IDC_ADD_BUTTON:
    Add_Ignore_Entry();
    End_Dialog();
    break;
  }

  PopupDialogClass::On_Command(ctrl_id, message_id, param);
}

////////////////////////////////////////////////////////////////
//
//	Add_Ignore_Entry
//
////////////////////////////////////////////////////////////////
void MPWolAddIgnoreEntry::Add_Ignore_Entry(void) {
  WOLBuddyMgr *buddyMgr = WOLBuddyMgr::GetInstance(false);

  if (buddyMgr) {
    const WCHAR *name = Get_Dlg_Item_Text(IDC_IGNORE_USER_EDIT);
    buddyMgr->AddIgnore(name);
    buddyMgr->Release_Ref();
  }
}

void MPWolAddIgnoreEntry::On_EditCtrl_Change(EditCtrlClass *edit, int id) {
  if (IDC_IGNORE_USER_EDIT == id) {
    // Do not allow leading or trailing whitespace
    WideStringClass text(0, true);
    text = edit->Get_Text();

    text.Trim();
    edit->Set_Text(text);

    // Only enable the add button if they have entered something
    bool enable = (text.Get_Length() > 0);
    Enable_Dlg_Item(IDC_ADD_BUTTON, enable);
  }
}

void MPWolAddIgnoreEntry::On_EditCtrl_Enter_Pressed(EditCtrlClass *edit, int id) {
  if (IDC_IGNORE_USER_EDIT == id) {
    Add_Ignore_Entry();
  }
}
