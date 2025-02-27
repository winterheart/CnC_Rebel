# Microsoft Developer Studio Project File - Name="pluglib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=pluglib - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pluglib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pluglib.mak" CFG="pluglib - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pluglib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "pluglib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "pluglib - Win32 Hybrid" (based on "Win32 (x86) Static Library")
!MESSAGE "pluglib - Win32 GMax Hybrid" (based on "Win32 (x86) Static Library")
!MESSAGE "pluglib - Win32 GMax Release" (based on "Win32 (x86) Static Library")
!MESSAGE "pluglib - Win32 Max4 Hybrid" (based on "Win32 (x86) Static Library")
!MESSAGE "pluglib - Win32 Max4 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Commando/Code/Tools/pluglib", TSJAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pluglib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /YX /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /D "_DEBUG" /D "_WINDOWS" /YX /FD WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\Debug\pluglibd.lib"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "pluglib_"
# PROP BASE Intermediate_Dir "pluglib_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Hybrid"
# PROP Intermediate_Dir "Hybrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Z7 /Od /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\Lib\pluglib.lib"
# ADD LIB32 /nologo /out:".\Hybrid\pluglib.lib"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "GMax_Hybrid"
# PROP BASE Intermediate_Dir "GMax_Hybrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "GMax_Hybrid"
# PROP Intermediate_Dir "GMax_Hybrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Z7 /Od /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Z7 /Od /D "WIN32" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\Hybrid\pluglib.lib"
# ADD LIB32 /nologo /out:".\GMax_Hybrid\pluglib.lib"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "GMax_Release"
# PROP BASE Intermediate_Dir "GMax_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "GMax_Release"
# PROP Intermediate_Dir "GMax_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /YX /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"./GMaxRelease\pluglib.lib"
# ADD LIB32 /nologo /out:".\GMax_Release\pluglib.lib"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Max4_Hybrid"
# PROP BASE Intermediate_Dir "Max4_Hybrid"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Max4_Hybrid"
# PROP Intermediate_Dir "Max4_Hybrid"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Z7 /Od /D "WIN32" /D "_WINDOWS" /FR /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /ZI /Od /D "WIN32" /D "_WINDOWS" /D "W3D_MAX4" /FR /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\GMax_Hybrid\pluglib.lib"
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Max4_Release"
# PROP BASE Intermediate_Dir "Max4_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Max4 Release"
# PROP Intermediate_Dir "Max4 Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "W3D_MAX4" /YX /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:".\GMax_Release\pluglib.lib"
# ADD LIB32 /nologo /out:".\Max4_Release\pluglib.lib"

!ENDIF 

# Begin Target

# Name "pluglib - Win32 Release"
# Name "pluglib - Win32 Debug"
# Name "pluglib - Win32 Hybrid"
# Name "pluglib - Win32 GMax Hybrid"
# Name "pluglib - Win32 GMax Release"
# Name "pluglib - Win32 Max4 Hybrid"
# Name "pluglib - Win32 Max4 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\chunkio.cpp
DEP_CPP_CHUNK=\
	".\always.h"\
	".\bittype.h"\
	".\bool.h"\
	".\borlandc.h"\
	".\chunkio.h"\
	".\iostruct.h"\
	".\visualc.h"\
	".\watcom.h"\
	".\wwfile.h"\
	
NODEP_CPP_CHUNK=\
	".\osdep.h"\
	

