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

#if !defined(AFX_ANIMATIONPROPPAGE_H__9B07DA65_62B6_11D2_9FC7_00104B791122__INCLUDED_)
#define AFX_ANIMATIONPROPPAGE_H__9B07DA65_62B6_11D2_9FC7_00104B791122__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AnimationPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAnimationPropPage dialog

class CAnimationPropPage : public CPropertyPage {
  DECLARE_DYNCREATE(CAnimationPropPage)

  // Construction
public:
  CAnimationPropPage();
  ~CAnimationPropPage();

  // Dialog Data
  //{{AFX_DATA(CAnimationPropPage)
  enum { IDD = IDD_PROP_PAGE_ANIMATION };
  // NOTE - ClassWizard will add data members here.
  //    DO NOT EDIT what you see in these blocks of generated code !
  //}}AFX_DATA

  // Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CAnimationPropPage)
protected:
  virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support
                                                   //}}AFX_VIRTUAL

  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CAnimationPropPage)
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATIONPROPPAGE_H__9B07DA65_62B6_11D2_9FC7_00104B791122__INCLUDED_)
