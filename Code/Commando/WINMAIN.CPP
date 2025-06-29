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

/***********************************************************************************************
 ***                            Confidential - Westwood Studios                              ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Commando                                                     *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/Commando/WINMAIN.CPP                         $*
 *                                                                                             *
 *                      $Author:: Steve_t                                                     $*
 *                                                                                             *
 *                     $Modtime:: 2/17/02 11:08a                                              $*
 *                                                                                             *
 *                    $Revision:: 85                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   WinMain -- Win32 Program Entry Point!                                                     *
 *   WIN_resize -- Surrender-required function which resizes the main window                   *
 *   WIN_set_fullscreen -- Surrender-required function for toggling full-screen mode           *
 *   Main_Window_Proc -- Windows Proc for the main game window                                 *
 *   Create_Main_Window -- Creates the main game window                                        *
 *   On_Focus_Loss -- this function is called when the application loses focus                 *
 *   On_Focus_Restore -- This function is called when the application gets focus               *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "winmain.h"
#include "win.h"
#include "WW3D.H"

#include "input.h"
#include "useroptions.h"

#include "buildinfo.h"
#include "dxdefs.h"
#include "verchk.h"
#include "devoptions.h"
#include "renegadedialogmgr.h"
#include "except.h"

#include "DirectInput.h"
#include "WebBrowser.h"
#include "wwmemlog.h"

#include "datasafe.h"

#include "registry.h"
#include "init.h"
#include "_globals.h"
#include "dx8wrapper.h"
#include "formconv.h"
#include "autostart.h"
#include "consolemode.h"
#include "slavemaster.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif //_DEBUG

#if (_MSC_VER >= 1200)
#pragma warning(push, 1)
#endif

#include <iostream>
#include "singletoninstancekeeper.h"
#include "packetmgr.h"

#if (_MSC_VER >= 1200)
#pragma warning(pop)
#endif

//----------------------------------------------------------------------------
//	Globals
//----------------------------------------------------------------------------
extern "C" {
HWND hWndMain;
bool WIN_fullscreen = true;
}

//----------------------------------------------------------------------------
//	Local functions
//----------------------------------------------------------------------------
static BOOL Create_Main_Window(HANDLE hInstance, int nCmdShow);
long FAR PASCAL Main_Window_Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void On_Focus_Loss(void);
void On_Focus_Restore(void);
void Split_Command_Line_Args(HINSTANCE instance, char *path_to_exe, char *command_line);
void Set_Working_Directory(char *old_path, char *new_path);
int Start_Application(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
void Set_Working_Directory(HINSTANCE hInstance);

#ifdef _MSC_VER
int Game_Main_Loop_Try();
#endif

#ifndef _MSC_VER
long Top_Level_Exception_Filter(EXCEPTION_POINTERS *e_info) {
  return (Exception_Handler(e_info->ExceptionRecord->ExceptionCode, e_info));
}
#endif //_MSC_VER

/***********************************************************************************************
 * WinMain -- Win32 Program Entry Point!                                                       *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * 	Standard WinMain inputs :-)                                                                *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * 	Standard WinMain output                                                                    *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/18/1997 GH  : Created.                                                                 *
 *=============================================================================================*/
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  WWMemoryLogClass::Init(); // This switches memlog from static to dynamic allocations mode

#ifdef _DEBUG
  /*
  **	Setup to track memory heap integrity and check for
  **	memory leaks. Output is dumped to the debug string console.
  */
  if (cDevOptions::CrtDbgEnabled.Is_True()) {

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  }

  /*
  ** Leak test
  */
  // char *flibble = new char [1024];
  // unsigned long *flibble2 = new unsigned long;
  // void *flibble3 = malloc(128);

  // flibble = flibble;
  // flibble2 = flibble2;
  // flibble3 = flibble3;
#endif //_DEBUG

  // Migrate old registry data to new location
  if (RegistryClass::Migrate_Registry(HKEY_LOCAL_MACHINE, OLD_APP_SUB_KEY, HKEY_CURRENT_USER, APP_SUB_KEY)) {
    WWDEBUG_SAY(("Migrated old registry settings.\r\n"));
  }

  cDevOptions::Init();
  cUserOptions::Init();

#ifdef WWDEBUG
  //
  // If necessary, disable packet optimizations
  //
  if (cDevOptions::PacketOptimizationsEnabled.Is_False()) {
    PacketManager.Disable_Optimizations();
  }
