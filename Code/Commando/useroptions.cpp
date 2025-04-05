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

//
// Filename:     useroptions.cpp
// Author:       Tom Spencer-Smith
// Date:         Dec 1999
// Description:
//

#include "useroptions.h"

#include "_globals.h"
#include "wwdebug.h"
#include "player.h"
#include "cnetwork.h"
#include "registry.h"
#include "player.h"
#include "playertype.h"
#include "bandwidth.h"
#include "bandwidthcheck.h"
#include <stdio.h>
#include "trim.h"
#include "singletoninstancekeeper.h"
#include "slavemaster.h"
#include "debug.h"
#include "rawfile.h"
#include "serversettings.h"
#include "autostart.h"
#include "consolemode.h"
#ifdef ENABLE_GAMESPY
#include "GameSpy_QnR.h"
#endif
#include "gamespyadmin.h"
#include "specialbuilds.h"
#include "useroptions.h"

extern char DefaultRegistryModifier[1024];

//
// Class statics
//
cRegistryBool cUserOptions::ShowNamesOnSoldier;
cRegistryBool cUserOptions::SkipQuitConfirmDialog;
cRegistryBool cUserOptions::SkipIngameQuitConfirmDialog;
cRegistryBool cUserOptions::CameraLockedToTurret;
cRegistryBool cUserOptions::PermitDiagLogging;

cRegistryInt cUserOptions::Sku;

cRegistryInt cUserOptions::BandwidthType;
cRegistryInt cUserOptions::BandwidthBps;

cRegistryInt cUserOptions::GameSpyBandwidthType;
cRegistryInt cUserOptions::PreferredGameSpyNic;
cRegistryString	cUserOptions::GameSpyNickname;
cRegistryInt cUserOptions::GameSpyQueryPort;
cRegistryInt cUserOptions::GameSpyGamePort;
cRegistryInt cUserOptions::SplashCount;
cRegistryBool cUserOptions::DoneClientBandwidthTest;

cRegistryInt cUserOptions::PreferredLanNic;
cRegistryInt cUserOptions::NetUpdateRate;
cRegistryFloat cUserOptions::ClientHintFactor;
cRegistryFloat cUserOptions::MaxFacingPenalty;
cRegistryFloat cUserOptions::IrrelevancePenalty;

cRegistryInt cUserOptions::ResultsLogNumber;


void cUserOptions::Init() {
	ShowNamesOnSoldier = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETOPTIONS, "ShowNamesOnSoldier",  true);
	SkipQuitConfirmDialog = cRegistryBool(APPLICATION_SUB_KEY_NAME_OPTIONS,	"SkipQuitConfirmDialog", false);
	SkipIngameQuitConfirmDialog = cRegistryBool(APPLICATION_SUB_KEY_NAME_OPTIONS, "SkipIngameQuitConfirmDialog", false);
	CameraLockedToTurret = cRegistryBool(APPLICATION_SUB_KEY_NAME_OPTIONS, "CameraLockedToTurret", false);
	PermitDiagLogging = cRegistryBool(APPLICATION_SUB_KEY_NAME_OPTIONS, "PermitDiagLogging", true);

	Sku = cRegistryInt(APPLICATION_SUB_KEY_NAME, "SKU", RENEGADE_BASE_SKU);

	BandwidthType = cRegistryInt(APPLICATION_SUB_KEY_NAME_NETOPTIONS, "BandwidthType", BANDWIDTH_AUTO);
	BandwidthBps = cRegistryInt(APPLICATION_SUB_KEY_NAME_NETOPTIONS, "BandwidthBps", 33600);

	GameSpyBandwidthType = cRegistryInt(APPLICATION_SUB_KEY_NAME_GAMESPY, "GameSpyBandwidthType", BANDWIDTH_AUTO);
	PreferredGameSpyNic = cRegistryInt(APPLICATION_SUB_KEY_NAME_GAMESPY, "PreferredGameSpyNic", 0);
	GameSpyNickname = cRegistryString(APPLICATION_SUB_KEY_NAME_GAMESPY, "GameSpyNickname", "");
	GameSpyQueryPort = cRegistryInt(APPLICATION_SUB_KEY_NAME_GAMESPY, "GameSpyQueryPort", 25300);
	GameSpyGamePort = cRegistryInt(APPLICATION_SUB_KEY_NAME_GAMESPY, "GameSpyGamePort", 4848);
	SplashCount = cRegistryInt(APPLICATION_SUB_KEY_NAME_GAMESPY, "SplashCount", 0);
	DoneClientBandwidthTest = cRegistryBool(APPLICATION_SUB_KEY_NAME_GAMESPY, "DoneClientBandwidthTest", false);

	PreferredLanNic = cRegistryInt(APPLICATION_SUB_KEY_NAME_NETOPTIONS, "PreferredLanNic", 0);
	NetUpdateRate = cRegistryInt(APPLICATION_SUB_KEY_NAME_NETOPTIONS, "NetUpdateRate", 10);
	ClientHintFactor = cRegistryFloat(APPLICATION_SUB_KEY_NAME_NETOPTIONS, "ClientHintFactor", 10.0f);
	MaxFacingPenalty = cRegistryFloat(APPLICATION_SUB_KEY_NAME_NETOPTIONS, "MaxFacingPenalty", 0.3f);
	IrrelevancePenalty = cRegistryFloat(APPLICATION_SUB_KEY_NAME_NETOPTIONS, "IrrelevancePenalty", 0.2f);

	ResultsLogNumber = cRegistryInt(APPLICATION_SUB_KEY_NAME_NETOPTIONS, "ResultsLogNumber", 1);
}


