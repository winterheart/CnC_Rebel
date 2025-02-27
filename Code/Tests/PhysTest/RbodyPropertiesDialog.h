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

#if !defined(AFX_RBODYPROPERTIESDIALOG_H__33DD6AC1_E78D_11D2_9BD2_00A0C9988171__INCLUDED_)
#define AFX_RBODYPROPERTIESDIALOG_H__33DD6AC1_E78D_11D2_9BD2_00A0C9988171__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RbodyPropertiesDialog.h : header file
//

class MoveablePhysClass;

/////////////////////////////////////////////////////////////////////////////
// CRbodyPropertiesDialog dialog

class CRbodyPropertiesDialog : public CDialog
{
// Construction
public:
	CRbodyPropertiesDialog(CWnd* pParent,MoveablePhysClass * obj);

// Dialog Data
	//{{AFX_DATA(CRbodyPropertiesDialog)
	enum { IDD = IDD_RBODY_PROPERTIES_DIALOG };
	CSpinButtonCtrl	m_LengthSpin;
	CSpinButtonCtrl	m_StiffnessSpin;
	CSpinButtonCtrl	m_DampingSpin;
	CSpinButtonCtrl	m_PositionZSpin;
	CSpinButtonCtrl	m_PositionYSpin;
	CSpinButtonCtrl	m_PositionXSpin;
	CSpinButtonCtrl	m_MassSpin;
	CSpinButtonCtrl	m_GravitySpin;
	CSpinButtonCtrl	m_ElasticitySpin;
	//}}AFX_DATA

	MoveablePhysClass *	Object;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRbodyPropertiesDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	float GetDlgItemFloat(int controlid);
	void SetDlgItemFloat(int controlid,float val);

	// Generated message map functions
	//{{AFX_MSG(CRbodyPropertiesDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RBODYPROPERTIESDIALOG_H__33DD6AC1_E78D_11D2_9BD2_00A0C9988171__INCLUDED_)
