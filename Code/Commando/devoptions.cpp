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
// Filename:     devoptions.cpp
// Author:       Tom Spencer-Smith
// Date:         Dec 1999
// Description:
//

#include "devoptions.h" // I WANNA BE FIRST!

#include "_globals.h"
#include "wwdebug.h"
#include "player.h"
#include "registry.h"

#ifdef WWDEBUG
cRegistryBool cDevOptions::ShowGodStatus;
cRegistryBool cDevOptions::ShowSoldierData;
cRegistryBool cDevOptions::ShowVehicleData;
cRegistryBool cDevOptions::ShowDoorData;
cRegistryBool cDevOptions::ShowElevatorData;
cRegistryBool cDevOptions::ShowDSAPOData;
cRegistryBool cDevOptions::ShowPowerupData;
cRegistryBool cDevOptions::ShowBuildingData;
cRegistryBool cDevOptions::ShowSpawnerData;
cRegistryBool cDevOptions::ShowImportStates;
cRegistryBool cDevOptions::ShowImportStatesSV;
cRegistryBool cDevOptions::ShowServerRhostData;
cRegistryBool cDevOptions::ShowClientRhostData;
//cRegistryBool cDevOptions::ShowPacketGraphs);

cRegistryBool cDevOptions::PacketsSentServer;
cRegistryBool cDevOptions::PacketsSentClient;
cRegistryBool cDevOptions::PacketsRecdServer;
cRegistryBool cDevOptions::PacketsRecdClient;
cRegistryBool cDevOptions::AvgSizePacketsSentServer;
cRegistryBool cDevOptions::AvgSizePacketsSentClient;
cRegistryBool cDevOptions::AvgSizePacketsRecdServer;
cRegistryBool cDevOptions::AvgSizePacketsRecdClient;
cRegistryBool cDevOptions::BytesSentServer;
cRegistryBool cDevOptions::BytesSentClient;
cRegistryBool cDevOptions::BytesRecdServer;
cRegistryBool cDevOptions::BytesRecdClient;

cRegistryBool cDevOptions::WwnetPacketsSentServer;
cRegistryBool cDevOptions::WwnetPacketsSentClient;
cRegistryBool cDevOptions::WwnetPacketsRecdServer;
cRegistryBool cDevOptions::WwnetPacketsRecdClient;
cRegistryBool cDevOptions::WwnetAvgSizePacketsSentServer;
cRegistryBool cDevOptions::WwnetAvgSizePacketsSentClient;
cRegistryBool cDevOptions::WwnetAvgSizePacketsRecdServer;
cRegistryBool cDevOptions::WwnetAvgSizePacketsRecdClient;
cRegistryBool cDevOptions::WwnetBytesSentServer;
cRegistryBool cDevOptions::WwnetBytesSentClient;
cRegistryBool cDevOptions::WwnetBytesRecdServer;
cRegistryBool cDevOptions::WwnetBytesRecdClient;

cRegistryBool cDevOptions::ShowPriorities;
cRegistryBool cDevOptions::ShowBandwidth;
cRegistryBool cDevOptions::ShowLatency;
cRegistryBool cDevOptions::ShowLastContact;
cRegistryBool cDevOptions::ShowListSizes;
cRegistryBool cDevOptions::ShowListTimes;
cRegistryBool cDevOptions::ShowListPacketSizes;
//cRegistryBool cDevOptions::ShowBandwidthBudgetOut;
cRegistryBool cDevOptions::ShowWatchList;
cRegistryBool cDevOptions::ShowWolLocation;
cRegistryBool cDevOptions::ShowDiagnostics;
cRegistryBool cDevOptions::ShowMenuStack;
cRegistryBool cDevOptions::ShowIpAddresses;
cRegistryBool cDevOptions::ShowClientFps;
cRegistryBool cDevOptions::ShowId;
cRegistryBool cDevOptions::ShowPing;
cRegistryBool cDevOptions::ShowObjectTally;
cRegistryBool cDevOptions::ShowInactivePlayers;
cRegistryBool cDevOptions::ShowGameSpyAuthState;

