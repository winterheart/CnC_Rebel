# Microsoft Developer Studio Project File - Name="movietest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=movietest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "movietest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "movietest.mak" CFG="movietest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "movietest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "movietest - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""$/Commando/Code/Tests/movietest", TCOAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "movietest - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\sr130\sr.h" /I "..\..\Library" /I "..\..\WWMath" /I "..\..\ww3d" /I "..\..\wwdebug" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib ddraw.lib winmm.lib library.lib wwmath.lib ww3d.lib sr.lib /nologo /subsystem:windows /machine:I386 /out:"Run/movietest.exe" /libpath:"..\..\libs\Release" /libpath:"..\..\sr130\release"

!ELSEIF  "$(CFG)" == "movietest - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\..\sr130\sr.h" /I "..\..\Library" /I "..\..\WWMath" /I "..\..\ww3d" /I "..\..\wwdebug" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib ddraw.lib winmm.lib library.lib wwmath.lib ww3d.lib srdb.lib /nologo /subsystem:windows /profile /map /debug /machine:I386 /out:"Run/movietest_d.exe" /libpath:"..\..\libs\Debug" /libpath:"..\..\sr130\debug"
# Begin Special Build Tool
SOURCE=$(InputPath)
PostBuild_Cmds=copy    debug\movietest.map    run\ 
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "movietest - Win32 Release"
# Name "movietest - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp,c"
# Begin Source File

SOURCE=.\_GLOBALS.CPP
# End Source File
# Begin Source File

SOURCE=.\_viewpt.cpp
# End Source File
# Begin Source File

SOURCE=.\_world.cpp
# End Source File
# Begin Source File

SOURCE=.\init.cpp
# End Source File
# Begin Source File

SOURCE=.\mainloop.cpp
# End Source File
# Begin Source File

SOURCE=.\shutdown.cpp
# End Source File
# Begin Source File

SOURCE=.\WINMAIN.CPP
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\_GLOBALS.H
# End Source File
# Begin Source File

SOURCE=.\_viewpt.h
# End Source File
# Begin Source File

SOURCE=.\_world.h
# End Source File
# Begin Source File

SOURCE=.\init.h
# End Source File
# Begin Source File

SOURCE=.\mainloop.h
# End Source File
# Begin Source File

SOURCE=.\shutdown.h
# End Source File
# Begin Source File

SOURCE=.\WINMAIN.H
# End Source File
# End Group
# End Target
# End Project