#endif // WWDEBUG

  if (!cUserOptions::Parse_Command_Line(lpCmdLine)) {
    return (0);
  }

  //
  // There's a couple of options we need for the FDS
  //
#ifdef FREEDEDICATEDSERVER
  if (!SlaveMaster.Am_I_Slave() && !ServerSettingsClass::Is_Server_Settings_File_Set()) {
    cUserOptions::Set_Server_INI_File("STARTSERVER=server.ini");
  }
  ConsoleBox.Set_Exclusive(true);
#endif // FREEDEDICATEDSERVER

  //
  //	Verify that we can execute (i.e. make sure there are no other instances running)
  //
  SingletonInstanceKeeperClass instance_keeper;
  if (instance_keeper.Verify_Safe_To_Execute() == false) {
    return 0;
  }

  //
  //	Start the game!
  //
  int retval = Start_Application(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
  return retval;
}

static bool Graphics_Settings_Trouble_Shooting() {
  RegistryClass registry(APPLICATION_SUB_KEY_NAME_DEBUG);
  if (!registry.Is_Valid())
    return true;

  int progress = registry.Get_Int(VALUE_NAME_GAME_INITIALIZATION_IN_PROGRESS, 0);
  if (progress) {
    StringClass options = "wwconfig.exe ";
    char *opts = options.Peek_Buffer();
    STARTUPINFO startup_info;
    ZeroMemory(&startup_info, sizeof(STARTUPINFO));
    startup_info.cb = sizeof(STARTUPINFO);
    PROCESS_INFORMATION process_info;
    CreateProcess(NULL, opts, NULL, NULL, FALSE, 0, NULL, NULL, &startup_info, &process_info);

    unsigned long exit_code = STILL_ACTIVE;
    unsigned res = 0;
    do {
      res = GetExitCodeProcess(process_info.hProcess, &exit_code);
      if (!res) {
        return true;
      }
      Sleep(100);
    } while (exit_code == STILL_ACTIVE);
    return !exit_code;
  }
  return true;
}

typedef DX_IDirect3DX *(WINAPI *Direct3DCreate8Type)(UINT SDKVersion);
static Direct3DCreate8Type Direct3DCreate8Ptr = NULL;
static HINSTANCE D3D8Lib = NULL;

