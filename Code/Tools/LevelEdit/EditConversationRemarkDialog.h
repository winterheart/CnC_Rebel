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

#if !defined(AFX_EDITCONVERSATIONREMARKDIALOG_H__9FDB5AC9_9866_40F9_B912_2679C63EB92D__INCLUDED_)
#define AFX_EDITCONVERSATIONREMARKDIALOG_H__9FDB5AC9_9866_40F9_B912_2679C63EB92D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "stringpickerdialog.h"
#include "conversationremark.h"

/////////////////////////////////////////////////////////////////////////////
//
// EditConversationRemarkDialogClass
//
/////////////////////////////////////////////////////////////////////////////
class EditConversationRemarkDialogClass : public CDialog {
  // Construction
public:
  EditConversationRemarkDialogClass(CWnd *pParent = NULL); // standard constructor

  // Dialog Data
  //{{AFX_DATA(EditConversationRemarkDialogClass)
  enum { IDD = IDD_EDIT_CONVERSATION_REMARK };
  CSpinButtonCtrl m_OratorIDSpin;
  //}}AFX_DATA

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(EditConversationRemarkDialogClass)
protected:
  virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support
                                                   //}}AFX_VIRTUAL

  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(EditConversationRemarkDialogClass)
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

public:
  //////////////////////////////////////////////////////////////////////////
  //	Public methods
  //////////////////////////////////////////////////////////////////////////
  void Set_Remark(const ConversationRemarkClass &remark) { Remark = remark; }
  const ConversationRemarkClass &Get_Remark(void) const { return Remark; }

  void Set_Orator_Bitmask(int mask = 0x00000001) { m_OratorBitmask = mask; }

protected:
  //////////////////////////////////////////////////////////////////////////
  //	Protected methods
  //////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////
  //	Protected member data
  //////////////////////////////////////////////////////////////////////////
  int m_OratorBitmask;
  ConversationRemarkClass Remark;

  StringPickerDialogClass StringPicker;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONVERSATIONREMARKDIALOG_H__9FDB5AC9_9866_40F9_B912_2679C63EB92D__INCLUDED_)
