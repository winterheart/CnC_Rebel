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

#if !defined(AFX_PARTICLESIZEDIALOG_H__0CD2CBA5_1219_11D3_A034_00104B791122__INCLUDED_)
#define AFX_PARTICLESIZEDIALOG_H__0CD2CBA5_1219_11D3_A034_00104B791122__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParticleSizeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ParticleSizeDialogClass dialog

class ParticleSizeDialogClass : public CDialog {
  // Construction
public:
  ParticleSizeDialogClass(float size, CWnd *pParent = NULL); // standard constructor

  // Dialog Data
  //{{AFX_DATA(ParticleSizeDialogClass)
  enum { IDD = IDD_PARTICLE_SIZE };
  CSpinButtonCtrl m_SizeSpin;
  //}}AFX_DATA

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(ParticleSizeDialogClass)
protected:
  virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support
  virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
  //}}AFX_VIRTUAL

  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(ParticleSizeDialogClass)
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

public:
  /////////////////////////////////////////////////////////////
  //	Public methods
  /////////////////////////////////////////////////////////////
  float Get_Size(void) const { return m_Size; }

private:
  /////////////////////////////////////////////////////////////
  //	Private member data
  /////////////////////////////////////////////////////////////
  float m_Size;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARTICLESIZEDIALOG_H__0CD2CBA5_1219_11D3_A034_00104B791122__INCLUDED_)
