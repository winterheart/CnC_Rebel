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

#if !defined(AFX_ANIMMIXINGPAGE_H__67C01722_7C0D_11D3_9A3A_0090272E6F90__INCLUDED_)
#define AFX_ANIMMIXINGPAGE_H__67C01722_7C0D_11D3_9A3A_0090272E6F90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnimMixingPage.h : header file
//

class CAdvancedAnimSheet;

/////////////////////////////////////////////////////////////////////////////
// CAnimMixingPage dialog

class CAnimMixingPage : public CPropertyPage {
  DECLARE_DYNCREATE(CAnimMixingPage)

  // Construction
public:
  CAnimMixingPage(CAdvancedAnimSheet *sheet = NULL);
  ~CAnimMixingPage();

  // Dialog Data
  //{{AFX_DATA(CAnimMixingPage)
  enum { IDD = IDD_PROP_PAGE_ADVANIM_MIXING };
  CListCtrl m_AnimList;
  //}}AFX_DATA

  // Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CAnimMixingPage)
public:
  virtual void OnOK();
  virtual BOOL OnKillActive();

protected:
  virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support
                                                   //}}AFX_VIRTUAL

  // Implementation
protected:
  void FillListCtrl(void);

  CAdvancedAnimSheet *m_Sheet;

  // Generated message map functions
  //{{AFX_MSG(CAnimMixingPage)
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMMIXINGPAGE_H__67C01722_7C0D_11D3_9A3A_0090272E6F90__INCLUDED_)
