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

#if !defined(AFX_LIGHTSOLVEPROGRESSDIALOG_H__0C41C25F_AD2E_49CF_950E_0032CF919B17__INCLUDED_)
#define AFX_LIGHTSOLVEPROGRESSDIALOG_H__0C41C25F_AD2E_49CF_950E_0032CF919B17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LightSolveProgressDialog.h : header file
//

class LightSolveContextClass;
class LightSolveProgressClass;

/////////////////////////////////////////////////////////////////////////////
//
// LightSolveProgressDialog dialog
//
/////////////////////////////////////////////////////////////////////////////
class LightSolveProgressDialog : public CDialog {
  // Construction
public:
  LightSolveProgressDialog(LightSolveContextClass &context, CWnd *pParent = NULL); // standard constructor

  // Dialog Data
  //{{AFX_DATA(LightSolveProgressDialog)
  enum { IDD = IDD_GENERATING_LIGHT_SOLVE };
  CProgressCtrl m_ProgressBar;
  //}}AFX_DATA

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(LightSolveProgressDialog)
protected:
  virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  //}}AFX_VIRTUAL

  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(LightSolveProgressDialog)
  virtual BOOL OnInitDialog();
  virtual void OnCancel();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

public:
  /////////////////////////////////////////////////////////////
  //	Public methods
  /////////////////////////////////////////////////////////////
  bool Was_Cancelled(void) const { return m_Cancelled; }
  void Set_Finished(void);
  void Update_Stats(void);

  /////////////////////////////////////////////////////////////
  //	Static methods
  /////////////////////////////////////////////////////////////
  static void Solve(LightSolveContextClass &context, CWnd *parent);

private:
  /////////////////////////////////////////////////////////////
  //	Private methods
  /////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////
  //	Private member data
  /////////////////////////////////////////////////////////////
  bool m_Cancelled;
  LightSolveContextClass &m_SolveContext;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTSOLVEPROGRESSDIALOG_H__0C41C25F_AD2E_49CF_950E_0032CF919B17__INCLUDED_)
