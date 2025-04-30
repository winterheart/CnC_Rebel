# Microsoft Developer Studio Project File - Name="wwbitpack" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=wwbitpack - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wwbitpack.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wwbitpack.mak" CFG="wwbitpack - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wwbitpack - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "wwbitpack - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "wwbitpack - Win32 Profile" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Commando/Code/wwbitpack", JAQDAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wwbitpack - Win32 Release"

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
# ADD CPP /nologo /MT /W4 /WX /Zi /O2 /Ob2 /I "..\wwlib" /I "..\wwdebug" /I "..\wwutil" /D "NDEBUG" /D WINVER=0x400 /D "_WINDOWS" /D "WIN32_LEAN_AND_MEAN" /D "WIN32" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\libs\Release\wwbitpack.lib"

!ELSEIF  "$(CFG)" == "wwbitpack - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /WX /Gm /Gi /ZI /Od /I "..\wwlib" /I "..\wwdebug" /I "..\wwutil" /D "_DEBUG" /D "WWDEBUG" /D WINVER=0x400 /D "_WINDOWS" /D "WIN32_LEAN_AND_MEAN" /D "WIN32" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\libs\Debug\wwbitpack.lib"

!ELSEIF  "$(CFG)" == "wwbitpack - Win32 Profile"

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
# ADD BASE CPP /nologo /MD /W4 /WX /GX /O2 /I "..\wwlib" /I "..\wwdebug" /I "..\wwutil" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W4 /WX /Zi /O2 /Op /Ob2 /I "..\wwlib" /I "..\wwdebug" /I "..\wwutil" /D "NDEBUG" /D "WWDEBUG" /D WINVER=0x400 /D "_WINDOWS" /D "WIN32_LEAN_AND_MEAN" /D "WIN32" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\libs\Release\wwbitpack.lib"
# ADD LIB32 /nologo /out:"..\libs\Profile\wwbitpack.lib"

!ENDIF 

# Begin Target

# Name "wwbitpack - Win32 Release"
# Name "wwbitpack - Win32 Debug"
# Name "wwbitpack - Win32 Profile"
# Begin Source File

SOURCE=.\BitPacker.cpp
# End Source File
# Begin Source File

SOURCE=.\BitPacker.h
# End Source File
# Begin Source File

SOURCE=.\bitpackids.h
# End Source File
# Begin Source File

SOURCE=.\bitstream.cpp
# End Source File
# Begin Source File

SOURCE=.\bitstream.h
# End Source File
# Begin Source File

SOURCE=.\encoderlist.cpp
# End Source File
# Begin Source File

SOURCE=.\encoderlist.h
# End Source File
# Begin Source File

SOURCE=.\encodertypeentry.cpp
# End Source File
# Begin Source File

SOURCE=.\encodertypeentry.h
# End Source File
# End Target
# End Project
