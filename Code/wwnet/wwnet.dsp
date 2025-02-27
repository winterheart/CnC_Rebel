# Microsoft Developer Studio Project File - Name="wwnet" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=wwnet - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wwnet.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wwnet.mak" CFG="wwnet - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wwnet - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "wwnet - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "wwnet - Win32 Profile" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Commando/Code/wwnet", KBDBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wwnet - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W4 /WX /GX- /Zi /O2 /Ob2 /I "..\\" /I "..\wwbitpack" /I "..\wwdebug" /I "..\wwutil" /I "..\wwlib" /I "..\wwmath" /I "..\wwsaveload" /I "..\wolapi" /I "..\wwonline" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "WIN32_LEAN_AND_MEAN" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Libs\Release\wwnet.lib"

!ELSEIF  "$(CFG)" == "wwnet - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "wwnet___"
# PROP BASE Intermediate_Dir "wwnet___"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W4 /WX /Gm /Gi /GR- /GX- /ZI /Od /I "..\\" /I "..\wwbitpack" /I "..\wwdebug" /I "..\wwutil" /I "..\wwlib" /I "..\wwmath" /I "..\wwsaveload" /I "..\wolapi" /I "..\wwonline" /D "STRICT" /D "_DEBUG" /D "WWDEBUG" /D "WIN32_LEAN_AND_MEAN" /D "_WINDOWS" /D "WIN32" /FD /c
# SUBTRACT CPP /Fr /YX /Yc /Yu
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Libs\Debug\wwnet.lib"

!ELSEIF  "$(CFG)" == "wwnet - Win32 Profile"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Profile"
# PROP BASE Intermediate_Dir "Profile"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Profile"
# PROP Intermediate_Dir "Profile"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\wwlzhl" /I "..\wwutil" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W4 /WX /GX- /Zi /O2 /Op /Ob2 /I "..\\" /I "..\wwbitpack" /I "..\wwdebug" /I "..\wwutil" /I "..\wwlib" /I "..\wwmath" /I "..\wwsaveload" /I "..\wolapi" /I "..\wwonline" /D "NDEBUG" /D "WWDEBUG" /D "_WINDOWS" /D "WIN32" /D "WIN32_LEAN_AND_MEAN" /FD /c
# SUBTRACT CPP /Fr /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libs\Release\wwnet.lib"
# ADD LIB32 /nologo /out:"..\Libs\Profile\wwnet.lib"

!ENDIF 

# Begin Target

# Name "wwnet - Win32 Release"
# Name "wwnet - Win32 Debug"
# Name "wwnet - Win32 Profile"
# Begin Source File

SOURCE=.\BWBalance.cpp
# End Source File
# Begin Source File

SOURCE=.\BWBalance.h
# End Source File
# Begin Source File

SOURCE=.\connect.cpp
# End Source File
# Begin Source File

SOURCE=.\connect.h
# End Source File
# Begin Source File

SOURCE=.\fromaddress.h
# End Source File
# Begin Source File

SOURCE=.\msgstat.cpp
# End Source File
# Begin Source File

SOURCE=.\msgstat.h
# End Source File
# Begin Source File

SOURCE=.\msgstatlist.cpp
# End Source File
# Begin Source File

SOURCE=.\msgstatlist.h
# End Source File
# Begin Source File

SOURCE=.\msgstatlistgroup.cpp
# End Source File
# Begin Source File

SOURCE=.\msgstatlistgroup.h
# End Source File
# Begin Source File

SOURCE=.\netstats.cpp
# End Source File
# Begin Source File

SOURCE=.\netstats.h
# End Source File
# Begin Source File

SOURCE=.\netutil.cpp
# End Source File
# Begin Source File

SOURCE=.\netutil.h
# End Source File
# Begin Source File

SOURCE=.\networkobject.cpp
# End Source File
# Begin Source File

SOURCE=.\networkobject.h
# End Source File
# Begin Source File

SOURCE=.\networkobjectfactory.cpp
# End Source File
# Begin Source File

SOURCE=.\networkobjectfactory.h
# End Source File
# Begin Source File

SOURCE=.\networkobjectfactorymgr.cpp
# End Source File
# Begin Source File

SOURCE=.\networkobjectfactorymgr.h
# End Source File
# Begin Source File

SOURCE=.\networkobjectmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\networkobjectmgr.h
# End Source File
# Begin Source File

SOURCE=.\packetmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\packetmgr.h
# End Source File
# Begin Source File

SOURCE=.\packettype.h
# End Source File
# Begin Source File

SOURCE=.\rhost.cpp
# End Source File
# Begin Source File

SOURCE=.\rhost.h
# End Source File
# Begin Source File

SOURCE=.\singlepl.cpp
# End Source File
# Begin Source File

SOURCE=.\singlepl.h
# End Source File
# Begin Source File

SOURCE=.\wwpacket.cpp
# End Source File
# Begin Source File

SOURCE=.\wwpacket.h
# End Source File
# End Target
# End Project
