# Microsoft Developer Studio Project File - Name="PhysTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PhysTest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PhysTest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PhysTest.mak" CFG="PhysTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PhysTest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PhysTest - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Commando/Code/Tests/PhysTest", QCOBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PhysTest - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\sr\sr.h" /I "..\..\srsdk1x\include" /I "..\..\wwdebug" /I "..\..\wwmath" /I "..\..\ww3d" /I "..\..\wwphys" /I "..\..\wwlib" /I "..\..\wwsaveload" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 sr.lib wwdebug.lib wwmath.lib ww3d.lib wwlib.lib wwphys.lib wwsaveload.lib vfw32.lib winmm.lib version.lib /nologo /subsystem:windows /machine:I386 /out:"Run/PhysTest.exe" /libpath:"..\..\Libs\release" /libpath:"..\..\srsdk1x\msvc6\lib\release"

!ELSEIF  "$(CFG)" == "PhysTest - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\srsdk1x\include" /I "..\..\wwdebug" /I "..\..\wwmath" /I "..\..\ww3d" /I "..\..\wwphys" /I "..\..\wwlib" /I "..\..\wwsaveload" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "WWDEBUG" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 
# ADD LINK32 srdb.lib wwdebug.lib wwmath.lib ww3d.lib wwlib.lib wwphys.lib wwsaveload.lib vfw32.lib winmm.lib version.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Run/PhysTestD.exe"  /libpath:"..\..\Libs\debug" /libpath:"..\..\srsdk1x\msvc6\lib\debug"

!ENDIF 

# Begin Target

# Name "PhysTest - Win32 Release"
# Name "PhysTest - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DataView.cpp
# End Source File
# Begin Source File

SOURCE=.\Globals.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphicView.cpp
# End Source File
# Begin Source File

SOURCE=.\InertiaDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MotorcycleDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MotorVehicleDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PhysicsConstantsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PhysTest.cpp
# End Source File
# Begin Source File

SOURCE=.\PhysTestDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\PhysTestSaveSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\RbodyPropertiesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RenderDeviceDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\VJoyDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\WheeledVehicleDialog.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DataView.h
# End Source File
# Begin Source File

SOURCE=.\GraphicView.h
# End Source File
# Begin Source File

SOURCE=.\InertiaDialog.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MotorcycleDialog.h
# End Source File
# Begin Source File

SOURCE=.\MotorVehicleDialog.h
# End Source File
# Begin Source File

SOURCE=.\PhysicsConstantsDialog.h
# End Source File
# Begin Source File

SOURCE=.\PhysTest.h
# End Source File
# Begin Source File

SOURCE=.\PhysTestDoc.h
# End Source File
# Begin Source File

SOURCE=.\PhysTestSaveSystem.h
# End Source File
# Begin Source File

SOURCE=.\RbodyPropertiesDialog.h
# End Source File
# Begin Source File

SOURCE=.\RenderDeviceDialog.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\VJoyDialog.h
# End Source File
# Begin Source File

SOURCE=.\WheeledVehicleDialog.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\PhysTest.ico
# End Source File
# Begin Source File

SOURCE=.\PhysTest.rc
# End Source File
# Begin Source File

SOURCE=.\res\PhysTest.rc2
# End Source File
# Begin Source File

SOURCE=.\res\PhysTestDoc.ico
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Axes.w3d
# End Source File
# Begin Source File

SOURCE=.\res\Point.w3d
# End Source File
# End Target
# End Project
