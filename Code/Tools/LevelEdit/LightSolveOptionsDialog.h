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

#if !defined(AFX_LIGHTSOLVEOPTIONSDIALOG_H__71E8C194_1511_4569_8F11_D27772ED5159__INCLUDED_)
#define AFX_LIGHTSOLVEOPTIONSDIALOG_H__71E8C194_1511_4569_8F11_D27772ED5159__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LightSolveOptionsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LightSolveOptionsDialogClass dialog

class LightSolveOptionsDialogClass : public CDialog {
  // Construction
public:
  LightSolveOptionsDialogClass(CWnd *pParent = NULL); // standard constructor

  // Dialog Data
  //{{AFX_DATA(LightSolveOptionsDialogClass)
  enum { IDD = IDD_LIGHT_SOLVE_OPTIONS };
  // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(LightSolveOptionsDialogClass)
protected:
  virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support
                                                   //}}AFX_VIRTUAL

  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(LightSolveOptionsDialogClass)
  virtual void OnOK();
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTSOLVEOPTIONSDIALOG_H__71E8C194_1511_4569_8F11_D27772ED5159__INCLUDED_)
