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

// MixViewerView.h : interface of the CMixViewerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIXVIEWERVIEW_H__562AE398_6B91_4DA8_B325_73D4EC73EB36__INCLUDED_)
#define AFX_MIXVIEWERVIEW_H__562AE398_6B91_4DA8_B325_73D4EC73EB36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "vector.h"
#include "wwstring.h"

//////////////////////////////////////////////////////////////////////////////////
//
//	CMixViewerView
//
//////////////////////////////////////////////////////////////////////////////////
class CMixViewerView : public CListView {
protected: // create from serialization only
  CMixViewerView();
  DECLARE_DYNCREATE(CMixViewerView)

  // Attributes
public:
  CMixViewerDoc *GetDocument();

  // Operations
public:
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CMixViewerView)
public:
  virtual void OnDraw(CDC *pDC); // overridden to draw this view
  virtual BOOL PreCreateWindow(CREATESTRUCT &cs);

protected:
  virtual void OnInitialUpdate(); // called first time after construct
                                  //}}AFX_VIRTUAL

  // Implementation
public:
  virtual ~CMixViewerView();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext &dc) const;
#endif

protected:
  // Generated message map functions
protected:
  //{{AFX_MSG(CMixViewerView)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnWindowPosChanging(WINDOWPOS FAR *lpwndpos);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

public:
  ///////////////////////////////////////////////////////////////////////
  //	Public methods
  ///////////////////////////////////////////////////////////////////////
  void Reload(const char *filename);
  void Reset(void);

private:
  ///////////////////////////////////////////////////////////////////////
  //	Private member data
  ///////////////////////////////////////////////////////////////////////
  DynamicVectorClass<StringClass> FilenameList;

  StringClass CurrentFilename;
};

#ifndef _DEBUG // debug version in MixViewerView.cpp
inline CMixViewerDoc *CMixViewerView::GetDocument() { return (CMixViewerDoc *)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIXVIEWERVIEW_H__562AE398_6B91_4DA8_B325_73D4EC73EB36__INCLUDED_)