static bool Video_Card_Driver_Check() {
  RegistryClass render_registry(APPLICATION_SUB_KEY_NAME_RENDER);
  if (!render_registry.Is_Valid())
    return true;

  int disabled = render_registry.Get_Int("DriverVersionCheckDisabled");
  if (disabled >= 87)
    return true;

  DX_IDirect3DX *d3d = NULL;
  DX_D3DCAPS tmp_caps;
  const DX_D3DCAPS *d3dcaps = NULL;
  DX_D3DADAPTER_IDENTIFIER adapter_id;

  // Init D3D
  Init_D3D_To_WW3_Conversion();

  D3D8Lib = LoadLibrary(DX_D3D_DLL);

  if (D3D8Lib != NULL) {
    Direct3DCreate8Ptr = (Direct3DCreate8Type)GetProcAddress(D3D8Lib, DX_D3D_CREATE_FUNC);
    if (Direct3DCreate8Ptr) {
      d3d = Direct3DCreate8Ptr(D3D_SDK_VERSION); // TODO: handle failure cases...
      if (!d3d) {
        FreeLibrary(D3D8Lib);
        return true;
      }
    } else {
      FreeLibrary(D3D8Lib);
      return (true);
    }
  } else {
    return (true);
  }

  // Select device. If there is already a device selected in the registry, use it.

  int current_adapter_index = D3DADAPTER_DEFAULT;

  //
  //	Load the render device settings from the registry
  //
  char device_name[256] = {0};
  render_registry.Get_String(VALUE_NAME_RENDER_DEVICE_NAME, device_name, sizeof(device_name));

  int adapter_count = d3d->GetAdapterCount();
  for (int adapter_index = 0; adapter_index < adapter_count; adapter_index++) {
    DX_D3DADAPTER_IDENTIFIER id;
    ::ZeroMemory(&id, sizeof(DX_D3DADAPTER_IDENTIFIER));
#if (DIRECT3D_VERSION < 0x0900)
    HRESULT res = d3d->GetAdapterIdentifier(adapter_index, D3DENUM_NO_WHQL_LEVEL, &id);
#else
    HRESULT res = d3d->GetAdapterIdentifier(adapter_index, 0, &id);
#endif
    // If device ok, check if it matches the currently set adapter name
    if (res == D3D_OK) {
      StringClass name(id.Description, true);
      if (name == device_name) {
        current_adapter_index = adapter_index;
        break;
      }
    }
  }

  if (FAILED(d3d->GetDeviceCaps(current_adapter_index, D3DDEVTYPE_HAL, &tmp_caps))) {
    d3d->Release();
    FreeLibrary(D3D8Lib);
    return true;
  }

  ::ZeroMemory(&adapter_id, sizeof(DX_D3DADAPTER_IDENTIFIER));
#if (DIRECT3D_VERSION < 0x0900)
  if (FAILED(d3d->GetAdapterIdentifier(current_adapter_index, D3DENUM_NO_WHQL_LEVEL, &adapter_id)))
#else
  if (FAILED(d3d->GetAdapterIdentifier(current_adapter_index, 0, &adapter_id)))
#endif
  {
    d3d->Release();
    FreeLibrary(D3D8Lib);

    return true;
  }

  d3dcaps = &tmp_caps;
  DX8Caps caps(d3d, *d3dcaps, WW3D_FORMAT_UNKNOWN, adapter_id);

  DX8Caps::DriverVersionStatusType status = caps.Get_Driver_Version_Status();

  d3d->Release();
  FreeLibrary(D3D8Lib);

  switch (status) {
  default:
  case DX8Caps::DRIVER_STATUS_GOOD:
  case DX8Caps::DRIVER_STATUS_OK:
  case DX8Caps::DRIVER_STATUS_UNKNOWN:
    render_registry.Set_Int("DriverVersionCheckDisabled", 87);
    return true;
    break;
  case DX8Caps::DRIVER_STATUS_BAD:
    break;
  }

  StringClass options = "wwconfig.exe -driverversion";
  char *opts = options.Peek_Buffer();
  STARTUPINFO startup_info;
  ZeroMemory(&startup_info, sizeof(STARTUPINFO));
  startup_info.cb = sizeof(STARTUPINFO);
  PROCESS_INFORMATION process_info;
  if (!CreateProcess(NULL, opts, NULL, NULL, FALSE, 0, NULL, NULL, &startup_info, &process_info)) {
    return true;
  }

  unsigned long exit_code = STILL_ACTIVE;
  unsigned res = 0;
  do {
    res = GetExitCodeProcess(process_info.hProcess, &exit_code);
    if (!res) {
      return true;
    }
    Sleep(100);
  } while (exit_code == STILL_ACTIVE);
  return !exit_code;
}

#ifdef _MSC_VER
int Game_Main_Loop_Try() {
  /*
  ** The __try/__except construct is part of the WIN32 interface. This is not the same
  ** as C++ exception handling. There is no additional code overhead required
  ** with this interface and the compilers exception handling options should be disabled
  ** to prevent the compiler generating additional stack unwinding code.
  */
  __try {
    return Game_Main_Loop();
  } __except (Exception_Handler(GetExceptionCode(), GetExceptionInformation())) {
    return EXIT_SUCCESS;
  };
}
#endif _MSC_VER

/***********************************************************************************************
 * Start_Application -- Handles WinMain execution.                                             *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * 	Standard WinMain inputs :-)                                                                *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * 	Standard WinMain output                                                                    *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/19/2001 PDS  : Created.                                                                *
 *=============================================================================================*/