cRegistryInt cDevOptions::DesiredFrameSleepMs;
cRegistryInt cDevOptions::SimulatedPacketLossPc;
cRegistryInt cDevOptions::SimulatedPacketDuplicationPc;
cRegistryInt cDevOptions::SimulatedLatencyRangeMsLower;
cRegistryInt cDevOptions::SimulatedLatencyRangeMsUpper;
cRegistryInt cDevOptions::SpamCount;

cRegistryBool cDevOptions::SoundEffectOnAssert;
cRegistryBool cDevOptions::DisplayLogfileOnAssert;
cRegistryBool cDevOptions::BreakToDebuggerOnAssert;
cRegistryBool cDevOptions::ShutdownInputOnAssert;
cRegistryBool cDevOptions::PreloadAssets;
cRegistryBool cDevOptions::FilterLevelFiles;
cRegistryBool cDevOptions::IBelieveInGod;
cRegistryBool cDevOptions::LogDataSafe;
cRegistryBool cDevOptions::EnableExceptionHandler;
cRegistryBool cDevOptions::ShowThumbnailPreInitDialog;
cRegistryBool cDevOptions::CrtDbgEnabled;
cRegistryBool cDevOptions::PacketOptimizationsEnabled;
cRegistryBool cDevOptions::ShowMoney;
cRegistryBool cDevOptions::ExtraNetDebug;
cRegistryBool cDevOptions::ExtraModemBandwidthThrottling;

cBoolean cDevOptions::GoToMainMenu;

#endif // WWDEBUG

cBoolean cDevOptions::QuickFullExit;

cRegistryBool cDevOptions::ExitThreadOnAssert;
cRegistryBool cDevOptions::CompareExeVersionOnNetwork;

cRegistryBool cDevOptions::UseNewTCADO;
cRegistryBool cDevOptions::ShowFps;

// cRegistryBool::DoThumbnailPreInit;


