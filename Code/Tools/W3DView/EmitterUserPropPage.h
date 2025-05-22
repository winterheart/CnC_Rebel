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

#if !defined(AFX_EMITTERUSERPROPPAGE_H__83A8B840_BA3B_11D2_9FFA_00104B791122__INCLUDED_)
#define AFX_EMITTERUSERPROPPAGE_H__83A8B840_BA3B_11D2_9FFA_00104B791122__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EmitterUserPropPage.h : header file
//

#include "Resource.H"

// Forward delcarations
class EmitterInstanceListClass;

/////////////////////////////////////////////////////////////////////////////
// EmitterUserPropPageClass dialog

class EmitterUserPropPageClass : public CPropertyPage {
  DECLARE_DYNCREATE(EmitterUserPropPageClass)

  // Construction
public:
  EmitterUserPropPageClass(EmitterInstanceListClass *pemitter_list = NULL);
  ~EmitterUserPropPageClass();

  // Dialog Data
  //{{AFX_DATA(EmitterUserPropPageClass)
  enum { IDD = IDD_PROP_PAGE_EMITTER_USER };
  CComboBox m_TypeCombo;
  //}}AFX_DATA

  // Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(EmitterUserPropPageClass)
public:
  virtual BOOL OnApply();

protected:
  virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support
                                                   //}}AFX_VIRTUAL

  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(EmitterUserPropPageClass)
  virtual BOOL OnInitDialog();
  afx_msg void OnChangeProgrammerSettingsEdit();
  afx_msg void OnSelchangeTypeCombo();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

public:
  /////////////////////////////////////////////////////////
  //
  //	Public methods
  //

  //
  //	Inline accessors
  //
  EmitterInstanceListClass *Get_Emitter(void) const { return m_pEmitterList; }
  void Set_Emitter(EmitterInstanceListClass *pemitter_list) {
    m_pEmitterList = pemitter_list;
    Initialize();
  }
  bool Is_Data_Valid(void) const { return m_bValid; }

  int Get_Type(void) const { return m_iType; }
  const CString &Get_String(void) const { return m_UserString; }
  void Set_Type(int type) { m_iType = type; }
  void Set_String(LPCTSTR string) { m_UserString = string; }

protected:
  /////////////////////////////////////////////////////////
  //
  //	Protected methods
  //
  void Initialize(void);

private:
  /////////////////////////////////////////////////////////
  //
  //	Private member data
  //
  EmitterInstanceListClass *m_pEmitterList;
  bool m_bValid;

  int m_iType;
  CString m_UserString;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMITTERUSERPROPPAGE_H__83A8B840_BA3B_11D2_9FFA_00104B791122__INCLUDED_)