!IF  "$(CFG)" == "pluglib - Win32 Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\EULER.CPP
DEP_CPP_EULER=\
	".\EULER.H"\
	{$(INCLUDE)}"acolor.h"\
	{$(INCLUDE)}"actiontable.h"\
	{$(INCLUDE)}"animtbl.h"\
	{$(INCLUDE)}"appio.h"\
	{$(INCLUDE)}"assert1.h"\
	{$(INCLUDE)}"baseinterface.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bitarray.h"\
	{$(INCLUDE)}"box2.h"\
	{$(INCLUDE)}"box3.h"\
	{$(INCLUDE)}"buildver.h"\
	{$(INCLUDE)}"captypes.h"\
	{$(INCLUDE)}"channels.h"\
	{$(INCLUDE)}"cmdmode.h"\
	{$(INCLUDE)}"color.h"\
	{$(INCLUDE)}"coreexp.h"\
	{$(INCLUDE)}"custcont.h"\
	{$(INCLUDE)}"dbgprint.h"\
	{$(INCLUDE)}"dpoint3.h"\
	{$(INCLUDE)}"euler.h"\
	{$(INCLUDE)}"evuser.h"\
	{$(INCLUDE)}"excllist.h"\
	{$(INCLUDE)}"export.h"\
	{$(INCLUDE)}"gencam.h"\
	{$(INCLUDE)}"genhier.h"\
	{$(INCLUDE)}"genlight.h"\
	{$(INCLUDE)}"genshape.h"\
	{$(INCLUDE)}"geom.h"\
	{$(INCLUDE)}"geomlib.h"\
	{$(INCLUDE)}"gfloat.h"\
	{$(INCLUDE)}"gfx.h"\
	{$(INCLUDE)}"gfxlib.h"\
	{$(INCLUDE)}"gutil.h"\
	{$(INCLUDE)}"hitdata.h"\
	{$(INCLUDE)}"hold.h"\
	{$(INCLUDE)}"icolorman.h"\
	{$(INCLUDE)}"ifnpub.h"\
	{$(INCLUDE)}"impapi.h"\
	{$(INCLUDE)}"impexp.h"\
	{$(INCLUDE)}"imtl.h"\
	{$(INCLUDE)}"inode.h"\
	{$(INCLUDE)}"interval.h"\
	{$(INCLUDE)}"ioapi.h"\
	{$(INCLUDE)}"iparamb.h"\
	{$(INCLUDE)}"ipoint2.h"\
	{$(INCLUDE)}"ipoint3.h"\
	{$(INCLUDE)}"istdplug.h"\
	{$(INCLUDE)}"itreevw.h"\
	{$(INCLUDE)}"lockid.h"\
	{$(INCLUDE)}"log.h"\
	{$(INCLUDE)}"matrix2.h"\
	{$(INCLUDE)}"matrix3.h"\
	{$(INCLUDE)}"max.h"\
	{$(INCLUDE)}"maxapi.h"\
	{$(INCLUDE)}"maxcom.h"\
	{$(INCLUDE)}"maxtess.h"\
	{$(INCLUDE)}"maxtypes.h"\
	{$(INCLUDE)}"mesh.h"\
	{$(INCLUDE)}"meshlib.h"\
	{$(INCLUDE)}"mnbigmat.h"\
	{$(INCLUDE)}"mncommon.h"\
	{$(INCLUDE)}"mnmath.h"\
	{$(INCLUDE)}"mnmesh.h"\
	{$(INCLUDE)}"mouseman.h"\
	{$(INCLUDE)}"mtl.h"\
	{$(INCLUDE)}"namesel.h"\
	{$(INCLUDE)}"nametab.h"\
	{$(INCLUDE)}"object.h"\
	{$(INCLUDE)}"objmode.h"\
	{$(INCLUDE)}"paramtype.h"\
	{$(INCLUDE)}"patch.h"\
	{$(INCLUDE)}"patchlib.h"\
	{$(INCLUDE)}"patchobj.h"\
	{$(INCLUDE)}"plugapi.h"\
	{$(INCLUDE)}"plugin.h"\
	{$(INCLUDE)}"point2.h"\
	{$(INCLUDE)}"point3.h"\
	{$(INCLUDE)}"point4.h"\
	{$(INCLUDE)}"polyobj.h"\
	{$(INCLUDE)}"polyshp.h"\
	{$(INCLUDE)}"ptrvec.h"\
	{$(INCLUDE)}"quat.h"\
	{$(INCLUDE)}"random.h"\
	{$(INCLUDE)}"ref.h"\
	{$(INCLUDE)}"render.h"\
	{$(INCLUDE)}"renderelements.h"\
	{$(INCLUDE)}"rtclick.h"\
	{$(INCLUDE)}"sbmtlapi.h"\
	{$(INCLUDE)}"sceneapi.h"\
	{$(INCLUDE)}"sfx.h"\
	{$(INCLUDE)}"shape.h"\
	{$(INCLUDE)}"shphier.h"\
	{$(INCLUDE)}"shpsels.h"\
	{$(INCLUDE)}"snap.h"\
	{$(INCLUDE)}"soundobj.h"\
	{$(INCLUDE)}"spline3d.h"\
	{$(INCLUDE)}"stack.h"\
	{$(INCLUDE)}"stack3.h"\
	{$(INCLUDE)}"strbasic.h"\
	{$(INCLUDE)}"strclass.h"\
	{$(INCLUDE)}"svcore.h"\
	{$(INCLUDE)}"systemutilities.h"\
	{$(INCLUDE)}"tab.h"\
	{$(INCLUDE)}"templt.h"\
	{$(INCLUDE)}"trig.h"\
	{$(INCLUDE)}"triobj.h"\
	{$(INCLUDE)}"udmia64.h"\
	{$(INCLUDE)}"units.h"\
	{$(INCLUDE)}"utilexp.h"\
	{$(INCLUDE)}"utillib.h"\
	{$(INCLUDE)}"vedge.h"\
	{$(INCLUDE)}"winutil.h"\
	

