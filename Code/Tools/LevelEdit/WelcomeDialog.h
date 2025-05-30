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

#if !defined(AFX_WELCOMEDIALOG_H__FF90928E_9450_11D2_9FEB_00104B791122__INCLUDED_)
#define AFX_WELCOMEDIALOG_H__FF90928E_9450_11D2_9FEB_00104B791122__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WelcomeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// WelcomeDialogClass dialog

class WelcomeDialogClass : public CDialog {
  // Construction
public:
  WelcomeDialogClass(CWnd *pParent = NULL); // standard constructor

  // Dialog Data
  //{{AFX_DATA(WelcomeDialogClass)
  enum { IDD = IDD_WELCOME_PAGE };
  // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(WelcomeDialogClass)
public:
  virtual int DoModal();

protected:
  virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support
                                                   //}}AFX_VIRTUAL

  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(WelcomeDialogClass)
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  afx_msg void OnPaint();
  afx_msg void OnDestroy();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

public:
  bool Are_Changes_Temporary(void) { return m_bChangesTemp; }

private:
  bool m_bChangesTemp;
  HBITMAP m_hBMP;
  int m_iWidth;
  int m_iHeight;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELCOMEDIALOG_H__FF90928E_9450_11D2_9FEB_00104B791122__INCLUDED_)
