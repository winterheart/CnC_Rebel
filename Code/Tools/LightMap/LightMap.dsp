# Microsoft Developer Studio Project File - Name="LightMap" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=LightMap - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LightMap.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LightMap.mak" CFG="LightMap - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LightMap - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "LightMap - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "LightMap - Win32 Profile" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Commando/Code/Tools/LightMap", CXCCAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LightMap - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Ot /Op /Ob2 /I "..\..\Lightscape\Inc" /I "..\..\srsdk1x\include" /I "..\..\wwdebug" /I "..\..\Wwlib" /I "..\..\Ww3d2" /I "..\..\wwmath" /I "..\..\wwsaveload" /I "..\..\wwphys" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 lvsio.lib wwlib.lib wwmath.lib ww3d2.lib wwdebug.lib wwsaveload.lib vfw32.lib sr.lib version.lib winmm.lib d3dx8.lib d3d8.lib /nologo /subsystem:windows /map /machine:I386 /out:"Run\LightMap.exe" /libpath:"..\..\Lightscape\Lib" /libpath:"..\..\Libs\Release" /libpath:"..\..\srsdk1x\msvc6\lib\release"
# SUBTRACT LINK32 /profile

!ELSEIF  "$(CFG)" == "LightMap - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\Lightscape\Inc" /I "..\..\srsdk1x\include" /I "..\..\wwdebug" /I "..\..\Wwlib" /I "..\..\Ww3d2" /I "..\..\wwmath" /I "..\..\wwsaveload" /I "..\..\wwphys" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 
# ADD LINK32 lvsiod.lib wwlib.lib wwmath.lib ww3d2.lib wwdebug.lib wwsaveload.lib vfw32.lib srdb.lib version.lib winmm.lib d3dx8.lib d3d8.lib /nologo /subsystem:windows /profile /map /debug /machine:I386 /out:"Run\LightMapD.exe" /libpath:"..\..\Lightscape\Lib" /libpath:"..\..\Libs\Debug" /libpath:"..\..\srsdk1x\msvc6\lib\debug"

!ELSEIF  "$(CFG)" == "LightMap - Win32 Profile"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Profile"
# PROP BASE Intermediate_Dir "Profile"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Profile"
# PROP Intermediate_Dir "Profile"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Ot /Op /Ob2 /I "..\..\Lightscape\Inc" /I "..\..\srsdk1x\include" /I "..\..\wwdebug" /I "..\..\Wwlib" /I "..\..\Ww3d2" /I "..\..\wwmath" /I "..\..\wwsaveload" /I "..\..\wwphys" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O2 /Op /Ob2 /I "..\..\Lightscape\Inc" /I "..\..\srsdk1x\include" /I "..\..\wwdebug" /I "..\..\Wwlib" /I "..\..\Ww3d2" /I "..\..\wwmath" /I "..\..\wwsaveload" /I "..\..\wwphys" /D "WIN32" /D "WWDEBUG" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 lvsio.lib wwlib.lib wwmath.lib ww3d2.lib wwdebug.lib wwsaveload.lib vfw32.lib sr.lib version.lib winmm.lib d3dx8.lib d3d8.lib /nologo /subsystem:windows /map /machine:I386 /out:"Run\LightMap.exe" /libpath:"..\..\Lightscape\Lib" /libpath:"..\..\Libs\Release" /libpath:"..\..\srsdk1x\msvc6\lib\release"
# SUBTRACT BASE LINK32 /profile
# ADD LINK32 lvsio.lib wwlib.lib wwmath.lib ww3d2.lib wwdebug.lib wwsaveload.lib vfw32.lib sr.lib version.lib winmm.lib d3dx8.lib d3d8.lib /nologo /subsystem:windows /incremental:yes /debug /machine:I386 /out:"Run\LightMap.exe" /libpath:"..\..\Lightscape\Lib" /libpath:"..\..\Libs\Profile" /libpath:"..\..\srsdk1x\msvc6\lib\release"
# SUBTRACT LINK32 /profile /map

!ENDIF 

# Begin Target

# Name "LightMap - Win32 Release"
# Name "LightMap - Win32 Debug"
# Name "LightMap - Win32 Profile"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\InsertSolveDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\LightMap.cpp
# End Source File
# Begin Source File

SOURCE=.\LightMap.rc
# End Source File
# Begin Source File

SOURCE=.\LightMapDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\LightMapPacker.cpp
# End Source File
# Begin Source File

SOURCE=.\LightMapView.cpp
# End Source File
# Begin Source File

SOURCE=.\Lightscape.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PackingDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PerlinNoise.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectionDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\StringBuilder.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Chunk.h
# End Source File
# Begin Source File

SOURCE=.\InsertSolveDialog.h
# End Source File
# Begin Source File

SOURCE=.\LightMap.h
# End Source File
# Begin Source File

SOURCE=.\LightMapDoc.h
# End Source File
# Begin Source File

SOURCE=.\LightMapPacker.h
# End Source File
# Begin Source File

SOURCE=.\LightMapView.h
# End Source File
# Begin Source File

SOURCE=.\Lightscape.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\OptionsDialog.h
# End Source File
# Begin Source File

SOURCE=.\PackingDialog.h
# End Source File
# Begin Source File

SOURCE=.\PerlinNoise.h
# End Source File
# Begin Source File

SOURCE=.\ProceduralTexture.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SelectionDialog.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StringBuilder.h
# End Source File
# Begin Source File

SOURCE=.\TextureNameNode.h
# End Source File
# Begin Source File

SOURCE=.\Triangle.h
# End Source File
# End Group
# Begin Group "Resources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Res\LightMap.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Toolbar.bmp
# End Source File
# End Group
# End Target
# End Project
