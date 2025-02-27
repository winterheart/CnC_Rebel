# Microsoft Developer Studio Project File - Name="wwphys" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=wwphys - Win32 DebugE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wwphys.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wwphys.mak" CFG="wwphys - Win32 DebugE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wwphys - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "wwphys - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "wwphys - Win32 Profile" (based on "Win32 (x86) Static Library")
!MESSAGE "wwphys - Win32 ProfileE" (based on "Win32 (x86) Static Library")
!MESSAGE "wwphys - Win32 DebugE" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Commando/Code/wwphys", ZLNAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wwphys - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /Zi /O2 /Ob2 /I "..\wwsaveload" /I "..\wwlib" /I "..\wwmath" /I "..\ww3d2" /I "..\wwdebug" /I "..\wwlzhl" /I "..\wwbitpack" /I "..\wwutil" /I "..\umbra\interface" /I "..\DirectX\include" /D "NDEBUG" /D WINVER=0x400 /D "_WINDOWS" /D "WIN32" /FD /c
# SUBTRACT CPP /WX /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Libs\release\wwphys.lib"

!ELSEIF  "$(CFG)" == "wwphys - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W4 /Gm /Gi /ZI /Od /I "..\wwsaveload" /I "..\wwlib" /I "..\wwmath" /I "..\ww3d2" /I "..\wwdebug" /I "..\wwlzhl" /I "..\wwbitpack" /I "..\wwutil" /I "..\umbra\interface" /I "..\DirectX\include" /D "_DEBUG" /D "WWDEBUG" /D WINVER=0x400 /D "_WINDOWS" /D "WIN32" /FR /YX /FD /c
# SUBTRACT CPP /WX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Libs\debug\wwphys.lib"

!ELSEIF  "$(CFG)" == "wwphys - Win32 Profile"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "wwphys__"
# PROP BASE Intermediate_Dir "wwphys__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Profile"
# PROP Intermediate_Dir "Profile"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\Library" /I "..\wwmath" /I "..\ww3d" /I "..\sr130\sr.h" /I "..\wwdebug" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Zi /O2 /Op /Ob2 /I "..\wwsaveload" /I "..\wwlib" /I "..\wwmath" /I "..\ww3d2" /I "..\wwdebug" /I "..\wwlzhl" /I "..\wwbitpack" /I "..\wwutil" /I "..\umbra\interface" /I "..\DirectX\include" /D "NDEBUG" /D "WWDEBUG" /D WINVER=0x400 /D "_WINDOWS" /D "WIN32" /FD /c
# SUBTRACT CPP /WX /YX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libs\release\wwphys.lib"
# ADD LIB32 /nologo /out:"..\Libs\profile\wwphys.lib"

!ELSEIF  "$(CFG)" == "wwphys - Win32 ProfileE"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ProfileE"
# PROP BASE Intermediate_Dir "ProfileE"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ProfileE"
# PROP Intermediate_Dir "ProfileE"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /Gi /GX /Zi /O2 /I "..\wwsaveload" /I "..\wwlib" /I "..\wwmath" /I "..\ww3d" /I "..\srsdk1x\include" /I "..\wwdebug" /I "..\wwlzhl" /I "..\wwbitpack" /I "..\wwutil" /D "NDEBUG" /D "WWDEBUG" /D WINVER=0x400 /D "_WINDOWS" /D "WIN32" /YX /FD /c
# SUBTRACT BASE CPP /WX
# ADD CPP /nologo /MT /W3 /Gm /Gi /Zi /O2 /I "..\wwsaveload" /I "..\wwlib" /I "..\wwmath" /I "..\ww3d2" /I "..\wwdebug" /I "..\wwlzhl" /I "..\wwbitpack" /I "..\wwutil" /I "..\umbra\interface" /I "..\DirectX\include" /D "NDEBUG" /D "WWDEBUG" /D WINVER=0x400 /D "_WINDOWS" /D "WIN32" /D "PARAM_EDITING_ON" /YX /FD /c
# SUBTRACT CPP /WX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libs\profile\wwphys.lib"
# ADD LIB32 /nologo /out:"..\Libs\profile\wwphyse.lib"