!IF  "$(CFG)" == "pluglib - Win32 Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HSV.CPP
DEP_CPP_HSV_C=\
	".\always.h"\
	".\bool.h"\
	".\borlandc.h"\
	".\hsv.h"\
	".\rgb.h"\
	".\visualc.h"\
	".\watcom.h"\
	

!IF  "$(CFG)" == "pluglib - Win32 Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\JShell.CPP
DEP_CPP_JSHEL=\
	".\always.h"\
	".\bool.h"\
	".\borlandc.h"\
	".\visualc.h"\
	".\watcom.h"\
	

!IF  "$(CFG)" == "pluglib - Win32 Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\matrix3d.cpp
DEP_CPP_MATRI=\
	".\always.h"\
	".\bool.h"\
	".\borlandc.h"\
	".\matrix3d.h"\
	".\matrix4.h"\
	".\vector2.h"\
	".\vector3.h"\
	".\vector4.h"\
	".\visualc.h"\
	".\w3dquat.h"\
	".\watcom.h"\
	".\wwmath.h"\
	".\WWmatrix3.h"\
	
NODEP_CPP_MATRI=\
	".\osdep.h"\
	

!IF  "$(CFG)" == "pluglib - Win32 Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\matrix4.cpp
DEP_CPP_MATRIX=\
	".\always.h"\
	".\bool.h"\
	".\borlandc.h"\
	".\matrix3d.h"\
	".\matrix4.h"\
	".\vector2.h"\
	".\vector3.h"\
	".\vector4.h"\
	".\visualc.h"\
	".\watcom.h"\
	".\wwmath.h"\
	".\WWmatrix3.h"\
	
NODEP_CPP_MATRIX=\
	".\osdep.h"\
	

