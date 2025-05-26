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

// W3DViewView.h : interface of the CW3DViewView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_W3DVIEWVIEW_H__2BB39E33_5D3A_11D2_9FC6_00104B791122__INCLUDED_)
#define AFX_W3DVIEWVIEW_H__2BB39E33_5D3A_11D2_9FC6_00104B791122__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CW3DViewView : public CView {
protected: // create from serialization only
  CW3DViewView();
  DECLARE_DYNCREATE(CW3DViewView)

  // Attributes
public:
  CW3DViewDoc *GetDocument();

  // Operations
public:
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CW3DViewView)
public:
  virtual void OnDraw(CDC *pDC); // overridden to draw this view
  virtual BOOL PreCreateWindow(CREATESTRUCT &cs);

protected:
  //}}AFX_VIRTUAL

  // Implementation
public:
  virtual ~CW3DViewView();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext &dc) const;
#endif

protected:
  // Generated message map functions
protected:
  //{{AFX_MSG(CW3DViewView)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG // debug version in W3DViewView.cpp
inline CW3DViewDoc *CW3DViewView::GetDocument() { return (CW3DViewDoc *)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_W3DVIEWVIEW_H__2BB39E33_5D3A_11D2_9FC6_00104B791122__INCLUDED_)
