# Microsoft Developer Studio Project File - Name="wwutil" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=wwutil - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wwutil.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wwutil.mak" CFG="wwutil - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wwutil - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "wwutil - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "wwutil - Win32 Profile" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Commando/Code/wwutil", ACDBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wwutil - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W4 /Zi /O2 /Ob2 /I "..\wwlib" /I "..\wwdebug" /I "..\wwmath" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "WIN32" /D "_WINDOWS" /D "WIN32_LEAN_AND_MEAN" /FD /c
# SUBTRACT CPP /WX /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\libs\release\wwutil.lib"

!ELSEIF  "$(CFG)" == "wwutil - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /WX /Gm /Gi /ZI /Od /I "..\wwlib" /I "..\wwdebug" /I "..\wwmath" /D "_DEBUG" /D "WWDEBUG" /D "_MBCS" /D "_LIB" /D "WIN32" /D "_WINDOWS" /D "WIN32_LEAN_AND_MEAN" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Libs\Debug\wwutil.lib"

!ELSEIF  "$(CFG)" == "wwutil - Win32 Profile"

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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W4 /Zi /O2 /Op /Ob2 /I "..\wwlib" /I "..\wwdebug" /I "..\wwmath" /D "NDEBUG" /D "WWDEBUG" /D "_MBCS" /D "_LIB" /D "WIN32" /D "_WINDOWS" /D "WIN32_LEAN_AND_MEAN" /FD /c
# SUBTRACT CPP /WX /Fr /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\libs\profile\wwutil.lib"

!ENDIF 

# Begin Target

# Name "wwutil - Win32 Release"
# Name "wwutil - Win32 Debug"
# Name "wwutil - Win32 Profile"
# Begin Source File

SOURCE=.\mathutil.cpp
# End Source File
# Begin Source File

SOURCE=.\mathutil.h
# End Source File
# Begin Source File

SOURCE=.\miscutil.cpp
# End Source File
# Begin Source File

SOURCE=.\miscutil.h
# End Source File
# Begin Source File

SOURCE=.\stackdump.cpp
# End Source File
# Begin Source File

SOURCE=.\stackdump.h
# End Source File
# End Target
# End Project