!IF  "$(CFG)" == "pluglib - Win32 Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nodefilt.cpp
DEP_CPP_NODEF=\
	".\always.h"\
	".\bool.h"\
	".\borlandc.h"\
	".\nodefilt.h"\
	".\visualc.h"\
	".\watcom.h"\
	{$(INCLUDE)}"acolor.h"\
	{$(INCLUDE)}"actiontable.h"\
	{$(INCLUDE)}"animtbl.h"\
	{$(INCLUDE)}"appio.h"\
	{$(INCLUDE)}"assert1.h"\
	{$(INCLUDE)}"baseinterface.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bitarray.h"\
	{$(INCLUDE)}"box2.h"\
	{$(INCLUDE)}"box3.h"\
	{$(INCLUDE)}"buildver.h"\
	{$(INCLUDE)}"captypes.h"\
	{$(INCLUDE)}"channels.h"\
	{$(INCLUDE)}"cmdmode.h"\
	{$(INCLUDE)}"color.h"\
	{$(INCLUDE)}"coreexp.h"\
	{$(INCLUDE)}"custcont.h"\
	{$(INCLUDE)}"dbgprint.h"\
	{$(INCLUDE)}"dpoint3.h"\
	{$(INCLUDE)}"euler.h"\
	{$(INCLUDE)}"evuser.h"\
	{$(INCLUDE)}"excllist.h"\
	{$(INCLUDE)}"export.h"\
	{$(INCLUDE)}"gencam.h"\
	{$(INCLUDE)}"genhier.h"\
	{$(INCLUDE)}"genlight.h"\
	{$(INCLUDE)}"genshape.h"\
	{$(INCLUDE)}"geom.h"\
	{$(INCLUDE)}"geomlib.h"\
	{$(INCLUDE)}"gfloat.h"\
	{$(INCLUDE)}"gfx.h"\
	{$(INCLUDE)}"gfxlib.h"\
	{$(INCLUDE)}"gutil.h"\
	{$(INCLUDE)}"hitdata.h"\
	{$(INCLUDE)}"hold.h"\
	{$(INCLUDE)}"icolorman.h"\
	{$(INCLUDE)}"ifnpub.h"\
	{$(INCLUDE)}"impapi.h"\
	{$(INCLUDE)}"impexp.h"\
	{$(INCLUDE)}"imtl.h"\
	{$(INCLUDE)}"inode.h"\
	{$(INCLUDE)}"interval.h"\
	{$(INCLUDE)}"ioapi.h"\
	{$(INCLUDE)}"iparamb.h"\
	{$(INCLUDE)}"ipoint2.h"\
	{$(INCLUDE)}"ipoint3.h"\
	{$(INCLUDE)}"istdplug.h"\
	{$(INCLUDE)}"itreevw.h"\
	{$(INCLUDE)}"lockid.h"\
	{$(INCLUDE)}"log.h"\
	{$(INCLUDE)}"matrix2.h"\
	{$(INCLUDE)}"matrix3.h"\
	{$(INCLUDE)}"max.h"\
	{$(INCLUDE)}"maxapi.h"\
	{$(INCLUDE)}"maxcom.h"\
	{$(INCLUDE)}"maxtess.h"\
	{$(INCLUDE)}"maxtypes.h"\
	{$(INCLUDE)}"mesh.h"\
	{$(INCLUDE)}"meshlib.h"\
	{$(INCLUDE)}"mnbigmat.h"\
	{$(INCLUDE)}"mncommon.h"\
	{$(INCLUDE)}"mnmath.h"\
	{$(INCLUDE)}"mnmesh.h"\
	{$(INCLUDE)}"mouseman.h"\
	{$(INCLUDE)}"mtl.h"\
	{$(INCLUDE)}"namesel.h"\
	{$(INCLUDE)}"nametab.h"\
	{$(INCLUDE)}"object.h"\
	{$(INCLUDE)}"objmode.h"\
	{$(INCLUDE)}"paramtype.h"\
	{$(INCLUDE)}"patch.h"\
	{$(INCLUDE)}"patchlib.h"\
	{$(INCLUDE)}"patchobj.h"\
	{$(INCLUDE)}"plugapi.h"\
	{$(INCLUDE)}"plugin.h"\
	{$(INCLUDE)}"point2.h"\
	{$(INCLUDE)}"point3.h"\
	{$(INCLUDE)}"point4.h"\
	{$(INCLUDE)}"polyobj.h"\
	{$(INCLUDE)}"polyshp.h"\
	{$(INCLUDE)}"ptrvec.h"\
	{$(INCLUDE)}"quat.h"\
	{$(INCLUDE)}"random.h"\
	{$(INCLUDE)}"ref.h"\
	{$(INCLUDE)}"render.h"\
	{$(INCLUDE)}"renderelements.h"\
	{$(INCLUDE)}"rtclick.h"\
	{$(INCLUDE)}"sbmtlapi.h"\
	{$(INCLUDE)}"sceneapi.h"\
	{$(INCLUDE)}"sfx.h"\
	{$(INCLUDE)}"shape.h"\
	{$(INCLUDE)}"shphier.h"\
	{$(INCLUDE)}"shpsels.h"\
	{$(INCLUDE)}"snap.h"\
	{$(INCLUDE)}"soundobj.h"\
	{$(INCLUDE)}"spline3d.h"\
	{$(INCLUDE)}"stack.h"\
	{$(INCLUDE)}"stack3.h"\
	{$(INCLUDE)}"strbasic.h"\
	{$(INCLUDE)}"strclass.h"\
	{$(INCLUDE)}"svcore.h"\
	{$(INCLUDE)}"systemutilities.h"\
	{$(INCLUDE)}"tab.h"\
	{$(INCLUDE)}"templt.h"\
	{$(INCLUDE)}"trig.h"\
	{$(INCLUDE)}"triobj.h"\
	{$(INCLUDE)}"udmia64.h"\
	{$(INCLUDE)}"units.h"\
	{$(INCLUDE)}"utilexp.h"\
	{$(INCLUDE)}"utillib.h"\
	{$(INCLUDE)}"vedge.h"\
	{$(INCLUDE)}"winutil.h"\
	

