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

/*****************************************************************************\
          C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S
*******************************************************************************
 File:       main.cpp
 Programmer: Neal Kettler

 StartDate:  Feb  6, 1998
 LastUpdate: Feb 10, 1998
-------------------------------------------------------------------------------

 Launcher application for games/apps using the chat API.  This should be
 run by the user and it will start the actual game executable.  If a patch
 file has been downloaded the patch will be applied before starting the game.

 This does not download patches or do version checks, the game/app is responsible
 for that.  This just applies patches that are in the correct location for the
 game.  All patches should be in the "Patches" folder of the app.

 The launcher should have a config file (launcher.cfg) so it knows which apps
 should be checked for patches. The file should look like this:

 # comment
 # RUN = the game to launch
 RUN = . notepad.exe        # directory and app name
 # RUN2 = the 2nd launcher if using one
 RUN2 = . wordpad.exe
 # FLAG = time in seconds of when to stop using 2nd launcher
 FLAG = 996778113
 #
 # Sku's to check for patches
 #
 SKU1 = 1100 SOFTWARE\Westwood\WOnline      # skus and registry keys
 SKU2 = 1234 SOFTWARE\Westwood\FakeGame

\*****************************************************************************/


#include "dialog.h"
#include "patch.h"
#include "findpatch.h"
#include "process.h"

#include "wdebug.h"
#include "monod.h"
#include "filed.h"
#include "configfile.h"
#include <windows.h>

#ifdef COPY_PROTECT
#include "Protect.h"
#include <Debug\DebugPrint.h>
#endif

#define UPDATE_RETVAL 123456789  // if a program returns this it means it wants to check for patches

#include "..\combat\specialbuilds.h"

/*
#ifdef FREEDEDICATEDSERVER

#define APPLICATION_SUB_KEY_NAME 				"Software\\Westwood\\RenegadeFDS\\"

#else  //FREEDEDICATEDSERVER

#ifdef MULTIPLAYERDEMO
#define APPLICATION_SUB_KEY_NAME 				"Software\\Westwood\\RenegadeMPDemo\\"
#else  //MULTIPLAYERDEMO
#define APPLICATION_SUB_KEY_NAME 				"Software\\Westwood\\Renegade\\"
#endif //MULTIPLAYERDEMO

#endif //FREEDEDICATEDSERVER
*/

#if	defined(FREEDEDICATEDSERVER)
#define APPLICATION_SUB_KEY_NAME 				"Software\\Westwood\\RenegadeFDS\\"
#elif defined(MULTIPLAYERDEMO)
#define APPLICATION_SUB_KEY_NAME 				"Software\\Westwood\\RenegadeMPDemo\\"
#else
#define APPLICATION_SUB_KEY_NAME 				"Software\\Westwood\\Renegade\\"
#endif



#define APPLICATION_SUB_KEY_NAME_WOLSETTINGS "WOLSettings\\"
#define APPLICATION_SUB_KEY_NAME_AUTOSTART 	"AutoRestartFlag"


void CreatePrimaryWin(char *prefix);
void myChdir(char *path);
bool Get_Restart_Flag(Process &proc, bool &slave);

void RunGame(char *thePath, ConfigFile &config, Process &proc)
{
	char patchFile[MAX_PATH];
	bool launchgame = true;

	// MDC 8/23/2001 Wait 3 seconds for the installer to release the mutex
	//
	//
	// TO_FIX - Use installer mutex to see when installer has gone away.
	//Sleep(3000);

	while (true)
	{
		int skuIndex;

		while ((skuIndex = Find_Patch(patchFile, MAX_PATH, config)) != 0)
		{
			//
			// If there is a patch and we are a slave server then we need to exit quick so the master server can apply it.
			//
			bool slave = false;
			bool restart = Get_Restart_Flag(proc, slave);

			if (!restart || !slave) {
				// Pass in the restart flag so that the patch code knows not to bring up the changes dialog.
				Apply_Patch(patchFile, config, skuIndex, !restart);
				launchgame = true;
			} else {
				launchgame = false;
			}
		}

		// launch the game if first pass, or found a patch
		if (launchgame)
		{
			// don't relaunch unless we find a patch (or checking for patches)
			launchgame = false;
			myChdir(thePath);

#ifndef COPY_PROTECT
			Create_Process(proc);
#else // COPY_PROTECT

#ifdef OLDWAY
			Protect protect;
			Create_Process(proc);
			protect.SendMappedFileHandle(proc.hProcess, proc.dwThreadID);
#else

			InitializeProtect();
			Create_Process(proc);
			SendProtectMessage(proc.hProcess, proc.dwThreadID);

#endif
#endif // COPY_PROTECT

			DWORD exit_code;
			Wait_Process(proc, &exit_code);

			// Relaunch if the game crashed unexpectedly (the auto restart flag is set).
			bool slave = false;
			if (Get_Restart_Flag(proc, slave)) {
				launchgame = true;
			} else {

#ifndef MULTIPLAYERDEMO
				if (exit_code == UPDATE_RETVAL)
				{
					// They just want to check for patches
					launchgame = true;

					// Start patchgrabber
					Process patchgrab;
					strcpy(patchgrab.directory,proc.directory);  // same dir as game
					strcpy(patchgrab.command,"patchget.dat");  // the program that grabs game patches
					strcpy(patchgrab.args,"");
					Create_Process(patchgrab);
					Wait_Process(patchgrab);  // wait for completion
				}
#endif //MULTIPLAYERDEMO
			}
#ifdef COPY_PROTECT
#ifndef OLDWAY
			ShutdownProtect();
#endif
#endif
		}
		else
		{
			// Don't delete patches if we are a slave server. That's the master servers job.
			bool slave = false;
			bool restart = Get_Restart_Flag(proc, slave);
			if (!slave) {
				Delete_Patches(config);  // delete all patches
			}
			break;
		}
	}
}