void cDevOptions::Init() {
	//
	// Class statics
	//
#ifdef WWDEBUG
	ShowGodStatus = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowGodStatus", true);
	ShowSoldierData = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowSoldierData", false);
	ShowVehicleData = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowVehicleData", false);
	ShowDoorData = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowDoorData", false);
	ShowElevatorData = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowElevatorData", false);
	ShowDSAPOData = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowDSAPOData", false);
	ShowPowerupData = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowPowerupData", false);
	ShowBuildingData = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowBuildingData", false);
	ShowSpawnerData = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowSpawnerData", false);
	ShowImportStates = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowImportStates", false);
	ShowImportStatesSV = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowImportStatesSV", false);
	ShowServerRhostData = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowServerRhostData", false);
	ShowClientRhostData = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowClientRhostData", false);
	// ShowPacketGraphs = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowPacketGraphs", false);

	PacketsSentServer = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "PacketsSentServer", false);
	PacketsSentClient = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "PacketsSentClient", false);
	PacketsRecdServer = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "PacketsRecdServer", false);
	PacketsRecdClient = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "PacketsRecdClient", false);
	AvgSizePacketsSentServer = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "AvgSizePacketsSentServer", false);
	AvgSizePacketsSentClient = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "AvgSizePacketsSentClient", false);
	AvgSizePacketsRecdServer = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "AvgSizePacketsRecdServer", false);
	AvgSizePacketsRecdClient = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "AvgSizePacketsRecdClient", false);
	BytesSentServer = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "BytesSentServer", false);
	BytesSentClient = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "BytesSentClient", false);
	BytesRecdServer = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "BytesRecdServer", false);
	BytesRecdClient = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "BytesRecdClient", false);

	WwnetPacketsSentServer = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "WwnetPacketsSentServer", false);
	WwnetPacketsSentClient = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "WwnetPacketsSentClient", false);
	WwnetPacketsRecdServer = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "WwnetPacketsRecdServer", false);
	WwnetPacketsRecdClient = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "WwnetPacketsRecdClient", false);
	WwnetAvgSizePacketsSentServer = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "WwnetAvgSizePacketsSentServer", false);
	WwnetAvgSizePacketsSentClient = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "WwnetAvgSizePacketsSentClient", false);
	WwnetAvgSizePacketsRecdServer = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "WwnetAvgSizePacketsRecdServer", false);
	WwnetAvgSizePacketsRecdClient = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "WwnetAvgSizePacketsRecdClient", false);
	WwnetBytesSentServer = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "WwnetBytesSentServer", false);
	WwnetBytesSentClient = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "WwnetBytesSentClient", false);
	WwnetBytesRecdServer = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "WwnetBytesRecdServer", false);
	WwnetBytesRecdClient = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "WwnetBytesRecdClient", false);

	ShowPriorities = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowPriorities", false);
	ShowBandwidth = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowBandwidth", false);
	ShowLatency = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowLatency", false);
	ShowLastContact = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowLastContact", false);
	ShowListSizes = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowListSizes", false);
	ShowListTimes = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowListTimes",  false);
	ShowListPacketSizes = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowListPacketSizes", false);
	// ShowBandwidthBudgetOut = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowBandwidthBudgetOut", false);
	ShowWatchList = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowWatchList", false);
	ShowWolLocation = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowWolLocation", false);
	ShowDiagnostics = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowDiagnostics", false);
	ShowMenuStack = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowMenuStack", false);
	ShowIpAddresses = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowIpAddresses", false);
	ShowClientFps = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowClientFps", false);
	ShowId = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowId", false);
	ShowPing = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowPing", false);
	ShowObjectTally = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowObjectTally", false);
	ShowInactivePlayers = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowInactivePlayers", false);
	ShowGameSpyAuthState = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowGameSpyAuthState", false);

	DesiredFrameSleepMs = cRegistryInt(APPLICATION_SUB_KEY_NAME_NETDEBUG, "DesiredFrameSleepMs", 0);
	SimulatedPacketLossPc = cRegistryInt(APPLICATION_SUB_KEY_NAME_NETDEBUG, "SimulatedPacketLossPc", 0);
	SimulatedPacketDuplicationPc = cRegistryInt(APPLICATION_SUB_KEY_NAME_NETDEBUG, "SimulatedPacketDuplicationPc", 0);
	SimulatedLatencyRangeMsLower = cRegistryInt(APPLICATION_SUB_KEY_NAME_NETDEBUG, "SimulatedLatencyRangeMsLower", 0);
	SimulatedLatencyRangeMsUpper = cRegistryInt(APPLICATION_SUB_KEY_NAME_NETDEBUG, "SimulatedLatencyRangeMsUpper", 0);
	SpamCount = cRegistryInt(APPLICATION_SUB_KEY_NAME_NETDEBUG, "SpamCount", 0);

	SoundEffectOnAssert = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "SoundEffectOnAssert", false);
	DisplayLogfileOnAssert = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "DisplayLogfileOnAssert", false);
	BreakToDebuggerOnAssert = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "BreakToDebuggerOnAssert", true);
	ShutdownInputOnAssert = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "ShutdownInputOnAssert", true);
	PreloadAssets = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "PreloadAssets", true);
	FilterLevelFiles = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "FilterLevelFiles", true);
	IBelieveInGod = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "IBelieveInGod", false);
	LogDataSafe = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "LogDataSafe", true);
	EnableExceptionHandler = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "ExceptionHandler", true);
	ShowThumbnailPreInitDialog = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "ShowThumbnailPreInitDialog", true);
	CrtDbgEnabled = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "CrtDbgEnabled", true);
	PacketOptimizationsEnabled = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "PacketOptimizationsEnabled", true);
	ShowMoney = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "ShowMoney", false);
	ExtraNetDebug = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "NetDebugLog", false);
	ExtraModemBandwidthThrottling = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "ExtraModemBWThrottling", true);

	GoToMainMenu = cBoolean(false);

#endif // WWDEBUG

	QuickFullExit = cBoolean(false);

	ExitThreadOnAssert = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "ExitThreadOnAssert", true);
	CompareExeVersionOnNetwork = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "CompareExeVersionOnNetwork", true);

	UseNewTCADO = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "NewTCADO", true);
	ShowFps = cRegistryBool(APPLICATION_SUB_KEY_NAME_NETDEBUG, "ShowFps", false);

	// DoThumbnailPreInit = cRegistryBool(APPLICATION_SUB_KEY_NAME_DEBUG, "DoThumbnailPreInit", true);
}
