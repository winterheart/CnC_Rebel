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
 *                     $Archive:: /Commando/Code/wwui/comboboxctrl.h          $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                *
 *                                                                                             *
 *                     $Modtime:: 1/09/02 4:07p                                               $*
 *                                                                                             *
 *                    $Revision:: 22                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef __COMBOBOX_CTRL_H
#define __COMBOBOX_CTRL_H

#include "dialogcontrol.h"
#include "vector3.h"
#include "render2dsentence.h"
#include "bittype.h"
#include "dropdownctrl.h"
#include "EditCtrl.h"

////////////////////////////////////////////////////////////////
//
//	ComboBoxCtrlClass
//
////////////////////////////////////////////////////////////////
class ComboBoxCtrlClass : public DialogControlClass {
public:
  ////////////////////////////////////////////////////////////////
  //	Public friends
  ////////////////////////////////////////////////////////////////
  friend class DropDownCtrlClass;

  ////////////////////////////////////////////////////////////////
  //	Public constructors/destructors
  ////////////////////////////////////////////////////////////////
  ComboBoxCtrlClass(void);
  virtual ~ComboBoxCtrlClass(void);

  ////////////////////////////////////////////////////////////////
  //	Public methods
  ////////////////////////////////////////////////////////////////

  //
  //	From DialogControlClass
  //
  const WCHAR *Get_Text(void) const;
  void Set_Text(const WCHAR *title);
  void Set_Window_Pos(const Vector2 &pos);
  void Render(void);

  void Set_Style(DWORD style);

  //
  //	Content control
  //
  int Add_String(const WCHAR *string) { return DropDownCtrl.Add_String(string); }
  void Delete_String(int index);
  int Find_String(const WCHAR *string) { return DropDownCtrl.Find_String(string); }
  int Select_String(const WCHAR *string);
  void Set_Item_Data(int index, uint32 data) {
    DropDownCtrl.Set_Item_Data(index, data);
    Set_Dirty();
  }
  uint32 Get_Item_Data(int index) { return DropDownCtrl.Get_Item_Data(index); }
  void Reset_Content(void) { DropDownCtrl.Reset_Content(); }
  bool Get_String(int index, WideStringClass &string) { return DropDownCtrl.Get_String(index, string); }

  int Get_Item_Count(void) { return DropDownCtrl.Get_Count(); }

  //
  //	Selection management
  //
  void Set_Curr_Sel(int index);
  int Get_Curr_Sel(void) const { return CurrSel; }

protected:
  ////////////////////////////////////////////////////////////////
  //	Protected methods
  ////////////////////////////////////////////////////////////////
  void Set_Sel(int index, bool notify);

  void On_LButton_Down(const Vector2 &mouse_pos);
  void On_LButton_Up(const Vector2 &mouse_pos);
  void On_Mouse_Move(const Vector2 &mouse_pos);
  void On_Set_Cursor(const Vector2 &mouse_pos);
  void On_Set_Focus(void);
  void On_Kill_Focus(DialogControlClass *focus);
  void On_Mouse_Wheel(int direction);
  bool On_Key_Down(uint32 key_id, uint32 key_data);
  void On_Create(void);
  void On_Destroy(void);
  void Update_Client_Rect(void);

  void Create_Control_Renderers(void);
  void Create_Text_Renderers(void);
  void Display_Drop_Down(bool onoff);

  //
  //	Notifications
  //
  void On_Drop_Down_End(int curr_sel);
  void On_EditCtrl_Change(EditCtrlClass *edit_ctrl, int ctrl_id);
  bool On_EditCtrl_Key_Down(EditCtrlClass *edit_ctrl, uint32 key_id, uint32 key_data);

  ////////////////////////////////////////////////////////////////
  //	Protected member data
  ////////////////////////////////////////////////////////////////
  Render2DSentenceClass TextRenderer;
  Render2DClass ControlRenderer;
  Render2DClass HilightRenderer;
  bool IsDropDownDisplayed;
  int CurrState;
  RectClass ButtonRect;
  RectClass TextRect;
  RectClass FullRect;
  Vector2 DropDownSize;
  bool WasButtonPressedOnMe;
  bool IsInitialized;
  DropDownCtrlClass DropDownCtrl;
  int LastDropDownDisplayChange;
  int CurrSel;
  EditCtrlClass EditControl;
};

#endif //__COMBOBOX_CTRL_H
