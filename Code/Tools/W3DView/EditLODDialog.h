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

#if !defined(AFX_EDITLODDIALOG_H__AF3CDE8E_61EC_11D2_9FC7_00104B791122__INCLUDED_)
#define AFX_EDITLODDIALOG_H__AF3CDE8E_61EC_11D2_9FC7_00104B791122__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// EditLODDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditLODDialog dialog

class CEditLODDialog : public CDialog {
  // Construction
public:
  CEditLODDialog(CWnd *pParent = NULL); // standard constructor

  // Dialog Data
  //{{AFX_DATA(CEditLODDialog)
  enum { IDD = IDD_EDIT_LOD };
  CSpinButtonCtrl m_switchUpSpin;
  CSpinButtonCtrl m_switchDownSpin;
  CListCtrl m_hierarchyListCtrl;
  //}}AFX_DATA

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CEditLODDialog)
protected:
  virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support
                                                   //}}AFX_VIRTUAL

  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CEditLODDialog)
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  virtual void OnCancel();
  afx_msg void OnDeltaposSwitchUpSpin(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnDeltaposSwitchDnSpin(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnItemChangedHierarchyList(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnUpdateSwitchDnEdit();
  afx_msg void OnUpdateSwitchUpEdit();
  afx_msg void OnRecalc();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

public:
protected:
  void ResetControls(int iIndex);
  void EnableControls(BOOL bEnable);

private:
  float m_spinIncrement;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITLODDIALOG_H__AF3CDE8E_61EC_11D2_9FC7_00104B791122__INCLUDED_)