int Start_Application(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow) {
  {
    WWMEMLOG(MEM_GAMEINIT);
    // LPSTR	command	= lpCmdLine;

    /*
    ** Set the working directory.
    */
    Set_Working_Directory(hInstance);

    //
    // TEMP Dev code - check the working folder is correct!
    //
    char tmp_buffer[256];
    char *tmp_ptr;
    if (!SearchPath("data", "always.dat", NULL, sizeof(tmp_buffer), tmp_buffer, &tmp_ptr)) {
      MessageBox(NULL, "Set working folder and try again...", "Invalid working folder", MB_OK);
      return 0;
    }

    /*
    ** Only do these checks if this isn't an auto-restart. If we are restarting then we must have run once OK already.
    *Right?
    */
    if (AutoRestart.Get_Restart_Flag() == false && !ConsoleBox.Is_Exclusive()) {
      if (!Video_Card_Driver_Check())
        return 0;
      if (!Graphics_Settings_Trouble_Shooting())
        return 0;
    }

    // Debug_Say(("Started logging at time %s", cMiscUtil::Get_Text_Time()));

    if (!Create_Main_Window(hInstance, nCmdShow))
      return 0;

    Register_Thread_ID(GetCurrentThreadId(), "Main Thread", true);
  }

  int exitCode = EXIT_SUCCESS;

#ifdef WWDEBUG
  if (cDevOptions::EnableExceptionHandler.Is_False()) {
    exitCode = Game_Main_Loop();
  } else {
#endif // WWDEBUG

    Register_Application_Exception_Callback(&Application_Exception_Callback);
    Register_Application_Version_Callback(&REBEL::BuildInfo::Get_Build_Info_String);

#ifdef _MSC_VER
    WWDEBUG_SAY(("Game_Main_Loop_Try\n"));
    exitCode = Game_Main_Loop_Try();
#else
  SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)&Top_Level_Exception_Filter);

  WWDEBUG_SAY(("Game_Main_Loop\n"));
  exitCode = Game_Main_Loop();

  SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)&Top_Level_Exception_Filter);
#endif // _MSC_VER

#ifdef WWDEBUG
  }
#endif // WWDEBUG

  Unregister_Thread_ID(GetCurrentThreadId(), "Main Thread");

  // Debug_Say(("Finished logging at time %s", cMiscUtil::Get_Text_Time()));

  return exitCode;
}

/***********************************************************************************************
 * Main_Window_Proc -- Windows Proc for the main game window                                   *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * 	Standard Windows Proc inputs                                                               *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * 	Standard Windows Proc output                                                               *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/18/1997 GH  : Created.                                                                 *
 *=============================================================================================*/
long FAR PASCAL Main_Window_Proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  static bool _reset = false;

  /*
  **	Pass this message through to the input handler. If the message
  **	was processed and requires no further action, then return with
  **	this information.
  */
  if (_TheWWUIInput && Input::Is_Console_Enabled() == false) {
    LRESULT result = 0;

    // DialogWalker->Process_Message(hwnd, message, wParam, lParam, result);

    if (_TheWWUIInput->ProcessMessage(hwnd, message, wParam, lParam, result)) {
      return result;
    }
  }

  switch (message) {
  /*
  ** basic management messages
  */
  case WM_ACTIVATEAPP:
    if (wParam && !GameInFocus) {
      WWDEBUG_SAY(("***** FOCUS GAINED *****\n"));
      GameInFocus = true;
      On_Focus_Restore();
    } else if (!wParam && GameInFocus) {
      WWDEBUG_SAY(("***** FOCUS LOST *****\n"));
      GameInFocus = false;
      On_Focus_Loss();
    }
    return (0);

  case WM_ERASEBKGND:
    return 1;

  case WM_PAINT:
    ValidateRect(hwnd, NULL);
    break;

  /*
  ** minimize/maximize
  */
  case WM_SYSKEYDOWN:

    if (wParam == VK_RETURN && ((lParam >> 16) & KF_ALTDOWN) && !((lParam >> 16) & KF_REPEAT)) {
      if (WIN_fullscreen) {
        WIN_fullscreen = false;
      } else {
        WIN_fullscreen = true;
      }
    }

    break;

  /*
  ** getch()
  */
  case WM_CHAR:
    // Debug_Say(("WM_CHAR %d\n", wParam));
    Input::Console_Add_Key(wParam);
    break;

  /*
  ** Main window creation
  */
  case WM_CREATE:
    break;

  /*
  ** Main window destruction
  */
  case WM_DESTROY:
    ReleaseCapture();
    PostQuitMessage(0);
    break;

  case WM_SYSCOMMAND:
    switch (wParam) {

    case SC_CLOSE:
      /*
      ** Windows sent us a close message. Probably in response to Alt-F4. Ignore it by
      ** pretending to handle the message and returning true;
      */
      return (0);

    case SC_KEYMENU:
      /*
      ** Ignore all "menu-activation" commands.
      */
      return (0);

    case SC_SCREENSAVE:
      /*
      ** Windoze is about to start the screen saver. If we just return without passing
      ** this message to DefWindowProc then the screen saver will not be allowed to start.
      */
      return (0);
    }
    break;

// Denzil - Using WM_xxxFOCUS messages to switch to windowed / fullscreen fails.
#if (0)
  case WM_KILLFOCUS: {
    if (WW3D::Is_Initted()) {

      // Get the current state of the redendering device
      int width = 0;
      int height = 0;
      int bits = 0;
      bool bwindowed = false;
      WW3D::Get_Device_Resolution(width, height, bits, bwindowed);

      // If we are running fullscreen, then toggle to 'windowed'
      // and minimze the window.
      if (bwindowed == false) {
        // Debug_Say(("WM_KILLFOCUS minimize"));
        WW3D::Set_Device_Resolution(-1, -1, -1, true);
        ::ShowWindow(hwnd, SW_MINIMIZE);
        _reset = true;
      }
    }
  } break;

  case WM_SETFOCUS:

    // If we need to reset the app to 'fullscreen' mode then
    // do so an restore the window.
    if (_reset == true) {
      WW3D::Set_Device_Resolution(-1, -1, -1, false);
      ::ShowWindow(hwnd, SW_RESTORE);
      _reset = false;
    }
    break;
#endif

  case WM_COMMAND:
    if (LOWORD(wParam) == IDM_TOGGLE_FULLSCREEN) {

      // Ask WW3D to toggle the fullscreen mode for us.
      WW3D::Toggle_Windowed();
    }

    break;

  default:
    break;
  }

  return DefWindowProc(hwnd, message, wParam, lParam);
}

