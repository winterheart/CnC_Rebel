# Microsoft Developer Studio Project File - Name="wwui" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=wwui - Win32 Profile
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wwui.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wwui.mak" CFG="wwui - Win32 Profile"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wwui - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "wwui - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "wwui - Win32 Profile" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Commando/Code/wwui", FKCEAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wwui - Win32 Release"

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
# ADD CPP /nologo /MT /W4 /Zi /O2 /Ob2 /I "..\wwtranslatedb" /I "..\wwsaveload" /I "..\wwaudio" /I "..\third_party\miles6\include" /I "..\wwmath" /I "..\ww3d2" /I "..\wwlib" /I "..\wwdebug" /I "..\DirectX\include" /D "NDEBUG" /D _WIN32_WINNT=0x400 /D "WIN32" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\libs\Release\wwui.lib"

!ELSEIF  "$(CFG)" == "wwui - Win32 Debug"

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
# ADD CPP /nologo /MTd /W4 /Gm /ZI /Od /I "..\wwtranslatedb" /I "..\wwsaveload" /I "..\wwaudio" /I "..\third_party\miles6\include" /I "..\wwmath" /I "..\ww3d2" /I "..\wwlib" /I "..\wwdebug" /I "..\DirectX\include" /D "_DEBUG" /D _WIN32_WINNT=0x400 /D "WWDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\libs\Debug\wwui.lib"

!ELSEIF  "$(CFG)" == "wwui - Win32 Profile"

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
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\wwaudio" /I "..\third_party\miles6\include" /I "..\wwmath" /I "..\ww3d2" /I "..\wwlib" /I "..\wwdebug" /D "_DEBUG" /D "WWDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MT /W4 /Zi /O2 /Ob2 /I "..\wwtranslatedb" /I "..\wwsaveload" /I "..\wwaudio" /I "..\third_party\miles6\include" /I "..\wwmath" /I "..\ww3d2" /I "..\wwlib" /I "..\wwdebug" /I "..\DirectX\include" /D "NDEBUG" /D "WWDEBUG" /D _WIN32_WINNT=0x400 /D "WIN32" /D "_MBCS" /D "_LIB" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\libs\Debug\wwui.lib"
# ADD LIB32 /nologo /out:"..\libs\Profile\wwui.lib"

!ENDIF 

# Begin Target

# Name "wwui - Win32 Release"
# Name "wwui - Win32 Debug"
# Name "wwui - Win32 Profile"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\buttonctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\checkboxctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\childdialog.cpp
# End Source File
# Begin Source File

SOURCE=.\comboboxctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\dialogbase.cpp
# End Source File
# Begin Source File

SOURCE=.\dialogcontrol.cpp
# End Source File
# Begin Source File

SOURCE=.\dialogmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\dialogparser.cpp
# End Source File
# Begin Source File

SOURCE=.\dialogtext.cpp
# End Source File
# Begin Source File

SOURCE=.\dialogtransition.cpp
# End Source File
# Begin Source File

SOURCE=.\dropdownctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\editctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\healthbarctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\imagectrl.cpp
# End Source File
# Begin Source File

SOURCE=.\IMECandidate.cpp
# End Source File
# Begin Source File

SOURCE=.\IMECandidateCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\IMEManager.cpp
# End Source File
# Begin Source File

SOURCE=.\inputctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\listctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\listiconmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\mapctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\menubackdrop.cpp
# End Source File
# Begin Source File

SOURCE=.\menudialog.cpp
# End Source File
# Begin Source File

SOURCE=.\menuentryctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\merchandisectrl.cpp
# End Source File
# Begin Source File

SOURCE=.\mousemgr.cpp
# End Source File
# Begin Source File

SOURCE=.\multilinetextctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\popupdialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\screencursor.cpp
# End Source File
# Begin Source File

SOURCE=.\scrollbarctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\shortcutbarctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\sliderctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\stylemgr.cpp
# End Source File
# Begin Source File