// The other launcher will handle itself.  Just fire and forget.
void RunLauncher(char *thePath, Process &proc)
{
	myChdir(thePath);
	Create_Process(proc);
}

//
// Called by WinMain
//
int main(int argc, char *argv[])
{
	char patchFile[MAX_PATH];

	char cwd[MAX_PATH];  // save current directory before game start
	_getcwd(cwd, MAX_PATH);

	InitCommonControls();

	// Goto the folder where launcher is installed
	myChdir(argv[0]);

	// extract the program name from argv[0].  Change the extension to
	//   .lcf (Launcher ConFig).  This is the name of our config file.
	char configName[MAX_PATH + 3];
	strcpy(configName, argv[0]);
	char* extension = configName;
	char* tempptr;

	while ((tempptr = strchr(extension + 1, '.')))
	{
		extension = tempptr;
	}

	if (*extension == '.')
	{
		*extension = 0;
	}

#ifdef DEBUG
	///MonoD outputDevice;
	char debugFile[MAX_PATH + 3];
	strcpy(debugFile, configName);
	strcat(debugFile, ".txt");
//	strcpy(debugLogName, strrchr(configName, '\\'));
//	strcat(debugLogName, "Log");
	FileD outputDevice(debugFile);
	MsgManager::setAllStreams(&outputDevice);
	DBGMSG("Launcher initialized");
#endif

	strcat(configName, ".lcf");

	DBGMSG("Config Name: "<<configName);

	ConfigFile config;
	FILE* in = fopen(configName, "r");

	if (in == NULL)
	{
		MessageBox(NULL,"You must run the game from its install directory.",
			"Launcher config file missing",MB_OK);
		exit(-1);
	}

	bit8 ok = config.readFile(in);
	fclose(in);

	if (ok == FALSE)
	{
		MessageBox(NULL,"File 'launcher.cfg' is corrupt","Error",MB_OK);
		exit(-1);
	}

	// Load process info
	Process proc;
	Read_Process_Info(config,proc);

	// Possible 2nd EXE
	Process proc2;
	int hasSecondEXE = Read_Process_Info(config,proc2,"RUN2");

	DBGMSG("Read process info");

	for (int i = 1; i < argc; i++)
	{
		strcat(proc.args, " ");
		strcat(proc.args, argv[i]);

		if (hasSecondEXE)
		{
			strcat(proc2.args, " ");
			strcat(proc2.args, argv[i]);
		}
	}

	DBGMSG("ARGS: "<<proc.args);

	// Just spawn the patchgrabber & apply any patches it downloads
	if ((argc >= 2) && (strcmp(argv[1], "GrabPatches") == 0))
	{
		// Start patchgrabber
		Process patchgrab;

		// same dir as game
		strcpy(patchgrab.directory, proc.directory);

		// the program that grabs game patches
		strcpy(patchgrab.command, "patchget.dat");
		strcpy(patchgrab.args, "");

		Create_Process(patchgrab);
		Wait_Process(patchgrab);

		// Apply any patches I find
		int skuIndex;

		while ((skuIndex = Find_Patch(patchFile, MAX_PATH, config)) != 0)
		{
			Apply_Patch(patchFile, config, skuIndex);
		}

		myChdir(cwd);
		return 0;
	}

	// Look for patch file(s) to apply
	bool launchgame = true;

	time_t cutoffTime = 0;
	if (hasSecondEXE)
	{
		Wstring timeStr;
		if (config.getString("FLAG", timeStr)!=FALSE)
		{
			cutoffTime = atoi(timeStr.get());
		}

		if (cutoffTime == 0)
		{
			// We didn't have the FLAG parameter; somebody's been hacking.  No game for you!  Bad hacker!
			DBGMSG("Saw cutoffTime of 0; real time is " << time(NULL));
			MessageBox(NULL,"File 'launcher.cfg' is corrupt","Error",MB_OK);
			exit(-1);
		}

		if (time(NULL) > cutoffTime)
		{
			// The future is now!  Just run the game.
			RunGame(argv[0], config, proc);
		}
		else
		{
			// Its still early in the product's lifetime, so run the 2nd (SafeDisk'd) launcher.
			// We don't have to wait around since it'll do the entire talk to game, look for patches,
			// etc. deal.
			RunLauncher(argv[0], proc2);
		}
	}
	else
	{
		// We're the second (or only) launcher, so act normally
		RunGame(argv[0], config, proc);
	}

	myChdir(cwd);

	// Exit normally
	return 0;
}


