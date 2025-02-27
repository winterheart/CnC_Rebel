# Microsoft Developer Studio Project File - Name="BinkMovie" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=BinkMovie - Win32 Profile
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BinkMovie.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BinkMovie.mak" CFG="BinkMovie - Win32 Profile"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BinkMovie - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "BinkMovie - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "BinkMovie - Win32 Profile" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Commando/Code/BinkMovie", XPFEAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BinkMovie - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX- /Zi /O2 /Ob2 /I "..\wwmath" /I "..\\" /I "..\ww3d2" /I "..\wwdebug" /I "..\wwlib" /I "..\DirectX\Include" /D "NDEBUG" /D WINVER=0x400 /D "_WINDOWS" /D "WIN32" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Libs\Release\BinkMovie.lib"

!ELSEIF  "$(CFG)" == "BinkMovie - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GR- /GX- /ZI /Od /I "..\wwmath" /I "..\\" /I "..\ww3d2" /I "..\wwdebug" /I "..\wwlib" /I "..\DirectX\Include" /D "_DEBUG" /D "WWDEBUG" /D WINVER=0x400 /D "_WINDOWS" /D "WIN32" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Libs\Debug\BinkMovie.lib"

!ELSEIF  "$(CFG)" == "BinkMovie - Win32 Profile"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Profile"
# PROP BASE Intermediate_Dir "Profile"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Profile"
# PROP Intermediate_Dir "Profile"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MT /W4 /GX- /Zi /O2 /Ob2 /I "..\wwmath" /I "..\\" /I "..\ww3d2" /I "..\wwdebug" /I "..\wwlib" /I "..\DirectX\Include" /D "NDEBUG" /D "WWDEBUG" /D WINVER=0x400 /D "_WINDOWS" /D "WIN32" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Debug\BinkMovieD.lib"
# ADD LIB32 /nologo /out:"..\Libs\Profile\BinkMovie.lib"

!ENDIF 

# Begin Target

# Name "BinkMovie - Win32 Release"
# Name "BinkMovie - Win32 Debug"
# Name "BinkMovie - Win32 Profile"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BINKMovie.cpp
# End Source File
# Begin Source File

SOURCE=.\subtitle.cpp
# End Source File
# Begin Source File

SOURCE=.\subtitlemanager.cpp
# End Source File
# Begin Source File

SOURCE=.\subtitleparser.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BINK.H
# End Source File
# Begin Source File

SOURCE=.\BINKMovie.h
# End Source File
# Begin Source File

SOURCE=.\RAD.H
# End Source File
# Begin Source File

SOURCE=.\subtitle.h
# End Source File
# Begin Source File

SOURCE=.\subtitlemanager.h
# End Source File
# Begin Source File

SOURCE=.\subtitleparser.h
# End Source File
# End Group
# End Target
# End Project