!ELSEIF  "$(CFG)" == "wwphys - Win32 DebugE"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugE"
# PROP BASE Intermediate_Dir "DebugE"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugE"
# PROP Intermediate_Dir "DebugE"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /Gi /GX /ZI /Od /I "..\wwsaveload" /I "..\wwlib" /I "..\wwmath" /I "..\ww3d" /I "..\srsdk1x\include" /I "..\wwdebug" /I "..\wwlzhl" /I "..\wwbitpack" /I "..\wwutil" /D "_DEBUG" /D "WWDEBUG" /D WINVER=0x400 /D "_WINDOWS" /D "WIN32" /FR /YX /FD /c
# SUBTRACT BASE CPP /WX
# ADD CPP /nologo /MTd /W4 /Gm /Gi /ZI /Od /I "..\wwsaveload" /I "..\wwlib" /I "..\wwmath" /I "..\ww3d2" /I "..\wwdebug" /I "..\wwlzhl" /I "..\wwbitpack" /I "..\wwutil" /I "..\umbra\interface" /I "..\DirectX\include" /D "_DEBUG" /D "WWDEBUG" /D WINVER=0x400 /D "_WINDOWS" /D "WIN32" /D "PARAM_EDITING_ON" /FR /YX /FD /c
# SUBTRACT CPP /WX
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libs\debug\wwphys.lib"
# ADD LIB32 /nologo /out:"..\Libs\debug\wwphyse.lib"

!ENDIF 

# Begin Target

# Name "wwphys - Win32 Release"
# Name "wwphys - Win32 Debug"
# Name "wwphys - Win32 Profile"
# Name "wwphys - Win32 ProfileE"
# Name "wwphys - Win32 DebugE"
# Begin Group "Source"

# PROP Default_Filter "c;cpp;asm"
# Begin Source File

SOURCE=.\accessiblephys.cpp
# End Source File
# Begin Source File

SOURCE=.\animcollisionmanager.cpp
# End Source File
# Begin Source File

SOURCE=.\bpt.cpp

!IF  "$(CFG)" == "wwphys - Win32 Release"

!ELSEIF  "$(CFG)" == "wwphys - Win32 Debug"

!ELSEIF  "$(CFG)" == "wwphys - Win32 Profile"

# ADD CPP /Ox /Ot /Og /Op /Ob2

!ELSEIF  "$(CFG)" == "wwphys - Win32 ProfileE"

# ADD BASE CPP /Ox /Ot /Og /Op /Ob2
# ADD CPP /Ox /Ot /Og /Op /Ob2

!ELSEIF  "$(CFG)" == "wwphys - Win32 DebugE"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\camerashakesystem.cpp
# End Source File
# Begin Source File

SOURCE=.\decophys.cpp
# End Source File
# Begin Source File

SOURCE=.\dynamicaabtreecull.cpp
# End Source File
# Begin Source File

SOURCE=.\dynamicanimphys.cpp
# End Source File
# Begin Source File

SOURCE=.\dynamicphys.cpp
# End Source File
# Begin Source File

SOURCE=.\dynamicshadowmanager.cpp
# End Source File
# Begin Source File

SOURCE=.\dyntexproject.cpp
# End Source File
# Begin Source File

SOURCE=.\floodfillbox.cpp
# End Source File
# Begin Source File

SOURCE=.\floodfillgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\grideffect.cpp
# End Source File
# Begin Source File

SOURCE=.\heightdb.cpp
# End Source File
# Begin Source File

SOURCE=.\humanphys.cpp
# End Source File
# Begin Source File

SOURCE=.\lightcull.cpp
# End Source File
# Begin Source File

SOURCE=.\lightphys.cpp
# End Source File
# Begin Source File

SOURCE=.\lightsolve.cpp
# End Source File
# Begin Source File

SOURCE=.\lightsolvecontext.cpp
# End Source File
# Begin Source File

SOURCE=.\materialeffect.cpp
# End Source File
# Begin Source File

SOURCE=.\motorcycle.cpp
# End Source File
# Begin Source File

SOURCE=.\motorvehicle.cpp
# End Source File
# Begin Source File

SOURCE=.\movephys.cpp
# End Source File
# Begin Source File

SOURCE=.\octbox.cpp
# End Source File
# Begin Source File

SOURCE=.\Path.cpp
# End Source File
# Begin Source File

SOURCE=.\PathDebugPlotter.cpp
# End Source File
# Begin Source File

SOURCE=.\Pathfind.cpp
# End Source File
# Begin Source File

