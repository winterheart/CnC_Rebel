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

#if !defined(AFX_WAYPATHINFOPAGE_H__D1D47A03_F096_11D3_A08F_00104B791122__INCLUDED_)
#define AFX_WAYPATHINFOPAGE_H__D1D47A03_F096_11D3_A08F_00104B791122__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "dockableform.h"

//////////////////////////////////////////////////////////
// Forward declarations
//////////////////////////////////////////////////////////
class WaypointNodeClass;


//////////////////////////////////////////////////////////
//
//	WaypathInfoPageClass
//
//////////////////////////////////////////////////////////
class WaypathInfoPageClass : public DockableFormClass
{
public:
	WaypathInfoPageClass (void);
	WaypathInfoPageClass (WaypointNodeClass *waypoint);
	virtual ~WaypathInfoPageClass (void);

// Dialog Data
	//{{AFX_DATA(WaypathInfoPageClass)
	enum { IDD = IDD_WAYPOINT_INFO };
	CSliderCtrl	m_SpeedSlider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WaypathInfoPageClass)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(WaypathInfoPageClass)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:

	///////////////////////////////////////////////////////
	//	Public methods
	///////////////////////////////////////////////////////
	void				HandleInitDialog (void);
	bool				Apply_Changes (void);

	///////////////////////////////////////////////////////
	//	Inline accessors
	///////////////////////////////////////////////////////
	void						Set_Waypoint (WaypointNodeClass *waypoint)	{ m_Waypoint = waypoint; }
	WaypointNodeClass *	Get_Waypoint (void)									{ return m_Waypoint; }

protected:

	///////////////////////////////////////////////////////
	//	Protected methods
	///////////////////////////////////////////////////////
	void						Update_Enable_State (void);

private:

	///////////////////////////////////////////////////////
	//	Private member data
	///////////////////////////////////////////////////////
	WaypointNodeClass *m_Waypoint;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAYPATHINFOPAGE_H__D1D47A03_F096_11D3_A08F_00104B791122__INCLUDED_)
