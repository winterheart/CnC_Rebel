# Microsoft Developer Studio Project File - Name="Scripts" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Scripts - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Scripts.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Scripts.mak" CFG="Scripts - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Scripts - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Scripts - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Scripts - Win32 Profile" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Commando/Code/Scripts", ISTAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Scripts - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W4 /WX /Zi /O2 /Ob2 /D "NDEBUG" /D WINVER=0x400 /D "_WINDOWS" /D "WIN32" /D "BUILDING_DLL" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:"..\..\Run\Scripts.pdb" /map:"..\..\Run\Scripts.map" /debug /machine:I386 /out:"..\..\Run\Scripts.dll"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Release\Scripts.lib ..\libs\Release\Scripts.lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Scripts - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W4 /WX /Gm /Gi /ZI /Od /D "_DEBUG" /D "WWDEBUG" /D WINVER=0x400 /D "_WINDOWS" /D "WIN32" /D "BUILDING_DLL" /Fr /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:"..\..\Run\ScriptsD.pdb" /map:"..\..\Run\ScriptsD.map" /debug /machine:I386 /out:"..\..\Run\ScriptsD.dll" /implib:"Debug/Scripts.lib" /libpath:"..\..\run\Debug"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Debug\Scripts.lib ..\libs\Debug\Scripts.lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Scripts - Win32 Profile"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Scripts_"
# PROP BASE Intermediate_Dir "Scripts_"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Profile"
# PROP Intermediate_Dir "Profile"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W4 /WX /Zi /O2 /Ob2 /D "NDEBUG" /D "WIN32_LEAN_AND_MEAN" /D "_MBCS" /D "_LIB" /D "WWDEBUG" /D WINVER=0x400 /D "_WINDOWS" /D "WIN32" /D "BUILDING_DLL" /FD /c
# SUBTRACT CPP /Fr /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\..\run\Debug/Scripts.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:"..\..\Run\ScriptsP.pdb" /map:"..\..\Run\ScriptsP.map" /debug /machine:I386 /out:"..\..\Run\ScriptsP.dll" /implib:"Profile/Scripts.lib"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy Profile\Scripts.lib ..\libs\Profile\Scripts.lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Scripts - Win32 Release"
# Name "Scripts - Win32 Debug"
# Name "Scripts - Win32 Profile"
# Begin Group "Support"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\always.h
# End Source File
# Begin Source File

SOURCE=.\bool.h
# End Source File
# Begin Source File

SOURCE=.\combatsound.h
# End Source File
# Begin Source File

SOURCE=.\CustomEvents.h
# End Source File
# Begin Source File

SOURCE=.\DLLmain.cpp
# End Source File
# Begin Source File

SOURCE=.\DPrint.cpp
# End Source File
# Begin Source File

SOURCE=.\DPrint.h
# End Source File
# Begin Source File

SOURCE=.\DrMobius.cpp
# End Source File
# Begin Source File

SOURCE=.\gameobjobserver.h
# End Source File
# Begin Source File

SOURCE=.\scriptevents.h
# End Source File
# Begin Source File

SOURCE=.\ScriptFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptFactory.h
# End Source File
# Begin Source File

SOURCE=.\ScriptNode.h
# End Source File
# Begin Source File

SOURCE=.\ScriptRegistrant.h
# End Source File
# Begin Source File

SOURCE=.\ScriptRegistrar.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptRegistrar.h
# End Source File
# Begin Source File

SOURCE=.\slist.h
# End Source File
# Begin Source File

SOURCE=.\slnode.h
# End Source File
# Begin Source File

SOURCE=.\strtrim.cpp
# End Source File
# Begin Source File

SOURCE=.\strtrim.h
# End Source File
# Begin Source File

SOURCE=.\vector.h
# End Source File
# Begin Source File

SOURCE=.\vector3.h
# End Source File
# Begin Source File

SOURCE=.\visualc.h
# End Source File
# Begin Source File

SOURCE=.\wwmath.h
# End Source File
# End Group
# Begin Group "Design_Test"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Test_BMG.cpp
# End Source File
# Begin Source File

SOURCE=.\Test_Cinematic.cpp
# End Source File
# Begin Source File

SOURCE=.\Test_DAK.cpp
# End Source File
# Begin Source File