SOURCE=.\pathfindbox.cpp
# End Source File
# Begin Source File

SOURCE=.\PathfindPortal.cpp
# End Source File
# Begin Source File

SOURCE=.\PathfindSector.cpp
# End Source File
# Begin Source File

SOURCE=.\pathmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\pathnode.cpp
# End Source File
# Begin Source File

SOURCE=.\PathObject.cpp
# End Source File
# Begin Source File

SOURCE=.\pathsolve.cpp
# End Source File
# Begin Source File

SOURCE=.\phys.cpp
# End Source File
# Begin Source File

SOURCE=.\phys3.cpp
# End Source File
# Begin Source File

SOURCE=.\physaabtreecull.cpp
# End Source File
# Begin Source File

SOURCE=.\physcon.cpp
# End Source File
# Begin Source File

SOURCE=.\physcontrol.cpp
# End Source File
# Begin Source File

SOURCE=.\physdecalsys.cpp
# End Source File
# Begin Source File

SOURCE=.\physdynamicsavesystem.cpp
# End Source File
# Begin Source File

SOURCE=.\physgridcull.cpp
# End Source File
# Begin Source File

SOURCE=.\physresourcemgr.cpp
# End Source File
# Begin Source File

SOURCE=.\physstaticsavesystem.cpp
# End Source File
# Begin Source File

SOURCE=.\phystexproject.cpp
# End Source File
# Begin Source File

SOURCE=.\progcall.cpp
# End Source File
# Begin Source File

SOURCE=.\projectile.cpp
# End Source File
# Begin Source File

SOURCE=.\projectormanager.cpp
# End Source File
# Begin Source File

SOURCE=.\pscene.cpp
# End Source File
# Begin Source File

SOURCE=.\pscene_collision.cpp
# End Source File
# Begin Source File

SOURCE=.\pscene_decal.cpp
# End Source File
# Begin Source File

SOURCE=.\pscene_lighting.cpp
# End Source File
# Begin Source File

SOURCE=.\pscene_projectors.cpp
# End Source File
# Begin Source File

SOURCE=.\pscene_saveload.cpp
# End Source File
# Begin Source File

SOURCE=.\pscene_vis.cpp
# End Source File
# Begin Source File

SOURCE=.\rbody.cpp
# End Source File
# Begin Source File

SOURCE=.\rbody_obsolete.cpp
# End Source File
# Begin Source File

SOURCE=.\renderobjphys.cpp
# End Source File
# Begin Source File

SOURCE=.\renegadeterrainmaterialpass.cpp
# End Source File
# Begin Source File

SOURCE=.\renegadeterrainpatch.cpp
# End Source File
# Begin Source File

SOURCE=.\ridermanager.cpp
# End Source File
# Begin Source File

SOURCE=.\shakeablestaticphys.cpp
# End Source File
# Begin Source File

SOURCE=.\staticaabtreecull.cpp
# End Source File
# Begin Source File

SOURCE=.\staticanimphys.cpp
# End Source File
# Begin Source File

SOURCE=.\staticphys.cpp
# End Source File
# Begin Source File

SOURCE=.\stealtheffect.cpp
# End Source File
# Begin Source File

SOURCE=.\terrainmaterial.cpp
# End Source File
# Begin Source File

SOURCE=.\timeddecophys.cpp
# End Source File
# Begin Source File

SOURCE=.\trackedvehicle.cpp
# End Source File
# Begin Source File

SOURCE=.\transitioneffect.cpp
# End Source File
# Begin Source File

SOURCE=.\umbrasupport.cpp
# End Source File
# Begin Source File

SOURCE=.\vehicledazzle.cpp
# End Source File
# Begin Source File

SOURCE=.\vehiclephys.cpp
# End Source File
# Begin Source File

SOURCE=.\visoptimizationcontext.cpp
# End Source File
# Begin Source File

SOURCE=.\visoptprogress.cpp
# End Source File
# Begin Source File

SOURCE=.\visrendercontext.cpp
# End Source File
# Begin Source File

SOURCE=.\vissample.cpp
# End Source File
# Begin Source File

SOURCE=.\vissectorstats.cpp
# End Source File
# Begin Source File

SOURCE=.\vistable.cpp
# End Source File
# Begin Source File

SOURCE=.\vistablemgr.cpp
# End Source File
# Begin Source File

SOURCE=.\vtolvehicle.cpp
# End Source File
# Begin Source File

