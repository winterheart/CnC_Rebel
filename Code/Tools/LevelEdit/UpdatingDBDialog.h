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

#if !defined(AFX_UPDATINGDBDIALOG_H__A5E14BDC_8F04_11D2_9FE7_00104B791122__INCLUDED_)
#define AFX_UPDATINGDBDIALOG_H__A5E14BDC_8F04_11D2_9FE7_00104B791122__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpdatingDBDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// UpdatingDBDialogClass dialog

class UpdatingDBDialogClass : public CDialog
{
// Construction
public:
	UpdatingDBDialogClass(HWND hparentwnd);   // standard constructor

// Dialog Data
	//{{AFX_DATA(UpdatingDBDialogClass)
	enum { IDD = IDD_UPDATING_DATABASE };
	CAnimateCtrl	m_AnimationCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(UpdatingDBDialogClass)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(UpdatingDBDialogClass)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATINGDBDIALOG_H__A5E14BDC_8F04_11D2_9FE7_00104B791122__INCLUDED_)