//-----------------------------------------------------------------------------
bool cUserOptions::Parse_Command_Line(LPCSTR command)
{
	WWASSERT(command != NULL);

	bool retcode = true;

	//
	// Convert to argv & argc for convenience.
	// First argument is supposed to be a pointer to the .EXE that is running
	// but we don't need that here.
	//
	int argc = 1;			//Set argument count to 1
	char * argv[20];		//Pointers to command line arguments
	argv[0] = NULL;		//Set 1st command line argument to point to full path

	//
	// Get pointers to command line arguments just like if we were in DOS
	//
	char *command_line = strdup(command);
	char *token = strtok(command_line, " ");
	while (argc < ARRAY_SIZE(argv) && token != NULL) {
		argv[argc++] = strtrim(token);
		token = strtok(NULL, " ");
		if (argc >= 19) {
			break;
		}
	}

	//
	// Loop through all the command line arguments.
	//

	char *cmd;
	for (int i=1 ; i<argc ; i++) {
		cmd = strupr(argv[i]);

		// Look for ip override.
		if (strstr(cmd, "IP=")) {
			extern ULONG g_ip_override;
			g_ip_override = ::inet_addr(strstr(cmd, "IP=") + 3);
			continue;
		}

		// See if multiple progrram instances are allowed.
		if (strstr(cmd, "MULTI")) {
			SingletonInstanceKeeperClass::Allow_Multiple_Instances(true);
			continue;
		}

		if (strstr(cmd, "REGMOD=")) {
			strcpy(DefaultRegistryModifier, strstr(cmd, "REGMOD=") + 7);
			#ifdef WWDEBUG
			OutputDebugString("Registry modifier on command line\n");
			#endif //WWDEBUG
			Reread();
			continue;
		}

		if (strstr(cmd, "SLAVE")) {
			SlaveMaster.Set_Slave_Mode(true);
			DebugManager::Set_Is_Slave(true);

			// Save out process ID so our master server can find us.
			char tempmod[512];
			strcpy(tempmod, DefaultRegistryModifier);
			strcpy(DefaultRegistryModifier, "");
			RegistryClass reg(APPLICATION_SUB_KEY_NAME);
			if (reg.Is_Valid()) {
				reg.Set_Int("ProcessId", GetCurrentProcessId());
			}
			strcpy(DefaultRegistryModifier, tempmod);

			RegistryClass::Set_Read_Only(true);
			continue;
		}

		if (strstr(cmd, "STARTSERVER=")) {
			Set_Server_INI_File(cmd);
			continue;
		}

		if (strstr(cmd, "GAMESPYSERVER=")) {
			char server_config_file[MAX_PATH];
			strcpy(server_config_file, strstr(cmd, "GAMESPYSERVER=") + 14);
			WWDEBUG_SAY(("Set to load gamespy server settings from config file %s\n", server_config_file));
			RawFileClass file(server_config_file);
			if (file.Is_Available()) {
				ServerSettingsClass::Set_Settings_File_Name(server_config_file);

				RegistryClass registry (APPLICATION_SUB_KEY_NAME_WOLSETTINGS);
				if (registry.Is_Valid ()) {
					registry.Set_Int(AutoRestartClass::REG_VALUE_AUTO_RESTART_FLAG, 1);
					registry.Set_Int(AutoRestartClass::REG_VALUE_AUTO_RESTART_TYPE, 0);
				}
				cGameSpyAdmin::Set_Is_Server_Gamespy_Listed(true);
#ifdef ENABLE_GAMESPY
				GameSpyQnR.Enable_Reporting(true);
#endif
			}
			continue;
		}

		if (strstr(cmd, "NODX")) {
			ConsoleBox.Set_Exclusive(true);
			continue;
		}
	}

	free(command_line);


#ifndef BETACLIENT

	//GAMESPY
	//
	// Gamespy params follow different param format
	//

	char *tmpstr = strdup(command);
	tmpstr = _strupr(tmpstr);

	char * ip_param = ::strstr(tmpstr, "+CONNECT");
	if (ip_param != NULL) {
		ip_param += ::strlen("+connect");

		USHORT port = 4848;
		DWORD addr = 0;
		char ipaddr[300] = "";
		::sscanf(ip_param, "%s", ipaddr);
		strtrim(ipaddr);

		char *tport = strchr(ipaddr, ':');
		if (tport) {
			*tport++ = 0;
			if (atoi(tport) != 0 || atoi(tport) > 0) {
				port = atoi(tport);
			}
		}

		addr = ::inet_addr(ipaddr);

		cGameSpyAdmin::Set_Game_Host_Ip(addr);
		cGameSpyAdmin::Set_Game_Host_Port(port);
		cGameSpyAdmin::Set_Is_Launch_From_Gamespy_Requested(true);
	}

	char * nickname_param = ::strstr(tmpstr, "+NETPLAYERNAME");
	if (nickname_param != NULL) {
		nickname_param = (char *)(command + (nickname_param-tmpstr));
		nickname_param += ::strlen("+NetPlayerName");

		char * start = nickname_param;
		// Strip leading spaces
		while (*start && *start == ' ') start++;
		// if we find a space before a quote then space delimit
		while (*start && *start != '"' && *start != ' ') {
			start++;
		}
		char * end = start;
		// Match the end quote
		if (*start && *start != ' ') {
			start++;
			end = start;
			while (*end && *end != '"') {
				end++;
			}
		}

		// Couldn't find any quotes, so delimit by spaces
		if (start == end) {
			start = nickname_param;
			while (*start && *start == ' ') start++;
			end = strchr(start, ' ');
			if (!end) end = start + strlen(start);
		}
		
		char nickname2[300] = "";
		::strncpy(nickname2, start, end - start);
		nickname2[end - start] = 0;

		cUserOptions::GameSpyNickname.Set(nickname2);
		cGameSpyAdmin::Set_Is_Launch_From_Gamespy_Requested(true);
	}

	char * password_param = ::strstr(tmpstr, "+PASS");
	if (password_param != NULL) {
		char *tmp_param = ::strstr(tmpstr, "+PASSWORD");
		if (tmp_param) {
			password_param = (char *)(command + (tmp_param-tmpstr));
			password_param += ::strlen("+PASSWORD");
		} else {
			password_param = (char *)(command + (password_param-tmpstr));
			password_param += ::strlen("+PASS");
		}

		char * start = password_param;
		// Strip leading spaces
		while (*start && *start == ' ') start++;
		// if we find a space before a quote then space delimit
		while (*start && *start != '"' && *start != ' ') {
			start++;
		}
		char * end = start;
		// Match the end quote
		if (*start && *start != ' ') {
			start++;
			end = start;
			while (*end && *end != '"') {
				end++;
			}
		}

		// Couldn't find any quotes, so delimit by spaces
		if (start == end) {
			start = password_param;
			while (*start && *start == ' ') start++;
			end = strchr(start, ' ');
			if (!end) end = start + strlen(start);
		}

		char password[300] = "";
		::strncpy(password, start, end - start);
		password[end - start] = 0;

		WideStringClass wide_password;
		wide_password.Convert_From(password);
		cGameSpyAdmin::Set_Password_Attempt(wide_password);
	}

	free(tmpstr);

#endif // !BETACLIENT


	// Return true if command line options scanned OK.
	return(retcode);
}



