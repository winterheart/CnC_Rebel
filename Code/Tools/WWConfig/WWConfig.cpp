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

// WWConfig.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "WWConfig.h"
#include "WWConfigDlg.h"
#include "argv.h"
#include "locale_api.h"
#include "registry.h"
#include "wwconfig_ids.h"

#define OLD_APP_SUB_KEY "Software\\Westwood\\Renegade"
#define APP_SUB_KEY "Software\\CnC_Rebel\\Rebel"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int GlobalExitValue = 1;
void AutoConfigSettings();
void CheckDriverVersion();

/////////////////////////////////////////////////////////////////////////////
// CWWConfigApp

BEGIN_MESSAGE_MAP(CWWConfigApp, CWinApp)
//{{AFX_MSG_MAP(CWWConfigApp)
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code!
//}}AFX_MSG
ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWWConfigApp construction

CWWConfigApp::CWWConfigApp() {
  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWWConfigApp object

CWWConfigApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWWConfigApp initialization
//	Modified: 12/06/2001 by	MML	- Retrieving strings from Locomoto file.

BOOL CWWConfigApp::InitInstance() {
  AfxEnableControlContainer();

  //-------------------------------------------------------------------------
  //	Standard initialization
  //
  //	If you are not using these features and wish to reduce the size
  //	of your final executable, you should remove from the following
  //	the specific initialization routines you do not need.
  //-------------------------------------------------------------------------

  // Migrate old registry data to new location
  RegistryClass::Migrate_Registry(HKEY_LOCAL_MACHINE, OLD_APP_SUB_KEY, HKEY_CURRENT_USER, APP_SUB_KEY);

  //-------------------------------------------------------------------------
  // Get the Command line parameters.
  //-------------------------------------------------------------------------
  CString cmd(m_lpCmdLine);

  //=========================================================================
  // Init the strings.
  //=========================================================================
  int language = -1;

  if (cmd.Find("-French") != -1) {
    language = IDL_FRENCH;
  } else if (cmd.Find("-German") != -1) {
    language = IDL_GERMAN;
  } else if (cmd.Find("-Japanese") != -1) {
    language = IDL_JAPANESE;
  } else if (cmd.Find("-Korean") != -1) {
    language = IDL_KOREAN;
  } else if (cmd.Find("-Chinese") != -1) {
    language = IDL_CHINESE;
  } else if (cmd.Find("-English") != -1) {
    language = IDL_ENGLISH;
  }

  Locale_Init(language, "WWConfig.loc");

  //
  //
  //
  if (cmd.Find("-autoconfig") != -1) {
    AutoConfigSettings();
  } else if (cmd.Find("-driverversion") != -1) {
    CheckDriverVersion();
  } else {
    CWWConfigDlg dlg;
    m_pMainWnd = &dlg;
    int nResponse = dlg.DoModal();
    if (nResponse == IDOK) {
      // TODO: Place code here to handle when the dialog is
      //  dismissed with OK
    } else if (nResponse == IDCANCEL) {
      // TODO: Place code here to handle when the dialog is
      //  dismissed with Cancel
    }
  }

  //-------------------------------------------------------------------------
  // Free the strings.
  //-------------------------------------------------------------------------
  Locale_Restore();

  // Since the dialog has been closed, return FALSE so that we exit the
  //  application, rather than start the application's message pump.
  return FALSE;
}

int CWWConfigApp::ExitInstance() {
  // TODO: Add your specialized code here and/or call the base class

  CWinApp::ExitInstance();
  return GlobalExitValue;
}
