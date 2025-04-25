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

#if !defined(AFX_OUTPUTFORMCLASS_H__E177C115_701D_11D2_9FCD_00104B791122__INCLUDED_)
#define AFX_OUTPUTFORMCLASS_H__E177C115_701D_11D2_9FCD_00104B791122__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OutputFormClass.h : header file
//

#include "dockableform.h"
#include "resource.h"
#include "textfile.h"

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

/////////////////////////////////////////////////////////////////////////////
//
// OutputFormClass form view
//
class OutputFormClass : public DockableFormClass {
public:
  OutputFormClass(); // protected constructor used by dynamic creation
                     // DECLARE_DYNCREATE(OutputFormClass)

  // Form Data
public:
  //{{AFX_DATA(OutputFormClass)
  enum { IDD = IDD_OUTPUT };
  CEdit m_OutputEdit;
  //}}AFX_DATA

  // Attributes
public:
  // Operations
public:
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(OutputFormClass)
protected:
  virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support
                                                   //}}AFX_VIRTUAL

  // Implementation
protected:
  virtual ~OutputFormClass();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext &dc) const;
#endif

  // Generated message map functions
  //{{AFX_MSG(OutputFormClass)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

public:
  ///////////////////////////////////////////////////////
  //	Public methods
  ///////////////////////////////////////////////////////
  void HandleInitDialog(void);
  void Output_Message(LPCTSTR new_message);

private:
  ///////////////////////////////////////////////////////
  //	Private member data
  ///////////////////////////////////////////////////////
  TextFileClass LogFile;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTFORMCLASS_H__E177C115_701D_11D2_9FCD_00104B791122__INCLUDED_)