SOURCE=.\waypath.cpp
# End Source File
# Begin Source File

SOURCE=.\waypoint.cpp
# End Source File
# Begin Source File

SOURCE=.\wheel.cpp
# End Source File
# Begin Source File

SOURCE=.\wheelvehicle.cpp
# End Source File
# Begin Source File

SOURCE=.\wwphys.cpp
# End Source File
# End Group
# Begin Group "Headers"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\accessiblephys.h
# End Source File
# Begin Source File

SOURCE=.\animcollisionmanager.h
# End Source File
# Begin Source File

SOURCE=.\bpt.h
# End Source File
# Begin Source File

SOURCE=.\camerashakesystem.h
# End Source File
# Begin Source File

SOURCE=.\cloud.h
# End Source File
# Begin Source File

SOURCE=.\decophys.h
# End Source File
# Begin Source File

SOURCE=.\dynamicaabtreecull.h
# End Source File
# Begin Source File

SOURCE=.\dynamicanimphys.h
# End Source File
# Begin Source File

SOURCE=.\dynamicphys.h
# End Source File
# Begin Source File

SOURCE=.\dynamicshadowmanager.h
# End Source File
# Begin Source File

SOURCE=.\dyntexproject.h
# End Source File
# Begin Source File

SOURCE=.\floodfillbox.h
# End Source File
# Begin Source File

SOURCE=.\floodfillgrid.h
# End Source File
# Begin Source File

SOURCE=.\grideffect.h
# End Source File
# Begin Source File

SOURCE=.\heightdb.h
# End Source File
# Begin Source File

SOURCE=.\humanphys.h
# End Source File
# Begin Source File

SOURCE=.\lightcull.h
# End Source File
# Begin Source File

SOURCE=.\lightexclude.h
# End Source File
# Begin Source File

SOURCE=.\lightphys.h
# End Source File
# Begin Source File

SOURCE=.\lightsolve.h
# End Source File
# Begin Source File

SOURCE=.\lightsolvecontext.h
# End Source File
# Begin Source File

SOURCE=.\lightsolveprogress.h
# End Source File
# Begin Source File

SOURCE=.\materialeffect.h
# End Source File
# Begin Source File

SOURCE=.\materialeffectlist.h
# End Source File
# Begin Source File

SOURCE=.\motorcycle.h
# End Source File
# Begin Source File

SOURCE=.\motorvehicle.h
# End Source File
# Begin Source File

SOURCE=.\movephys.h
# End Source File
# Begin Source File

SOURCE=.\octbox.h
# End Source File
# Begin Source File

SOURCE=.\Path.h
# End Source File
# Begin Source File

SOURCE=.\PathDebugPlotter.h
# End Source File
# Begin Source File

SOURCE=.\Pathfind.h
# End Source File
# Begin Source File

SOURCE=.\pathfindbox.h
# End Source File
# Begin Source File

SOURCE=.\PathfindPortal.h
# End Source File
# Begin Source File

SOURCE=.\PathfindSector.h
# End Source File
# Begin Source File

SOURCE=.\pathmgr.h
# End Source File
# Begin Source File

SOURCE=.\PathNode.h
# End Source File
# Begin Source File

SOURCE=.\PathObject.h
# End Source File
# Begin Source File

SOURCE=.\pathsolve.h
# End Source File
# Begin Source File

SOURCE=.\phunits.h
# End Source File
# Begin Source File

SOURCE=.\phys.h
# End Source File
# Begin Source File

SOURCE=.\phys3.h
# End Source File
# Begin Source File

SOURCE=.\physaabtreecull.h
# End Source File
# Begin Source File

SOURCE=.\physcoltest.h
# End Source File
# Begin Source File

SOURCE=.\physcon.h
# End Source File
# Begin Source File

SOURCE=.\physcontrol.h
# End Source File
# Begin Source File

SOURCE=.\physdecalsys.h
# End Source File
# Begin Source File

SOURCE=.\physdynamicsavesystem.h
# End Source File
# Begin Source File

SOURCE=.\physgridcull.h
# End Source File
# Begin Source File

SOURCE=.\physinttest.h
# End Source File
# Begin Source File

SOURCE=.\physlist.h
# End Source File
# Begin Source File

SOURCE=.\physobserver.h
# End Source File
# Begin Source File

