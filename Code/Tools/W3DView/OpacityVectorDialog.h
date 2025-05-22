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

#if !defined(AFX_OPACITYVECTORDIALOG_H__E86BBE8C_F527_11D3_A08F_00104B791122__INCLUDED_)
#define AFX_OPACITYVECTORDIALOG_H__E86BBE8C_F527_11D3_A08F_00104B791122__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "sphereobj.h"

// Forward declarations
class ColorBarClass;
class RenderObjClass;

/////////////////////////////////////////////////////////////////////////////
//
// OpacityVectorDialogClass
//
/////////////////////////////////////////////////////////////////////////////
class OpacityVectorDialogClass : public CDialog {
  // Construction
public:
  OpacityVectorDialogClass(CWnd *pParent = NULL); // standard constructor

  // Dialog Data
  //{{AFX_DATA(OpacityVectorDialogClass)
  enum { IDD = IDD_OPACITY_VECTOR };
  CSliderCtrl m_SliderZ;
  CSliderCtrl m_SliderY;
  //}}AFX_DATA

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(OpacityVectorDialogClass)
protected:
  virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support
  virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
  //}}AFX_VIRTUAL

  // Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(OpacityVectorDialogClass)
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  virtual void OnCancel();
  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

public:
  ////////////////////////////////////////////////////////////////
  //	Public methods
  ////////////////////////////////////////////////////////////////
  void Set_Render_Obj(RenderObjClass *render_obj) { m_RenderObj = render_obj; }
  void Set_Vector(const AlphaVectorStruct &def_vector) { m_Value = def_vector; }
  const AlphaVectorStruct &Get_Vector(void) const { return m_Value; }
  void Set_Key_Index(int index) { m_KeyIndex = index; }

private:
  ////////////////////////////////////////////////////////////////
  //	Protected methods
  ////////////////////////////////////////////////////////////////
  void Update_Object(const AlphaVectorStruct &value);
  void Update_Object(void);
  AlphaVectorStruct Update_Value(void);

private:
  ////////////////////////////////////////////////////////////////
  //	Private member data
  ////////////////////////////////////////////////////////////////
  ColorBarClass *m_OpacityBar;
  RenderObjClass *m_RenderObj;
  AlphaVectorStruct m_Value;
  int m_KeyIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPACITYVECTORDIALOG_H__E86BBE8C_F527_11D3_A08F_00104B791122__INCLUDED_)
