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

#if !defined(AFX_TEXTUREPATHDIALOG_H__FD455E37_D28C_11D3_A085_00104B791122__INCLUDED_)
#define AFX_TEXTUREPATHDIALOG_H__FD455E37_D28C_11D3_A085_00104B791122__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TexturePathDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TexturePathDialogClass dialog

class TexturePathDialogClass : public CDialog {
  // Construction
public:
  TexturePathDialogClass(CWnd *pParent = NULL); // standard constructor

  // Dialog Data
  //{{AFX_DATA(TexturePathDialogClass)
  enum { IDD = IDD_TEXTURE_PATHS };
  // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(TexturePathDialogClass)
protected:
  virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support
                                                   //}}AFX_VIRTUAL

  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(TexturePathDialogClass)
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  afx_msg void OnBrowse1();
  afx_msg void OnBrowse2();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTUREPATHDIALOG_H__FD455E37_D28C_11D3_A085_00104B791122__INCLUDED_)
