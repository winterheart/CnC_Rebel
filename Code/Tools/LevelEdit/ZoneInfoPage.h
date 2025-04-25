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

#if !defined(AFX_ZONEINFOPAGE_H__B17C4184_A438_11D2_9FEE_00104B791122__INCLUDED_)
#define AFX_ZONEINFOPAGE_H__B17C4184_A438_11D2_9FEE_00104B791122__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoneInfoPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ZoneInfoPageClass form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class ZoneInstanceClass;
#include "DockableForm.H"

//////////////////////////////////////////////////////////
//
//	ZoneInfoPageClass
//
class ZoneInfoPageClass : public DockableFormClass {
public:
  ZoneInfoPageClass();
  ZoneInfoPageClass(ZoneInstanceClass *pzone);
  virtual ~ZoneInfoPageClass();

  // Form Data
public:
  //{{AFX_DATA(ZoneInfoPageClass)
  enum { IDD = IDD_ZONE_INFO };
  // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA

  // Attributes
public:
  // Operations
public:
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(ZoneInfoPageClass)
protected:
  virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support
                                                   //}}AFX_VIRTUAL

  // Implementation
protected:
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext &dc) const;
#endif

  // Generated message map functions
  //{{AFX_MSG(ZoneInfoPageClass)
  // NOTE - the ClassWizard will add and remove member functions here.
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

public:
  ///////////////////////////////////////////////////////
  //
  //	Public methods
  //
  void HandleInitDialog(void);
  bool Apply_Changes(void);

  ///////////////////////////////////////////////////////
  //
  //	Inline accessors
  //
  void Set_Zone(ZoneInstanceClass *pzone) { m_pZone = pzone; }
  ZoneInstanceClass *Get_Zone(void) { return m_pZone; }

private:
  ///////////////////////////////////////////////////////
  //
  //	Private member data
  //
  ZoneInstanceClass *m_pZone;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZONEINFOPAGE_H__B17C4184_A438_11D2_9FEE_00104B791122__INCLUDED_)