SOURCE=.\physresourcemgr.h
# End Source File
# Begin Source File

SOURCE=.\physstaticsavesystem.h
# End Source File
# Begin Source File

SOURCE=.\phystexproject.h
# End Source File
# Begin Source File

SOURCE=.\progcall.h
# End Source File
# Begin Source File

SOURCE=.\projectile.h
# End Source File
# Begin Source File

SOURCE=.\projectormanager.h
# End Source File
# Begin Source File

SOURCE=.\pscene.h
# End Source File
# Begin Source File

SOURCE=.\rbody.h
# End Source File
# Begin Source File

SOURCE=.\renderobjphys.h
# End Source File
# Begin Source File

SOURCE=.\renegadeterrainmaterialpass.h
# End Source File
# Begin Source File

SOURCE=.\renegadeterrainpatch.h
# End Source File
# Begin Source File

SOURCE=.\ridermanager.h
# End Source File
# Begin Source File

SOURCE=.\shakeablestaticphys.h
# End Source File
# Begin Source File

SOURCE=.\staticaabtreecull.h
# End Source File
# Begin Source File

SOURCE=.\staticanimphys.h
# End Source File
# Begin Source File

SOURCE=.\staticphys.h
# End Source File
# Begin Source File

SOURCE=.\stealtheffect.h
# End Source File
# Begin Source File

SOURCE=.\terrainmaterial.h
# End Source File
# Begin Source File

SOURCE=.\timeddecophys.h
# End Source File
# Begin Source File

SOURCE=.\trackedvehicle.h
# End Source File
# Begin Source File

SOURCE=.\transitioneffect.h
# End Source File
# Begin Source File

SOURCE=.\umbrasupport.h
# End Source File
# Begin Source File

SOURCE=.\vehicledazzle.h
# End Source File
# Begin Source File

SOURCE=.\vehiclephys.h
# End Source File
# Begin Source File

SOURCE=.\visenum.h
# End Source File
# Begin Source File

SOURCE=.\visoptimizationcontext.h
# End Source File
# Begin Source File

SOURCE=.\visoptprogress.h
# End Source File
# Begin Source File

SOURCE=.\visrendercontext.h
# End Source File
# Begin Source File

SOURCE=.\vissample.h
# End Source File
# Begin Source File

SOURCE=.\vissectorstats.h
# End Source File
# Begin Source File

SOURCE=.\vistable.h
# End Source File
# Begin Source File

SOURCE=.\vistablemgr.h
# End Source File
# Begin Source File

SOURCE=.\vtolvehicle.h
# End Source File
# Begin Source File

SOURCE=.\waypath.h
# End Source File
# Begin Source File

SOURCE=.\waypathposition.h
# End Source File
# Begin Source File

SOURCE=.\waypoint.h
# End Source File
# Begin Source File

SOURCE=.\wheel.h
# End Source File
# Begin Source File

SOURCE=.\wheelvehicle.h
# End Source File
# Begin Source File

SOURCE=.\wwphys.h
# End Source File
# Begin Source File

SOURCE=.\wwphysids.h
# End Source File
# Begin Source File

SOURCE=.\wwphystrig.h
# End Source File
# Begin Source File

SOURCE=.\zone.h
# End Source File
# End Group
# Begin Group "Debug Widgets"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bin_aabox.cpp
# End Source File
# Begin Source File

SOURCE=.\bin_aabox.h
# End Source File
# Begin Source File

SOURCE=.\bin_axes.cpp
# End Source File
# Begin Source File

SOURCE=.\bin_axes.h
# End Source File
# Begin Source File

SOURCE=.\bin_obbox.cpp
# End Source File
# Begin Source File

SOURCE=.\bin_obbox.h
# End Source File
# Begin Source File

SOURCE=.\bin_point.cpp
# End Source File
# Begin Source File

SOURCE=.\bin_point.h
# End Source File
# Begin Source File

SOURCE=.\bin_vector.cpp
# End Source File
# Begin Source File

SOURCE=.\bin_vector.h
# End Source File
# Begin Source File

SOURCE=.\widgets.cpp
# End Source File
# Begin Source File

SOURCE=.\widgets.h
# End Source File
# Begin Source File

SOURCE=.\widgetuser.cpp
# End Source File
# Begin Source File

SOURCE=.\widgetuser.h
# End Source File
# End Group
# End Target
# End Project
