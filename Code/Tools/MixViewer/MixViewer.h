/*
 * 	Command & Conquer Renegade(tm)
 * 	Copyright 2025 Electronic Arts Inc.
 * 	Copyright 2025 CnC: Rebel Developers.
 *
 * 	This program is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License as published by
 * 	the Free Software Foundation, either version 3 of the License, or
 * 	(at your option) any later version.
 *
 * 	This program is distributed in the hope that it will be useful,
 * 	but WITHOUT ANY WARRANTY; without even the implied warranty of
 * 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * 	GNU General Public License for more details.
 *
 * 	You should have received a copy of the GNU General Public License
 * 	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// MixViewer.h : main header file for the MIXVIEWER application
//

#if !defined(AFX_MIXVIEWER_H__E184F3F7_FBE5_497F_8D2F_730CD788C579__INCLUDED_)
#define AFX_MIXVIEWER_H__E184F3F7_FBE5_497F_8D2F_730CD788C579__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h" // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMixViewerApp:
// See MixViewer.cpp for the implementation of this class
//

class CMixViewerApp : public CWinApp {
public:
  CMixViewerApp();

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CMixViewerApp)
public:
  virtual BOOL InitInstance();
  //}}AFX_VIRTUAL

  // Implementation
  //{{AFX_MSG(CMixViewerApp)
  afx_msg void OnAppAbout();
  // NOTE - the ClassWizard will add and remove member functions here.
  //    DO NOT EDIT what you see in these blocks of generated code !
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIXVIEWER_H__E184F3F7_FBE5_497F_8D2F_730CD788C579__INCLUDED_)