!IF  "$(CFG)" == "pluglib - Win32 Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nodelist.cpp
DEP_CPP_NODEL=\
	".\always.h"\
	".\bool.h"\
	".\borlandc.h"\
	".\nodefilt.h"\
	".\nodelist.h"\
	".\visualc.h"\
	".\watcom.h"\
	{$(INCLUDE)}"acolor.h"\
	{$(INCLUDE)}"actiontable.h"\
	{$(INCLUDE)}"animtbl.h"\
	{$(INCLUDE)}"appio.h"\
	{$(INCLUDE)}"assert1.h"\
	{$(INCLUDE)}"baseinterface.h"\
	{$(INCLUDE)}"basetsd.h"\
	{$(INCLUDE)}"bitarray.h"\
	{$(INCLUDE)}"box2.h"\
	{$(INCLUDE)}"box3.h"\
	{$(INCLUDE)}"buildver.h"\
	{$(INCLUDE)}"captypes.h"\
	{$(INCLUDE)}"channels.h"\
	{$(INCLUDE)}"cmdmode.h"\
	{$(INCLUDE)}"color.h"\
	{$(INCLUDE)}"coreexp.h"\
	{$(INCLUDE)}"custcont.h"\
	{$(INCLUDE)}"dbgprint.h"\
	{$(INCLUDE)}"dpoint3.h"\
	{$(INCLUDE)}"euler.h"\
	{$(INCLUDE)}"evuser.h"\
	{$(INCLUDE)}"excllist.h"\
	{$(INCLUDE)}"export.h"\
	{$(INCLUDE)}"gencam.h"\
	{$(INCLUDE)}"genhier.h"\
	{$(INCLUDE)}"genlight.h"\
	{$(INCLUDE)}"genshape.h"\
	{$(INCLUDE)}"geom.h"\
	{$(INCLUDE)}"geomlib.h"\
	{$(INCLUDE)}"gfloat.h"\
	{$(INCLUDE)}"gfx.h"\
	{$(INCLUDE)}"gfxlib.h"\
	{$(INCLUDE)}"gutil.h"\
	{$(INCLUDE)}"hitdata.h"\
	{$(INCLUDE)}"hold.h"\
	{$(INCLUDE)}"icolorman.h"\
	{$(INCLUDE)}"ifnpub.h"\
	{$(INCLUDE)}"impapi.h"\
	{$(INCLUDE)}"impexp.h"\
	{$(INCLUDE)}"imtl.h"\
	{$(INCLUDE)}"inode.h"\
	{$(INCLUDE)}"interval.h"\
	{$(INCLUDE)}"ioapi.h"\
	{$(INCLUDE)}"iparamb.h"\
	{$(INCLUDE)}"ipoint2.h"\
	{$(INCLUDE)}"ipoint3.h"\
	{$(INCLUDE)}"istdplug.h"\
	{$(INCLUDE)}"itreevw.h"\
	{$(INCLUDE)}"lockid.h"\
	{$(INCLUDE)}"log.h"\
	{$(INCLUDE)}"matrix2.h"\
	{$(INCLUDE)}"matrix3.h"\
	{$(INCLUDE)}"max.h"\
	{$(INCLUDE)}"maxapi.h"\
	{$(INCLUDE)}"maxcom.h"\
	{$(INCLUDE)}"maxtess.h"\
	{$(INCLUDE)}"maxtypes.h"\
	{$(INCLUDE)}"mesh.h"\
	{$(INCLUDE)}"meshlib.h"\
	{$(INCLUDE)}"mnbigmat.h"\
	{$(INCLUDE)}"mncommon.h"\
	{$(INCLUDE)}"mnmath.h"\
	{$(INCLUDE)}"mnmesh.h"\
	{$(INCLUDE)}"mouseman.h"\
	{$(INCLUDE)}"mtl.h"\
	{$(INCLUDE)}"namesel.h"\
	{$(INCLUDE)}"nametab.h"\
	{$(INCLUDE)}"object.h"\
	{$(INCLUDE)}"objmode.h"\
	{$(INCLUDE)}"paramtype.h"\
	{$(INCLUDE)}"patch.h"\
	{$(INCLUDE)}"patchlib.h"\
	{$(INCLUDE)}"patchobj.h"\
	{$(INCLUDE)}"plugapi.h"\
	{$(INCLUDE)}"plugin.h"\
	{$(INCLUDE)}"point2.h"\
	{$(INCLUDE)}"point3.h"\
	{$(INCLUDE)}"point4.h"\
	{$(INCLUDE)}"polyobj.h"\
	{$(INCLUDE)}"polyshp.h"\
	{$(INCLUDE)}"ptrvec.h"\
	{$(INCLUDE)}"quat.h"\
	{$(INCLUDE)}"random.h"\
	{$(INCLUDE)}"ref.h"\
	{$(INCLUDE)}"render.h"\
	{$(INCLUDE)}"renderelements.h"\
	{$(INCLUDE)}"rtclick.h"\
	{$(INCLUDE)}"sbmtlapi.h"\
	{$(INCLUDE)}"sceneapi.h"\
	{$(INCLUDE)}"sfx.h"\
	{$(INCLUDE)}"shape.h"\
	{$(INCLUDE)}"shphier.h"\
	{$(INCLUDE)}"shpsels.h"\
	{$(INCLUDE)}"snap.h"\
	{$(INCLUDE)}"soundobj.h"\
	{$(INCLUDE)}"spline3d.h"\
	{$(INCLUDE)}"stack.h"\
	{$(INCLUDE)}"stack3.h"\
	{$(INCLUDE)}"strbasic.h"\
	{$(INCLUDE)}"strclass.h"\
	{$(INCLUDE)}"svcore.h"\
	{$(INCLUDE)}"systemutilities.h"\
	{$(INCLUDE)}"tab.h"\
	{$(INCLUDE)}"templt.h"\
	{$(INCLUDE)}"trig.h"\
	{$(INCLUDE)}"triobj.h"\
	{$(INCLUDE)}"udmia64.h"\
	{$(INCLUDE)}"units.h"\
	{$(INCLUDE)}"utilexp.h"\
	{$(INCLUDE)}"utillib.h"\
	{$(INCLUDE)}"vedge.h"\
	{$(INCLUDE)}"winutil.h"\
	

