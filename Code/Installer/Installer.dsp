# Microsoft Developer Studio Project File - Name="Installer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Installer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Installer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Installer.mak" CFG="Installer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Installer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Installer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Commando/Code/Installer", KQFEAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Installer - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\WwSaveLoad" /I "..\Wwui" /I "..\Ww3d2" /I "..\Wwmath" /I "..\Wwlib" /I "..\BinkMovie" /I "..\Wwdebug" /I "..\WWAudio" /I "..\Miles6\Include" /I "Cab\Include" /I "..\Wwtranslatedb" /I "..\DirectX\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D _WIN32_WINNT=0x400 /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib vfw32.lib winmm.lib d3dx8.lib d3d8.lib wwui.lib ww3d2.lib wwmath.lib wwlib.lib wwsaveload.lib wwdebug.lib binkmovie.lib binkw32.lib wwaudio.lib ..\miles6\lib\win\mss32.lib cab\lib\fdi.lib version.lib wwtranslatedb.lib /nologo /subsystem:windows /machine:I386 /out:"Run\Setup.exe" /libpath:"..\Libs\Release" /libpath:"..\BinkMovie" /libpath:"..\DirectX\Lib"
# SUBTRACT LINK32 /debug
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=Copy Run\Setup.exe Run\Chinese\Setup.exe	Copy Run\Setup.exe Run\English\Setup.exe	Copy Run\Setup.exe Run\French\Setup.exe	Copy Run\Setup.exe Run\German\Setup.exe	Copy Run\Setup.exe Run\Korean\Setup.exe	Copy Run\Setup.exe Run\Japanese\Setup.exe	Copy Run\Setup.exe Run\Beta\Setup.exe
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Installer - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\WwSaveLoad" /I "..\Wwui" /I "..\Ww3d2" /I "..\Wwmath" /I "..\Wwlib" /I "..\BinkMovie" /I "..\Wwdebug" /I "..\WWAudio" /I "..\Miles6\Include" /I "Cab\Include" /I "..\Wwtranslatedb" /I "..\DirectX\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "WWDEBUG" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib vfw32.lib winmm.lib d3dx8.lib d3d8.lib wwui.lib ww3d2.lib wwmath.lib wwlib.lib wwsaveload.lib wwdebug.lib binkmovie.lib binkw32.lib wwaudio.lib ..\miles6\lib\win\mss32.lib cab\lib\fdi.lib version.lib wwtranslatedb.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"Run\SetupD.exe"  /libpath:"..\Libs\Debug" /libpath:"..\BinkMovie" /libpath:"..\DirectX\Lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=Copy Run\SetupD.exe Run\Chinese\SetupD.exe	Copy Run\SetupD.exe Run\English\SetupD.exe	Copy Run\SetupD.exe Run\French\SetupD.exe	Copy Run\SetupD.exe Run\German\SetupD.exe	Copy Run\SetupD.exe Run\Korean\SetupD.exe	Copy Run\SetupD.exe Run\Japanese\SetupD.exe	Copy Run\SetupD.exe Run\Beta\SetupD.exe
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Installer - Win32 Release"
# Name "Installer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CardSelectionDialog.cpp

!IF  "$(CFG)" == "Installer - Win32 Release"

!ELSEIF  "$(CFG)" == "Installer - Win32 Debug"

# ADD CPP /MTd

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CopyDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CopyThread.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectoryBrowser.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectoryDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrorHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\FinalDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Installer.cpp
# End Source File
# Begin Source File

SOURCE=.\Installer.rc
# End Source File
# Begin Source File

SOURCE=.\InstallMenuDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\LicenseDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageBox.cpp
# End Source File
# Begin Source File

SOURCE=.\RAMFileFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistryManager.cpp
# End Source File
# Begin Source File

SOURCE=.\ReviewDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SafeTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\SerialDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\TransitionDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Translator.cpp
# End Source File
# Begin Source File

SOURCE=.\Utilities.cpp
# End Source File
# Begin Source File

SOURCE=.\WelcomeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\WhatToInstallDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\WinMain.cpp
# End Source File
# Begin Source File

SOURCE=.\WOL1Dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\WOL2Dialog.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CardSelectionDialog.h
# End Source File
# Begin Source File

SOURCE=.\CodeControl.h
# End Source File
# Begin Source File

SOURCE=.\CopyDialog.h
# End Source File
# Begin Source File

SOURCE=.\CopyThread.h
# End Source File
# Begin Source File

SOURCE=.\DirectoryBrowser.h
# End Source File
# Begin Source File

SOURCE=.\DirectoryDialog.h
# End Source File
# Begin Source File

SOURCE=.\ErrorHandler.h
# End Source File
# Begin Source File

SOURCE=.\FinalDialog.h
# End Source File
# Begin Source File

SOURCE=.\FolderDialog.h
# End Source File
# Begin Source File

SOURCE=.\Installer.h
# End Source File
# Begin Source File

SOURCE=.\InstallMenuDialog.h
# End Source File
# Begin Source File

SOURCE=.\LicenseDialog.h
# End Source File
# Begin Source File

SOURCE=.\MessageBox.h
# End Source File
# Begin Source File

SOURCE=.\RAMFileFactory.h
# End Source File
# Begin Source File

SOURCE=.\RegistryManager.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ReviewDialog.h
# End Source File
# Begin Source File

SOURCE=.\SafeTimer.h
# End Source File
# Begin Source File

SOURCE=.\SerialDialog.h
# End Source File
# Begin Source File

SOURCE=.\TransitionDialog.h
# End Source File
# Begin Source File

SOURCE=.\Translator.h
# End Source File
# Begin Source File

SOURCE=.\Utilities.h
# End Source File
# Begin Source File

SOURCE=.\WelcomeDialog.h
# End Source File
# Begin Source File

SOURCE=.\WhatToInstallDialog.h
# End Source File
# Begin Source File

SOURCE=.\WOL1Dialog.h
# End Source File
# Begin Source File

SOURCE=.\WOL2Dialog.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Renegade.ico
# End Source File
# End Group
# End Target
# End Project