/***********************************************************************************************
 * Create_Main_Window -- Creates the main game window                                          *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * 	hInstance -- Instance handle of the application                                            *
 * 	nCmdShow -- how the window is to be shown                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * 	TRUE = success, FALSE = failure                                                            *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/18/1997 GH  : Created.                                                                 *
 *=============================================================================================*/
static BOOL Create_Main_Window(HANDLE hInstance, int nCmdShow) {
  WNDCLASS wc;
  BOOL rc;

  ProgramInstance = (HINSTANCE)hInstance;

  if (!ConsoleBox.Is_Exclusive()) {
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wc.lpfnWndProc = Main_Window_Proc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = (HINSTANCE)hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = SingletonInstanceKeeperClass::Get_GUID();

    rc = RegisterClass(&wc);
    if (!rc)
      return FALSE;

    // Assume windowed mode
    MainWindow = CreateWindowEx(0, SingletonInstanceKeeperClass::Get_GUID(), "Renegade",
                                WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_CLIPCHILDREN, 0, 0, 0, 0, NULL, NULL,
                                ProgramInstance, NULL);

    if (!MainWindow) {
      return FALSE;
    }

    SetFocus(MainWindow);
  }

  return TRUE;
}

/***********************************************************************************************
 * On_Focus_Loss -- this function is called when the application loses focus                   *
 *                                                                                             *
 * INPUT:		Nothing                                                                        *
 *                                                                                             *
 * OUTPUT:		Nothing                                                                        *
 *                                                                                             *
 * WARNINGS:	None                                                                           *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/18/1997 GH  : Created.                                                                 *
 *=============================================================================================*/
void On_Focus_Loss(void) { DirectInput::Unacquire(); }

/***********************************************************************************************
 * On_Focus_Restore -- This function is called when the application gets focus                 *
 *                                                                                             *
 * INPUT:		Nothing                                                                        *
 *                                                                                             *
 * OUTPUT:		Nothing                                                                        *
 *                                                                                             *
 * WARNINGS:	None                                                                           *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/18/1997 GH  : Created.                                                                 *
 *=============================================================================================*/
void On_Focus_Restore(void) {
  if (WebBrowser::IsWebPageDisplayed() == false) {
    DirectInput::Acquire();
  }

  GameModeManager::Hide_Render_Frames(1); // Hide the first rendered frame
}

void Prog_End(void) {}

/***********************************************************************************************
 * Set_Working_Directory -- Sets current directory to be the same as the .exe                  *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Program instance                                                                  *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   11/6/2001 12:11PM ST : Created                                                            *
 *=============================================================================================*/
void Set_Working_Directory(HINSTANCE instance) {
  char path_to_exe[256];
  char drive[_MAX_DRIVE];
  char dir[_MAX_DIR];
  char path[_MAX_PATH];

  GetModuleFileName(instance, path_to_exe, sizeof(path_to_exe));
  _splitpath(path_to_exe, drive, dir, NULL, NULL);
  _makepath(path, drive, dir, NULL, NULL);
  SetCurrentDirectory(path);
}