//-----------------------------------------------------------------------------
void cUserOptions::Set_Server_INI_File(char *cmd_line_entry)
{
	char server_config_file[MAX_PATH];
	strcpy(server_config_file, strstr(cmd_line_entry, "STARTSERVER=") + 12);
	WWDEBUG_SAY(("Set to load server settings from config file %s\n", server_config_file));
	RawFileClass file(server_config_file);
	if (file.Is_Available()) {
		ServerSettingsClass::Set_Settings_File_Name(server_config_file);

		RegistryClass registry (APPLICATION_SUB_KEY_NAME_WOLSETTINGS);
		if (registry.Is_Valid ()) {
			registry.Set_Int(AutoRestartClass::REG_VALUE_AUTO_RESTART_FLAG, 1);
			registry.Set_Int(AutoRestartClass::REG_VALUE_AUTO_RESTART_TYPE, 1);
		}
	}
}

//-----------------------------------------------------------------------------
void cUserOptions::Set_Bandwidth_Type(BANDWIDTH_TYPE_ENUM bandwidth_type)
{
	if (cGameSpyAdmin::Is_Gamespy_Game()) {
		GameSpyBandwidthType.Set(bandwidth_type);
	} else {
		BandwidthType.Set(bandwidth_type);
	}

	if (bandwidth_type != BANDWIDTH_CUSTOM) {
		if (bandwidth_type == BANDWIDTH_AUTO && BandwidthCheckerClass::Got_Bandwidth()) {
			ULONG bps = BandwidthCheckerClass::Get_Upstream_Bandwidth();
			WWASSERT(bps > 0);
			BandwidthBps.Set(bps);
		} else {
			ULONG bps = cBandwidth::Get_Bandwidth_Bps_From_Type(bandwidth_type);
			WWASSERT(bps > 0);
			BandwidthBps.Set(bps);
		}
	}
}

