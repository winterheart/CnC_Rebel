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

#if !defined(AFX_EDITCONVERSATIONLISTDIALOG_H__29A296FF_374F_46F9_A2F8_496C5307D103__INCLUDED_)
#define AFX_EDITCONVERSATIONLISTDIALOG_H__29A296FF_374F_46F9_A2F8_496C5307D103__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
//	 Forward declarations
/////////////////////////////////////////////////////////////////////////////
class ConversationClass;

/////////////////////////////////////////////////////////////////////////////
//
// EditConversationListDialogClass
//
/////////////////////////////////////////////////////////////////////////////
class EditConversationListDialogClass : public CDialog {
  // Construction
public:
  EditConversationListDialogClass(CWnd *pParent = NULL); // standard constructor

  // Dialog Data
  //{{AFX_DATA(EditConversationListDialogClass)
  enum { IDD = IDD_CONVERSATION_LIST };
  CListCtrl m_ListCtrl;
  //}}AFX_DATA

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(EditConversationListDialogClass)
protected:
  virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support
                                                   //}}AFX_VIRTUAL

  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(EditConversationListDialogClass)
  virtual BOOL OnInitDialog();
  afx_msg void OnAdd();
  virtual void OnOK();
  afx_msg void OnDblclkConversationList(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnDeleteitemConversationList(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnKeydownConversationList(NMHDR *pNMHDR, LRESULT *pResult);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

public:
  /////////////////////////////////////////////////////////////////////////////
  //	Public methods
  /////////////////////////////////////////////////////////////////////////////

protected:
  /////////////////////////////////////////////////////////////////////////////
  //	Protected methods
  /////////////////////////////////////////////////////////////////////////////
  void Add_Conversation(ConversationClass *conversation);
  void Update_Conversation(int sel_index);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONVERSATIONLISTDIALOG_H__29A296FF_374F_46F9_A2F8_496C5307D103__INCLUDED_)
