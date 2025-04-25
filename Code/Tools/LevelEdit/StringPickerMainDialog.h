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

#if !defined(AFX_STRINGPICKERMAINDIALOG_H__5A09E5A1_C5E6_4756_A673_E472150FE3BB__INCLUDED_)
#define AFX_STRINGPICKERMAINDIALOG_H__5A09E5A1_C5E6_4756_A673_E472150FE3BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "stringpickerdialog.h"

/////////////////////////////////////////////////////////////////////////////
//
//	StringPickerMainDialogClass
//
/////////////////////////////////////////////////////////////////////////////
class StringPickerMainDialogClass : public CDialog {
  // Construction
public:
  StringPickerMainDialogClass(CWnd *pParent = NULL); // standard constructor

  // Dialog Data
  //{{AFX_DATA(StringPickerMainDialogClass)
  enum { IDD = IDD_STRING_PICKER_DIALOG };
  // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(StringPickerMainDialogClass)
protected:
  virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support
                                                   //}}AFX_VIRTUAL

  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(StringPickerMainDialogClass)
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

public:
  ////////////////////////////////////////////////////////////////////
  //	Public methods
  ////////////////////////////////////////////////////////////////////
  int Get_String_ID(void) const { return TextID; }
  void Set_String_ID(int id) { TextID = id; }

private:
  ////////////////////////////////////////////////////////////////////
  //	Private member data
  ////////////////////////////////////////////////////////////////////
  int TextID;
  StringPickerDialogClass StringPicker;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRINGPICKERMAINDIALOG_H__5A09E5A1_C5E6_4756_A673_E472150FE3BB__INCLUDED_)