//-----------------------------------------------------------------------------
BANDWIDTH_TYPE_ENUM cUserOptions::Get_Bandwidth_Type(void)
{
	if (cGameSpyAdmin::Is_Gamespy_Game()) {
		return (BANDWIDTH_TYPE_ENUM) GameSpyBandwidthType.Get();
	} else {
		return (BANDWIDTH_TYPE_ENUM) BandwidthType.Get();
	}
}

//-----------------------------------------------------------------------------
void cUserOptions::Set_Bandwidth_Bps(int bandwidth_bps)
{
	WWASSERT(bandwidth_bps > 0);

	if (cGameSpyAdmin::Is_Gamespy_Game()) {
		GameSpyBandwidthType.Set(BANDWIDTH_CUSTOM);
	} else {
		BandwidthType.Set(BANDWIDTH_CUSTOM);
	}

	BandwidthBps.Set(bandwidth_bps);
}




//-----------------------------------------------------------------------------
void cUserOptions::Reread(void)
{
	Sku.Set(RegistryClass(APPLICATION_SUB_KEY_NAME).Get_Int("SKU", Sku.Get()));
	BandwidthType.Set(RegistryClass(APPLICATION_SUB_KEY_NAME_NETOPTIONS).Get_Int("BandwidthType", BandwidthType.Get()));
	BandwidthBps.Set(RegistryClass(APPLICATION_SUB_KEY_NAME_NETOPTIONS).Get_Int("BandwidthBps", BandwidthBps.Get()));
	GameSpyBandwidthType.Set(RegistryClass(APPLICATION_SUB_KEY_NAME_GAMESPY).Get_Int("GameSpyBandwidthType", GameSpyBandwidthType.Get()));
}