//
// Create a primary window
//
void CreatePrimaryWin(char *prefix)
{
	char name[256];
	sprintf(name, "launcher_%s", prefix);

	DBGMSG("CreatePrimary: "<<name);

	/*
	** set up and register window class
	*/
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;            // Don't need any extra class data
	wc.cbWndExtra = 0;            // No extra win data
	wc.hInstance = Global_instance;
	wc.hIcon=LoadIcon(Global_instance, MAKEINTRESOURCE(IDI_ICON));
	wc.hCursor = NULL;  /////////LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = NULL;
	wc.lpszMenuName = name;
	wc.lpszClassName = name;
	RegisterClass(&wc);

	/*
	** create a window
	*/
	HWND hwnd = CreateWindowEx(WS_EX_TOPMOST, name, name, WS_POPUP, 0, 0,
		GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
		NULL, NULL, Global_instance, NULL);

	if(!hwnd)
	{
		DBGMSG("Couldn't make window!");
	}
	else
	{
		DBGMSG("Window created!");
	}
}


//void DestroyPrimaryWin(void)
//{
//  DestroyWindow(PrimaryWin);
//  UnregisterClass(classname);
//}



//
// If given a file, it'll goto it's directory.  If on a diff drive,
//   it'll go there.
//
void myChdir(char *path)
{
	char drive[10];
	char dir[255];
	char file[255];
	char ext[64];
	char filepath[513];
	int  abc;

	_splitpath( path, drive, dir, file, ext );
	_makepath ( filepath,   drive, dir, NULL, NULL );

	if ( filepath[ strlen( filepath ) - 1 ] == '\\' )
	{
		filepath[ strlen( filepath ) - 1 ] = '\0';
	}
	abc = (unsigned)( toupper( filepath[0] ) - 'A' + 1 );
	if ( !_chdrive( abc ))
	{
		abc = chdir( filepath );  // Will fail with ending '\\'
	}
	// should be in proper folder now....
}




/***********************************************************************************************
 * Get_Restart_Flag -- Get AutoRestartFlag from the registry                                   *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   State of flag                                                                     *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   11/5/2001 7:14PM ST : Created                                                             *
 *=============================================================================================*/
bool Get_Restart_Flag(Process &proc, bool &slave)
{
	HKEY key;
	char args[1024];
	strcpy(args, proc.args);
	strupr(args);

	/*
	** Is this a slave server according to the command line?
	*/
	if (strstr(args, "SLAVE")) {
		slave = true;
	} else {
		slave = false;
	}

	char registry_modifier[256];

	/*
	** Use a modified registry path if one was specified on the games command line.
	*/
	char *regmod = strstr(args, "REGMOD=");
	if (regmod) {
		strcpy(registry_modifier, regmod + 7);
	}

	char regpath[1024];
	strcpy(regpath, APPLICATION_SUB_KEY_NAME);
	if (regmod) {
		strcat(regpath, registry_modifier);
		strcat(regpath, "\\");
	}
	strcat(regpath, APPLICATION_SUB_KEY_NAME_WOLSETTINGS);

	int result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, regpath, 0, KEY_ALL_ACCESS, &key);

	if (result == ERROR_SUCCESS) {

		unsigned long type;
		unsigned long data = 0;
		unsigned long data_len = sizeof(data);

		if ((RegQueryValueEx(key, APPLICATION_SUB_KEY_NAME_AUTOSTART, NULL, &type, (LPBYTE)&data, &data_len) == ERROR_SUCCESS) && (type == REG_DWORD)) {
			return((data != 0) ? true : false);
		}
	}
	return(false);
}