!IF  "$(CFG)" == "pluglib - Win32 Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PALETTE.CPP
DEP_CPP_PALET=\
	".\always.h"\
	".\bool.h"\
	".\borlandc.h"\
	".\palette.h"\
	".\rgb.h"\
	".\visualc.h"\
	".\watcom.h"\
	

!IF  "$(CFG)" == "pluglib - Win32 Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RAWFILE.CPP
DEP_CPP_RAWFI=\
	".\always.h"\
	".\bool.h"\
	".\borlandc.h"\
	".\rawfile.h"\
	".\visualc.h"\
	".\watcom.h"\
	".\win.h"\
	".\wwfile.h"\
	
NODEP_CPP_RAWFI=\
	".\osdep.h"\
	

!IF  "$(CFG)" == "pluglib - Win32 Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\realcrc.cpp
DEP_CPP_REALC=\
	".\realcrc.h"\
	

!IF  "$(CFG)" == "pluglib - Win32 Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RGB.CPP
DEP_CPP_RGB_C=\
	".\always.h"\
	".\bool.h"\
	".\borlandc.h"\
	".\hsv.h"\
	".\palette.h"\
	".\rgb.h"\
	".\visualc.h"\
	".\watcom.h"\
	

!IF  "$(CFG)" == "pluglib - Win32 Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\tri.cpp
DEP_CPP_TRI_C=\
	".\always.h"\
	".\bool.h"\
	".\borlandc.h"\
	".\tri.h"\
	".\vector2.h"\
	".\vector3.h"\
	".\vector4.h"\
	".\visualc.h"\
	".\watcom.h"\
	".\wwmath.h"\
	