SOURCE=.\Test_DAY.cpp
# End Source File
# Begin Source File

SOURCE=.\Test_DLS.cpp
# End Source File
# Begin Source File

SOURCE=.\Test_DME.cpp
# End Source File
# Begin Source File

SOURCE=.\Test_GTH.cpp
# End Source File
# Begin Source File

SOURCE=.\Test_JDG_EVA.cpp
# End Source File
# Begin Source File

SOURCE=.\Test_PDS.cpp
# End Source File
# Begin Source File

SOURCE=.\Test_RAD.cpp
# End Source File
# Begin Source File

SOURCE=.\Test_RMV.cpp
# End Source File
# Begin Source File

SOURCE=.\Test_RMV_Toolkit.cpp
# End Source File
# End Group
# Begin Group "Toolkit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Toolkit.cpp
# End Source File
# Begin Source File

SOURCE=.\Toolkit.h
# End Source File
# Begin Source File

SOURCE=.\Toolkit_Actions.cpp
# End Source File
# Begin Source File

SOURCE=.\Toolkit_Animations.cpp
# End Source File
# Begin Source File

SOURCE=.\Toolkit_Broadcaster.cpp
# End Source File
# Begin Source File

SOURCE=.\Toolkit_Explosions.cpp
# End Source File
# Begin Source File

SOURCE=.\Toolkit_Objectives.cpp
# End Source File
# Begin Source File

SOURCE=.\Toolkit_Objects.cpp
# End Source File
# Begin Source File

SOURCE=.\Toolkit_Powerup.cpp
# End Source File
# Begin Source File

SOURCE=.\Toolkit_Siege.cpp
# End Source File
# Begin Source File

SOURCE=.\Toolkit_Sounds.cpp
# End Source File
# Begin Source File

SOURCE=.\Toolkit_Spawners.cpp
# End Source File
# Begin Source File

SOURCE=.\Toolkit_Triggers.cpp
# End Source File
# End Group
# Begin Group "Missions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Mission00.cpp
# End Source File
# Begin Source File

SOURCE=.\Mission00.h
# End Source File
# Begin Source File

SOURCE=.\Mission01.cpp
# End Source File
# Begin Source File

SOURCE=.\Mission02.cpp
# End Source File
# Begin Source File

SOURCE=.\Mission03.cpp
# End Source File
# Begin Source File

SOURCE=.\Mission04.cpp
# End Source File
# Begin Source File

SOURCE=.\Mission05.cpp
# End Source File
# Begin Source File

SOURCE=.\Mission06.cpp
# End Source File
# Begin Source File

SOURCE=.\Mission07.cpp
# End Source File
# Begin Source File

SOURCE=.\mission08.cpp
# End Source File
# Begin Source File

SOURCE=.\Mission09.cpp
# End Source File
# Begin Source File

SOURCE=.\Mission1.h
# End Source File
# Begin Source File

SOURCE=.\Mission10.cpp
# End Source File
# Begin Source File

SOURCE=.\Mission10.h
# End Source File
# Begin Source File

SOURCE=.\Mission11.cpp
# End Source File
# Begin Source File

SOURCE=.\Mission11.h
# End Source File
# Begin Source File

SOURCE=.\Mission2.h
# End Source File
# Begin Source File

SOURCE=.\Mission3.h
# End Source File
# Begin Source File

SOURCE=.\Mission4.h
# End Source File
# Begin Source File

SOURCE=.\Mission5.h
# End Source File
# Begin Source File

SOURCE=.\Mission6.h
# End Source File
# Begin Source File

SOURCE=.\Mission7.h
# End Source File
# Begin Source File

SOURCE=.\Mission8.h
# End Source File
# Begin Source File

SOURCE=.\Mission9.h
# End Source File
# Begin Source File

SOURCE=.\MissionDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\MissionX0.cpp
# End Source File
# Begin Source File

SOURCE=.\MissionX0.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\actionparams.h
# End Source File
# Begin Source File

SOURCE=.\scriptcommands.h
# End Source File
# Begin Source File

SOURCE=.\scripts.cpp
# End Source File
# Begin Source File

SOURCE=.\scripts.h
# End Source File
# Begin Source File

SOURCE=.\string_ids.h
# End Source File
# End Target
# End Project