/*
cRegistryInt cUserOptions::GameListFilterMaxPing(				APPLICATION_SUB_KEY_NAME_NETOPTIONS, "GameListFilterMaxPing",								9999);
cRegistryInt cUserOptions::GameListFilterMinPlayersPresent(	APPLICATION_SUB_KEY_NAME_NETOPTIONS, "GameListFilterMinPlayersPresent",					0);
cRegistryInt cUserOptions::GameListFilterMaxPlayersPresent(	APPLICATION_SUB_KEY_NAME_NETOPTIONS, "GameListFilterMaxPlayersPresent",					99);
cRegistryInt cUserOptions::GameListFilterMaxPlayersPermitted( APPLICATION_SUB_KEY_NAME_NETOPTIONS, "GameListFilterMaxPlayersPermitted",			99);
cRegistryBool cUserOptions::GameListFilterShowPrivateGames(	APPLICATION_SUB_KEY_NAME_NETOPTIONS, "GameListFilterShowPrivateGames",					true);
cRegistryBool cUserOptions::GameListFilterShowOnlyDedicatedGames(	APPLICATION_SUB_KEY_NAME_NETOPTIONS, "GameListFilterShowOnlyDedicatedGames",	false);
cRegistryBool cUserOptions::GameListFilterShowOnlyGamesIRankFor(	APPLICATION_SUB_KEY_NAME_NETOPTIONS, "GameListFilterShowOnlyGamesIRankFor",	false);
*/

		/*
		//
		// Gamespy client launch params.
		// All 3 must be specified.
		// Example: Renegade.exe GAMESPY_IPADDR=192.168.10.100 GAMESPY_PORT=3333 GAMESPY_NICKNAME="Bob 1234"
		//
		LPCSTR param = NULL;
		char * value = NULL;

		param = "GAMESPY_IPADDR=";
		value = ::strstr(cmd, param);
		if (value != NULL) {
			value += ::strlen(param);
			ULONG ip = ::inet_addr(value);
			cGameSpyAdmin::Set_Game_Host_Ip(ip);
			cGameSpyAdmin::Set_Is_Launch_From_Gamespy_Requested(true);
			continue;
		}

		param = "GAMESPY_PORT=";
		value = ::strstr(cmd, param);
		if (value != NULL) {
			value += ::strlen(param);
			USHORT port = (USHORT)::atol(value);
			cGameSpyAdmin::Set_Game_Host_Port(port);
			cGameSpyAdmin::Set_Is_Launch_From_Gamespy_Requested(true);
			continue;
		}

		param = "GAMESPY_NICKNAME=";
		value = ::strstr(cmd, param);
		if (value != NULL) {
			value += ::strlen(param);
			WideStringClass nickname;
			char temp[200] = "";
			char seps[]   = "\"";
			char * start_token = ::strtok(value, seps);
			if (start_token != NULL) {
				start_token++;
			}
			char * end_token = ::strtok(NULL, seps);
			if (end_token != NULL && end_token > start_token) {
				::strncpy(temp, start_token, end_token - start_token);
				temp[end_token - start_token] = 0;
			}

			nickname.Convert_From(temp);
			cGameSpyAdmin::Set_Player_Nickname(nickname);
			cGameSpyAdmin::Set_Is_Launch_From_Gamespy_Requested(true);
			continue;
		}
		*/

		/*
		char nickname[300] = "";
		::sscanf(nickname_param, "%s", nickname);
		nickname[::strlen(nickname) - 1] = ' ';
		nickname[0] = ' ';

		char nickname2[300] = "";
		::sscanf(nickname, "%s", nickname2);
		*/

		/*
		char seps[]   = "\"";
		char * start_token = ::strtok(nickname_param, seps);
		if (start_token != NULL) {
			start_token++;
		}
		char * end_token = ::strtok(NULL, seps);
		char nickname2[300] = "";
		if (end_token != NULL && end_token > start_token) {
			char nickname2[300] = "";
			::strncpy(nickname2, start_token, end_token - start_token);
			nickname2[end_token - start_token] = 0;
		}
		*/

		/*
		WideStringClass wide_nickname;
		wide_nickname.Convert_From(nickname2);
		cGameSpyAdmin::Set_Player_Nickname(wide_nickname);
		*/