NODEP_CPP_TRI_C=\
	".\osdep.h"\
	

!IF  "$(CFG)" == "pluglib - Win32 Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Vector.CPP
DEP_CPP_VECTO=\
	".\always.h"\
	".\bool.h"\
	".\borlandc.h"\
	".\noinit.h"\
	".\Vector.H"\
	".\visualc.h"\
	".\watcom.h"\
	

!IF  "$(CFG)" == "pluglib - Win32 Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\w3dquat.cpp
DEP_CPP_W3DQU=\
	".\always.h"\
	".\bool.h"\
	".\borlandc.h"\
	".\matrix3d.h"\
	".\matrix4.h"\
	".\vector2.h"\
	".\vector3.h"\
	".\vector4.h"\
	".\visualc.h"\
	".\w3dquat.h"\
	".\watcom.h"\
	".\wwmath.h"\
	".\WWmatrix3.h"\
	
NODEP_CPP_W3DQU=\
	".\osdep.h"\
	

!IF  "$(CFG)" == "pluglib - Win32 Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\wwmath.cpp
DEP_CPP_WWMAT=\
	".\always.h"\
	".\bool.h"\
	".\borlandc.h"\
	".\visualc.h"\
	".\watcom.h"\
	".\wwmath.h"\
	

!IF  "$(CFG)" == "pluglib - Win32 Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\WWmatrix3.cpp
DEP_CPP_WWMATR=\
	".\always.h"\
	".\bool.h"\
	".\borlandc.h"\
	".\matrix3d.h"\
	".\matrix4.h"\
	".\vector2.h"\
	".\vector3.h"\
	".\vector4.h"\
	".\visualc.h"\
	".\w3dquat.h"\
	".\watcom.h"\
	".\wwmath.h"\
	".\WWmatrix3.h"\
	
NODEP_CPP_WWMATR=\
	".\osdep.h"\
	

!IF  "$(CFG)" == "pluglib - Win32 Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Debug"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 GMax Release"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Hybrid"

!ELSEIF  "$(CFG)" == "pluglib - Win32 Max4 Release"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\aaplane.h
# End Source File
# Begin Source File

SOURCE=.\always.h
# End Source File
# Begin Source File

SOURCE=.\bool.h
# End Source File
# Begin Source File

SOURCE=.\borlandc.h
# End Source File
# Begin Source File

SOURCE=.\chunkio.h
# End Source File
# Begin Source File

SOURCE=.\errclass.h
# End Source File
# Begin Source File

SOURCE=.\EULER.H
# End Source File
# Begin Source File

SOURCE=.\hsv.h
# End Source File
# Begin Source File

SOURCE=.\iostruct.h
# End Source File
# Begin Source File

SOURCE=.\matrix3d.h
# End Source File
# Begin Source File

SOURCE=.\matrix4.h
# End Source File
# Begin Source File

SOURCE=.\nodefilt.h
# End Source File
# Begin Source File

SOURCE=.\nodelist.h
# End Source File
# Begin Source File

SOURCE=.\palette.h
# End Source File
# Begin Source File

SOURCE=.\PROGRESS.H
# End Source File
# Begin Source File

SOURCE=.\rawfile.h
# End Source File
# Begin Source File

SOURCE=.\realcrc.h
# End Source File
# Begin Source File

SOURCE=.\rgb.h
# End Source File
# Begin Source File

SOURCE=.\tri.h
# End Source File
# Begin Source File

SOURCE=.\Vector.H
# End Source File
# Begin Source File

SOURCE=.\vector2.h
# End Source File
# Begin Source File

SOURCE=.\vector3i.h
# End Source File
# Begin Source File

SOURCE=.\visualc.h
# End Source File
# Begin Source File

SOURCE=.\w3dquat.h
# End Source File
# Begin Source File

SOURCE=.\watcom.h
# End Source File
# Begin Source File

SOURCE=.\win.h
# End Source File
# Begin Source File

SOURCE=.\wwfile.h
# End Source File
# Begin Source File

SOURCE=.\wwmath.h
# End Source File
# Begin Source File

SOURCE=.\WWmatrix3.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
