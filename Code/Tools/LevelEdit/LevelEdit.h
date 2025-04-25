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

// LevelEdit.h : main header file for the LEVELEDIT application
//

#if !defined(AFX_LEVELEDIT_H__6D711A23_651E_11D2_9FC8_00104B791122__INCLUDED_)
#define AFX_LEVELEDIT_H__6D711A23_651E_11D2_9FC8_00104B791122__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h" // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLevelEditApp:
// See LevelEdit.cpp for the implementation of this class
//

class CLevelEditApp : public CWinApp {
public:
  CLevelEditApp();

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CLevelEditApp)
public:
  virtual BOOL InitInstance();
  virtual int ExitInstance();
  virtual BOOL PreTranslateMessage(MSG *pMsg);
  //}}AFX_VIRTUAL

  // Implementation

  //{{AFX_MSG(CLevelEditApp)
  afx_msg void OnAppAbout();
  afx_msg void OnFileOpen();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

extern CLevelEditApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEVELEDIT_H__6D711A23_651E_11D2_9FC8_00104B791122__INCLUDED_)