SOURCE=.\tabctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\textmarqueectrl.cpp
# End Source File
# Begin Source File

SOURCE=.\tooltip.cpp
# End Source File
# Begin Source File

SOURCE=.\tooltipmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\treectrl.cpp
# End Source File
# Begin Source File

SOURCE=.\viewerctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\wwuiinput.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\buttonctrl.h
# End Source File
# Begin Source File

SOURCE=.\checkboxctrl.h
# End Source File
# Begin Source File

SOURCE=.\childdialog.h
# End Source File
# Begin Source File

SOURCE=.\comboboxctrl.h
# End Source File
# Begin Source File

SOURCE=.\controladvisesink.h
# End Source File
# Begin Source File

SOURCE=.\dialogbase.h
# End Source File
# Begin Source File

SOURCE=.\dialogcontrol.h
# End Source File
# Begin Source File

SOURCE=.\dialogfactory.h
# End Source File
# Begin Source File

SOURCE=.\dialogmgr.h
# End Source File
# Begin Source File

SOURCE=.\dialogparser.h
# End Source File
# Begin Source File

SOURCE=.\dialogtext.h
# End Source File
# Begin Source File

SOURCE=.\dialogtransition.h
# End Source File
# Begin Source File

SOURCE=.\dropdownctrl.h
# End Source File
# Begin Source File

SOURCE=.\editctrl.h
# End Source File
# Begin Source File

SOURCE=.\healthbarctrl.h
# End Source File
# Begin Source File

SOURCE=.\imagectrl.h
# End Source File
# Begin Source File

SOURCE=.\IMECandidate.h
# End Source File
# Begin Source File

SOURCE=.\IMECandidate.h
# End Source File
# Begin Source File

SOURCE=.\IMECandidateCtrl.h
# End Source File
# Begin Source File

SOURCE=.\IMEManager.h
# End Source File
# Begin Source File

SOURCE=.\IMEManager.h
# End Source File
# Begin Source File

SOURCE=.\inputctrl.h
# End Source File
# Begin Source File

SOURCE=.\listctrl.h
# End Source File
# Begin Source File

SOURCE=.\listiconmgr.h
# End Source File
# Begin Source File

SOURCE=.\mapctrl.h
# End Source File
# Begin Source File

SOURCE=.\menubackdrop.h
# End Source File
# Begin Source File

SOURCE=.\menudialog.h
# End Source File
# Begin Source File

SOURCE=.\menuentryctrl.h
# End Source File
# Begin Source File

SOURCE=.\merchandisectrl.h
# End Source File
# Begin Source File

SOURCE=.\mousemgr.h
# End Source File
# Begin Source File

SOURCE=.\multilinetextctrl.h
# End Source File
# Begin Source File

SOURCE=.\popupdialog.h
# End Source File
# Begin Source File

SOURCE=.\ProgressCtrl.h
# End Source File
# Begin Source File

SOURCE=.\screencursor.h
# End Source File
# Begin Source File

SOURCE=.\scrollbarctrl.h
# End Source File
# Begin Source File

SOURCE=.\shortcutbarctrl.h
# End Source File
# Begin Source File

SOURCE=.\sliderctrl.h
# End Source File
# Begin Source File

SOURCE=.\stylemgr.h
# End Source File
# Begin Source File

SOURCE=.\tabctrl.h
# End Source File
# Begin Source File

SOURCE=.\textmarqueectrl.h
# End Source File
# Begin Source File

SOURCE=.\tooltip.h
# End Source File
# Begin Source File

SOURCE=.\tooltipmgr.h
# End Source File
# Begin Source File

SOURCE=.\treectrl.h
# End Source File
# Begin Source File

SOURCE=.\viewerctrl.h
# End Source File
# Begin Source File

SOURCE=.\wwuiinput.h
# End Source File
# End Group
# End Target
# End Project
