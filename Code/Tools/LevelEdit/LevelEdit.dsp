# Microsoft Developer Studio Project File - Name="LevelEdit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=LevelEdit - Win32 ProfileE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LevelEdit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LevelEdit.mak" CFG="LevelEdit - Win32 ProfileE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LevelEdit - Win32 DebugE" (based on "Win32 (x86) Application")
!MESSAGE "LevelEdit - Win32 ProfileE" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Commando/Code/Tools/LevelEdit", LDKBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LevelEdit - Win32 DebugE"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugE"
# PROP BASE Intermediate_Dir "DebugE"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugE"
# PROP Intermediate_Dir "DebugE"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\combat" /I "..\..\wwdebug" /I "..\..\wwmath" /I "..\..\ww3d" /I "..\..\wwphys" /I "..\..\wwlib" /I "..\..\srsdk1x\include" /I "..\..\wwaudio" /I "..\..\miles6\include" /I "..\..\wwsaveload" /I "..\..\wwnet" /I "..\wwctrl" /I "..\..\wwtranslatedb" /I "..\..\wwbitpack" /I "..\..\wwutil" /D "_DEBUG" /D "WWDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT BASE CPP /Gf /Fr
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\..\wwui" /I "..\..\combat" /I "..\..\wwdebug" /I "..\..\wwmath" /I "..\..\ww3d2" /I "..\..\wwphys" /I "..\..\wwlib" /I "..\..\srsdk1x\include" /I "..\..\wwaudio" /I "..\..\miles6\include" /I "..\..\wwsaveload" /I "..\..\wwnet" /I "..\..\wwtranslatedb" /I "..\..\wwbitpack" /I "..\..\wwutil" /I "..\..\NvDXTLib\Inc" /I "..\..\directX\include" /D "_DEBUG" /D "WWDEBUG" /D "WIN32" /D "_WINDOWS" /D "PARAM_EDITING_ON" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Gf /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wwctrld.lib srdb.lib imagehlp.lib wwtranslatedb.lib wwnet.lib ws2_32.lib combat.lib wwaudio.lib ..\..\miles6\lib\win\mss32.lib wwdebug.lib wwmath.lib ww3d.lib wwphys.lib wwlib.lib winmm.lib vfw32.lib wwutil.lib wwsaveload.lib "..\..\Graphics APIs\directx\lib\dinput.lib" "..\..\Graphics APIs\directx\lib\dxguid.lib" /nologo /subsystem:windows /map /debug /debugtype:both /machine:I386 /nodefaultlib:"libcd" /out:"Run\LevelEditD.exe"  /libpath:"..\..\Libs\debug" /libpath:"..\..\srsdk1x\msvc6\lib\debug"
# SUBTRACT BASE LINK32 /incremental:no /nodefaultlib
# ADD LINK32 combate.lib ww3d2e.lib wwbitpack.lib imagehlp.lib wwtranslatedb.lib wwnet.lib ws2_32.lib wwaudioe.lib ..\..\miles6\lib\win\mss32.lib wwdebuge.lib wwmath.lib wwphyse.lib wwlib.lib winmm.lib vfw32.lib wwutil.lib wwsaveloade.lib d3dx8.lib d3d8.lib dxguid.lib dinput8.lib NvDXTLib.lib version.lib wwui.lib shlwapi.lib /nologo /subsystem:windows /pdb:"..\..\..\Run\LevelEditD.pdb" /map:"..\..\..\Run\LevelEditD.map" /debug /debugtype:cv /machine:I386 /out:"..\..\..\Run\LevelEditD.exe"  /libpath:"..\..\Libs\debug" /libpath:"..\..\Libs\profile" /libpath:"..\..\NvDXTLib\Lib" /libpath:"..\..\directX\lib"
# SUBTRACT LINK32 /incremental:no /nodefaultlib

!ELSEIF  "$(CFG)" == "LevelEdit - Win32 ProfileE"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ProfileE"
# PROP BASE Intermediate_Dir "ProfileE"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ProfileE"
# PROP Intermediate_Dir "ProfileE"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /O2 /I "..\..\combat" /I "..\..\wwdebug" /I "..\..\wwmath" /I "..\..\ww3d" /I "..\..\wwphys" /I "..\..\wwlib" /I "..\..\srsdk1x\include" /I "..\..\wwaudio" /I "..\..\miles6\include" /I "..\..\wwsaveload" /I "..\..\wwnet" /I "..\wwctrl" /I "..\..\wwtranslatedb" /I "..\..\wwbitpack" /I "..\..\wwutil" /D "NDEBUG" /D "WWDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /I "..\..\wwui" /I "..\..\combat" /I "..\..\wwdebug" /I "..\..\wwmath" /I "..\..\ww3d2" /I "..\..\wwphys" /I "..\..\wwlib" /I "..\..\srsdk1x\include" /I "..\..\wwaudio" /I "..\..\miles6\include" /I "..\..\wwsaveload" /I "..\..\wwnet" /I "..\..\wwtranslatedb" /I "..\..\wwbitpack" /I "..\..\wwutil" /I "..\..\NvDXTLib\Inc" /I "..\..\directX\include" /D "NDEBUG" /D "WWDEBUG" /D "WIN32" /D "_WINDOWS" /D "PARAM_EDITING_ON" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 wwctrl.lib sr.lib imagehlp.lib wwtranslatedb.lib wwnet.lib ws2_32.lib combat.lib wwaudio.lib ..\..\miles6\lib\win\mss32.lib wwdebug.lib wwmath.lib ww3d.lib wwphys.lib wwlib.lib winmm.lib vfw32.lib wwutil.lib wwsaveload.lib "..\..\Graphics APIs\directx\lib\dinput.lib" "..\..\Graphics APIs\directx\lib\dxguid.lib" /nologo /subsystem:windows /profile /map:"Run/LevelEdit.map" /debug /machine:I386 /nodefaultlib:"libcd" /out:"Run\LevelEdit.exe" /libpath:"..\..\Libs\profile" /libpath:"..\..\srsdk1x\msvc6\lib\release"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 combate.lib ww3d2e.lib wwbitpack.lib imagehlp.lib wwtranslatedb.lib wwnet.lib ws2_32.lib wwaudioe.lib ..\..\miles6\lib\win\mss32.lib wwdebuge.lib wwmath.lib wwphyse.lib wwlib.lib winmm.lib vfw32.lib wwutil.lib wwsaveloade.lib d3dx8.lib d3d8.lib dxguid.lib dinput8.lib NvDXTLib.lib version.lib wwui.lib shlwapi.lib /nologo /subsystem:windows /profile /map:"..\..\..\Run\LevelEdit.map" /debug /machine:I386 /out:"..\..\..\Run\LevelEdit.exe" /libpath:"..\..\Libs\profile" /libpath:"..\..\directX\lib" /libpath:"..\..\NvDXTLib\Lib"
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "LevelEdit - Win32 DebugE"
# Name "LevelEdit - Win32 ProfileE"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\_assetmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\_wwaudio.cpp
# End Source File
# Begin Source File

SOURCE=.\assetdatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\assetpackagemgr.cpp
# End Source File
# Begin Source File

SOURCE=.\AttenuationSphere.cpp
# End Source File
# Begin Source File

SOURCE=.\Box3D.cpp
# End Source File
# Begin Source File

SOURCE=.\buildingchildnode.cpp
# End Source File
# Begin Source File

SOURCE=.\BuildingNode.cpp
# End Source File
# Begin Source File

SOURCE=.\CameraMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\CameraSettingsForm.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckingOutDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckinStyleDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ChooseModPackageDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorPickerDialogClass.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\ConversationEditorMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\ConversationPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ConversationPickerDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CoverAttackPointNode.cpp
# End Source File
# Begin Source File

SOURCE=.\CoverSpotDefinition.cpp
# End Source File
# Begin Source File

SOURCE=.\CoverSpotInfoPage.cpp
# End Source File
# Begin Source File

SOURCE=.\CoverSpotNode.cpp
# End Source File
# Begin Source File

SOURCE=.\DamageZoneNode.cpp
# End Source File
# Begin Source File

SOURCE=.\DefinitionUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\DeviceSelectionDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogToolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\DockableForm.cpp
# End Source File
# Begin Source File

SOURCE=.\DummyObjectDefinition.cpp
# End Source File
# Begin Source File

SOURCE=.\DummyObjectNode.cpp
# End Source File
# Begin Source File

SOURCE=.\editableheightfield.cpp
# End Source File
# Begin Source File

SOURCE=.\EditConversationDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\EditConversationListDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\EditConversationRemarkDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\EditDialogueDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\EditFilenameListDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\EditorAssetMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\EditorINI.cpp
# End Source File
# Begin Source File

SOURCE=.\editormixfile.cpp
# End Source File
# Begin Source File

SOURCE=.\editoronlydefinition.cpp
# End Source File
# Begin Source File

SOURCE=.\editoronlyobjectnode.cpp
# End Source File
# Begin Source File

SOURCE=.\EditorPhys.cpp
# End Source File
# Begin Source File

SOURCE=.\EditorPropSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\EditorSaveLoad.cpp
# End Source File
# Begin Source File

SOURCE=.\EditRemarkDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\EditScript.cpp
# End Source File
# Begin Source File

SOURCE=.\EditStringDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\EditStringTwiddlerDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\excel.cpp
# End Source File
# Begin Source File

SOURCE=.\excel8.cpp
# End Source File
# Begin Source File

SOURCE=.\Export.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportPresetsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\FileMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\FilePicker.cpp
# End Source File
# Begin Source File

SOURCE=.\FormToolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\GenerateBaseDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GenerateVisDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneratingEdgeSampledVisDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneratingLightVisDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneratingManualVisDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneratingPathfindDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneratingVisDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GenericTextDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GotoGroupDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GotoLocationDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GotoObjectByIDDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GotoObjectDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GrabHandles.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\heightfieldeditor.cpp
# End Source File
# Begin Source File

SOURCE=.\HeightfieldMaterialSettingsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\heightfieldmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\heightfieldpage.cpp
# End Source File
# Begin Source File

SOURCE=.\HistogramCtl.cpp
# End Source File
# Begin Source File

SOURCE=.\Icons.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportTranslationDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\IncludeFilesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\InstancesPage.cpp
# End Source File
# Begin Source File

SOURCE=.\LevelEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\LevelEdit.rc
# End Source File
# Begin Source File

SOURCE=.\LevelEditDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\LevelEditView.cpp
# End Source File
# Begin Source File

SOURCE=.\LevelSettingsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\LightAmbientForm.cpp
# End Source File
# Begin Source File

SOURCE=.\LightDefinition.cpp
# End Source File
# Begin Source File

SOURCE=.\LightNode.cpp
# End Source File
# Begin Source File

SOURCE=.\LightSolveOptionsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\LightSolveProgressDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\lightsolvesavesystem.cpp
# End Source File
# Begin Source File

SOURCE=.\LODSettingsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MainDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MemLogDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MissingTranslationReportDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\mixfiledatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\ModelUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\MouseMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\Mover.cpp
# End Source File
# Begin Source File

SOURCE=.\MusicPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\NewAssetPackageDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\NewHeightfieldDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Node.cpp
# End Source File
# Begin Source File

SOURCE=.\NodeIDStartDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\NodeInfoPage.cpp
# End Source File
# Begin Source File

SOURCE=.\NodeMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\NodeScriptsPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectNode.cpp
# End Source File
# Begin Source File

SOURCE=.\OptimizingVisDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputForm.cpp
# End Source File
# Begin Source File

SOURCE=.\OverlapPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ParameterCtrls.cpp
# End Source File
# Begin Source File

SOURCE=.\ParameterInheritanceDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PathfindSectorBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\PathfindStartDefinition.cpp
# End Source File
# Begin Source File

SOURCE=.\PathfindStartNode.cpp
# End Source File
# Begin Source File

SOURCE=.\PhysObjectEditDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PhysObjEditTab.cpp
# End Source File
# Begin Source File

SOURCE=.\Picker.cpp
# End Source File
# Begin Source File

SOURCE=.\PlaySoundDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PositionPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Preset.cpp
# End Source File
# Begin Source File

SOURCE=.\PresetDependencyTab.cpp
# End Source File
# Begin Source File

SOURCE=.\PresetDialogueTab.cpp
# End Source File
# Begin Source File

SOURCE=.\PresetExport.cpp
# End Source File
# Begin Source File

SOURCE=.\PresetGeneralTab.cpp
# End Source File
# Begin Source File

SOURCE=.\PresetListDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PresetLogger.cpp
# End Source File
# Begin Source File

SOURCE=.\PresetMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\PresetPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\PresetPropSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\PresetRemapDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PresetSettingsTab.cpp
# End Source File
# Begin Source File

SOURCE=.\PresetsLibForm.cpp
# End Source File
# Begin Source File

SOURCE=.\PresetTransitionTab.cpp
# End Source File
# Begin Source File

SOURCE=.\PresetZoneTab.cpp
# End Source File
# Begin Source File

SOURCE=.\ProfileSection.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressUI.cpp
# End Source File
# Begin Source File

SOURCE=.\rcstringextractor.cpp
# End Source File
# Begin Source File

SOURCE=.\reportmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\SceneEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptEditDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectionBox.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectPresetDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SkyPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundNode.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundSettingsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\SpawnerNode.cpp
# End Source File
# Begin Source File

SOURCE=.\SpawnPointNode.cpp
# End Source File
# Begin Source File

SOURCE=.\SpecSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\SplashScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StringLibraryDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StringPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\StringPickerDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StringPickerMainDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StringsCategoryNameDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StringsCategoryViewDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\stringsmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\SunlightDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\TerrainDefinition.cpp
# End Source File
# Begin Source File

SOURCE=.\TerrainLODPage.cpp
# End Source File
# Begin Source File

SOURCE=.\TerrainNode.cpp
# End Source File
# Begin Source File

SOURCE=.\TerrainSectionPersist.cpp
# End Source File
# Begin Source File

SOURCE=.\test.cpp
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\TGAToDXT.cpp
# End Source File
# Begin Source File

SOURCE=.\TileDefinition.cpp
# End Source File
# Begin Source File

SOURCE=.\TileNode.cpp
# End Source File
# Begin Source File

SOURCE=.\TransitionEditDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\TransitionNode.cpp
# End Source File
# Begin Source File

SOURCE=.\TranslationExportDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\UIThread.cpp
# End Source File
# Begin Source File

SOURCE=.\UndoMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\UniqueList.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateAssetsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdatePresetDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdatingDBDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Utils.cpp
# End Source File
# Begin Source File

SOURCE=.\ValueListDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Vector3Dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\VisErrorReportDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\VisLog.cpp
# End Source File
# Begin Source File

SOURCE=.\VisMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\VisPointDefinition.cpp
# End Source File
# Begin Source File

SOURCE=.\VisPointGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\VisPointNode.cpp
# End Source File
# Begin Source File

SOURCE=.\VisSectorSampler.cpp
# End Source File
# Begin Source File

SOURCE=.\VisStatsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualOptionsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\VisWindowDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\VSS.IDL
# ADD BASE MTL /h "./vss.h"
# SUBTRACT BASE MTL /nologo /mktyplib203
# ADD MTL /h "./vss.h"
# SUBTRACT MTL /nologo /mktyplib203
# End Source File
# Begin Source File

SOURCE=.\vss_i.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\VSSClass.cpp
# End Source File
# Begin Source File

SOURCE=.\WaypathDefinition.cpp
# End Source File
# Begin Source File

SOURCE=.\WaypathInfoPage.cpp
# End Source File
# Begin Source File

SOURCE=.\WaypathNode.cpp
# End Source File
# Begin Source File

SOURCE=.\WaypointNode.cpp
# End Source File
# Begin Source File

SOURCE=.\WeatherPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\WelcomeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoneEditDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoneInfoPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoneNode.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\_assetmgr.h
# End Source File
# Begin Source File

SOURCE=.\_wwaudio.h
# End Source File
# Begin Source File

SOURCE=.\assetdatabase.h
# End Source File
# Begin Source File

SOURCE=.\assetpackagemgr.h
# End Source File
# Begin Source File

SOURCE=.\AttenuationSphere.h
# End Source File
# Begin Source File

SOURCE=.\Box3D.h
# End Source File
# Begin Source File

SOURCE=.\buildingchildnode.h
# End Source File
# Begin Source File

SOURCE=.\BuildingNode.h
# End Source File
# Begin Source File

SOURCE=.\CameraMgr.h
# End Source File
# Begin Source File

SOURCE=.\camerasettingsform.h
# End Source File
# Begin Source File

SOURCE=.\CheckingOutDialog.h
# End Source File
# Begin Source File

SOURCE=.\CheckinStyleDialog.h
# End Source File
# Begin Source File

SOURCE=.\ChooseModPackageDialog.h
# End Source File
# Begin Source File

SOURCE=.\CollisionGroups.h
# End Source File
# Begin Source File

SOURCE=.\ColorBar.h
# End Source File
# Begin Source File

SOURCE=.\ColorPicker.h
# End Source File
# Begin Source File

SOURCE=.\ColorPickerDialogClass.h
# End Source File
# Begin Source File

SOURCE=.\ColorUtils.h
# End Source File
# Begin Source File

SOURCE=.\ConversationEditorMgr.h
# End Source File
# Begin Source File

SOURCE=.\ConversationPage.h
# End Source File
# Begin Source File

SOURCE=.\ConversationPickerDialog.h
# End Source File
# Begin Source File

SOURCE=.\CoverAttackPointNode.h
# End Source File
# Begin Source File

SOURCE=.\CoverSpotDefinition.h
# End Source File
# Begin Source File

SOURCE=.\CoverSpotInfoPage.h
# End Source File
# Begin Source File

SOURCE=.\CoverSpotNode.h
# End Source File
# Begin Source File

SOURCE=.\DamageZoneNode.h
# End Source File
# Begin Source File

SOURCE=.\DefinitionParameter.h
# End Source File
# Begin Source File

SOURCE=.\DefinitionUtils.h
# End Source File
# Begin Source File

SOURCE=.\DeviceSelectionDialog.h
# End Source File
# Begin Source File

SOURCE=.\DialogToolbar.h
# End Source File
# Begin Source File

SOURCE=.\DockableForm.h
# End Source File
# Begin Source File

SOURCE=.\DummyObject.h
# End Source File
# Begin Source File

SOURCE=.\DummyObjectDefinition.h
# End Source File
# Begin Source File

SOURCE=.\DummyObjectNode.h
# End Source File
# Begin Source File

SOURCE=.\editableheightfield.h
# End Source File
# Begin Source File

SOURCE=.\EditConversationDialog.h
# End Source File
# Begin Source File

SOURCE=.\EditConversationListDialog.h
# End Source File
# Begin Source File

SOURCE=.\EditConversationRemarkDialog.h
# End Source File
# Begin Source File

SOURCE=.\EditDialogueDialog.h
# End Source File
# Begin Source File

SOURCE=.\EditFilenameListDialog.h
# End Source File
# Begin Source File

SOURCE=.\EditorAssetMgr.h
# End Source File
# Begin Source File

SOURCE=.\editorbuild.h
# End Source File
# Begin Source File

SOURCE=.\EditorChunkIDs.h
# End Source File
# Begin Source File

SOURCE=.\EditorINI.h
# End Source File
# Begin Source File

SOURCE=.\EditorLine.h
# End Source File
# Begin Source File

SOURCE=.\editormixfile.h
# End Source File
# Begin Source File

SOURCE=.\editoronlydefinition.h
# End Source File
# Begin Source File

SOURCE=.\editoronlyobjectnode.h
# End Source File
# Begin Source File

SOURCE=.\EditorPhys.h
# End Source File
# Begin Source File

SOURCE=.\EditorPropSheet.h
# End Source File
# Begin Source File

SOURCE=.\EditorSaveLoad.h
# End Source File
# Begin Source File

SOURCE=.\EditRemarkDialog.h
# End Source File
# Begin Source File

SOURCE=.\EditScript.h
# End Source File
# Begin Source File

SOURCE=.\EditStringDialog.h
# End Source File
# Begin Source File

SOURCE=.\excel.h
# End Source File
# Begin Source File

SOURCE=.\excel8.h
# End Source File
# Begin Source File

SOURCE=.\Export.h
# End Source File
# Begin Source File

SOURCE=.\ExportPresetsDialog.h
# End Source File
# Begin Source File

SOURCE=.\FileLocations.h
# End Source File
# Begin Source File

SOURCE=.\FileMgr.h
# End Source File
# Begin Source File

SOURCE=.\FilePicker.h
# End Source File
# Begin Source File

SOURCE=.\FormToolbar.h
# End Source File
# Begin Source File

SOURCE=.\GenerateBaseDialog.h
# End Source File
# Begin Source File

SOURCE=.\GenerateVisDialog.h
# End Source File
# Begin Source File

SOURCE=.\GeneratingEdgeSampledVisDialog.h
# End Source File
# Begin Source File

SOURCE=.\GeneratingLightVisDialog.h
# End Source File
# Begin Source File

SOURCE=.\GeneratingManualVisDialog.h
# End Source File
# Begin Source File

SOURCE=.\GeneratingPathfindDialog.h
# End Source File
# Begin Source File

SOURCE=.\GeneratingVisDialog.h
# End Source File
# Begin Source File

SOURCE=.\GenericTextDialog.h
# End Source File
# Begin Source File

SOURCE=.\GotoGroupDialog.h
# End Source File
# Begin Source File

SOURCE=.\GotoLocationDialog.h
# End Source File
# Begin Source File

SOURCE=.\GotoObjectByIDDialog.h
# End Source File
# Begin Source File

SOURCE=.\GotoObjectDialog.h
# End Source File
# Begin Source File

SOURCE=.\GrabHandles.h
# End Source File
# Begin Source File

SOURCE=.\Grid3D.h
# End Source File
# Begin Source File

SOURCE=.\GroupMgr.h
# End Source File
# Begin Source File

SOURCE=.\heightfieldeditor.h
# End Source File
# Begin Source File

SOURCE=.\HeightfieldMaterialSettingsDialog.h
# End Source File
# Begin Source File

SOURCE=.\heightfieldmgr.h
# End Source File
# Begin Source File

SOURCE=.\heightfieldpage.h
# End Source File
# Begin Source File

SOURCE=.\HistogramCtl.h
# End Source File
# Begin Source File

SOURCE=.\HitTestInfo.h
# End Source File
# Begin Source File

SOURCE=.\Icons.h
# End Source File
# Begin Source File

SOURCE=.\ImportTranslationDialog.h
# End Source File
# Begin Source File

SOURCE=.\IncludeFilesDialog.h
# End Source File
# Begin Source File

SOURCE=.\INISections.h
# End Source File
# Begin Source File

SOURCE=.\InstancesPage.h
# End Source File
# Begin Source File

SOURCE=.\LevelEdit.h
# End Source File
# Begin Source File

SOURCE=.\LevelEditDoc.h
# End Source File
# Begin Source File

SOURCE=.\LevelEditView.h
# End Source File
# Begin Source File

SOURCE=.\LevelFeature.h
# End Source File
# Begin Source File

SOURCE=.\LevelSettingsDialog.h
# End Source File
# Begin Source File

SOURCE=.\LightAmbientForm.h
# End Source File
# Begin Source File

SOURCE=.\LightDefinition.h
# End Source File
# Begin Source File

SOURCE=.\LightNode.h
# End Source File
# Begin Source File

SOURCE=.\LightSolveOptionsDialog.h
# End Source File
# Begin Source File

SOURCE=.\LightSolveProgressDialog.h
# End Source File
# Begin Source File

SOURCE=.\lightsolvesavesystem.h
# End Source File
# Begin Source File

SOURCE=.\ListTypes.h
# End Source File
# Begin Source File

SOURCE=.\LODSettingsDialog.h
# End Source File
# Begin Source File

SOURCE=.\MainDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MemLogDialog.h
# End Source File
# Begin Source File

SOURCE=.\MissingTranslationReportDialog.h
# End Source File
# Begin Source File

SOURCE=.\mixfiledatabase.h
# End Source File
# Begin Source File

SOURCE=.\ModelUtils.h
# End Source File
# Begin Source File

SOURCE=.\MouseMgr.h
# End Source File
# Begin Source File

SOURCE=.\Mover.h
# End Source File
# Begin Source File

SOURCE=.\MusicPropPage.h
# End Source File
# Begin Source File

SOURCE=.\NewAssetPackageDialog.h
# End Source File
# Begin Source File

SOURCE=.\NewHeightfieldDialog.h
# End Source File
# Begin Source File

SOURCE=.\Node.h
# End Source File
# Begin Source File

SOURCE=.\NodeCategories.h
# End Source File
# Begin Source File

SOURCE=.\NodeFunction.h
# End Source File
# Begin Source File

SOURCE=.\NodeIDStartDialog.h
# End Source File
# Begin Source File

SOURCE=.\NodeInfoPage.h
# End Source File
# Begin Source File

SOURCE=.\NodeMgr.H
# End Source File
# Begin Source File

SOURCE=.\NodeScriptsPropPage.h
# End Source File
# Begin Source File

SOURCE=.\nodetemplate.h
# End Source File
# Begin Source File

SOURCE=.\NodeTypes.h
# End Source File
# Begin Source File

SOURCE=.\ObjectNode.h
# End Source File
# Begin Source File

SOURCE=.\OptimizingVisDialog.h
# End Source File
# Begin Source File

SOURCE=.\OutputForm.h
# End Source File
# Begin Source File

SOURCE=.\OverlapPage.h
# End Source File
# Begin Source File

SOURCE=.\ParameterCtrls.h
# End Source File
# Begin Source File

SOURCE=.\ParameterInheritanceDialog.h
# End Source File
# Begin Source File

SOURCE=.\PathfindSectorBuilder.h
# End Source File
# Begin Source File

SOURCE=.\PathfindStartDefinition.h
# End Source File
# Begin Source File

SOURCE=.\PathfindStartNode.h
# End Source File
# Begin Source File

SOURCE=.\PhysObjectEditDialog.h
# End Source File
# Begin Source File

SOURCE=.\PhysObjEditTab.h
# End Source File
# Begin Source File

SOURCE=.\Picker.h
# End Source File
# Begin Source File

SOURCE=.\PlaySoundDialog.h
# End Source File
# Begin Source File

SOURCE=.\PositionPage.h
# End Source File
# Begin Source File

SOURCE=.\Preset.h
# End Source File
# Begin Source File

SOURCE=.\PresetDependencyTab.h
# End Source File
# Begin Source File

SOURCE=.\PresetDialogueTab.h
# End Source File
# Begin Source File

SOURCE=.\PresetExport.h
# End Source File
# Begin Source File

SOURCE=.\PresetGeneralTab.h
# End Source File
# Begin Source File

SOURCE=.\PresetListDialog.h
# End Source File
# Begin Source File

SOURCE=.\PresetLogger.h
# End Source File
# Begin Source File

SOURCE=.\PresetMgr.h
# End Source File
# Begin Source File

SOURCE=.\PresetPicker.h
# End Source File
# Begin Source File

SOURCE=.\PresetPropSheet.h
# End Source File
# Begin Source File

SOURCE=.\PresetRemapDialog.h
# End Source File
# Begin Source File

SOURCE=.\PresetSettingsTab.h
# End Source File
# Begin Source File

SOURCE=.\PresetsLibForm.h
# End Source File
# Begin Source File

SOURCE=.\PresetTransitionTab.h
# End Source File
# Begin Source File

SOURCE=.\PresetZoneTab.h
# End Source File
# Begin Source File

SOURCE=.\ProfileSection.h
# End Source File
# Begin Source File

SOURCE=.\ProgressUI.h
# End Source File
# Begin Source File

SOURCE=.\rcstringextractor.h
# End Source File
# Begin Source File

SOURCE=.\RegKeys.h
# End Source File
# Begin Source File

SOURCE=.\reportmgr.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SceneEditor.h
# End Source File
# Begin Source File

SOURCE=.\ScriptEditDialog.h
# End Source File
# Begin Source File

SOURCE=.\ScriptMgr.h
# End Source File
# Begin Source File

SOURCE=.\SelectionBox.h
# End Source File
# Begin Source File

SOURCE=.\SelectPresetDialog.h
# End Source File
# Begin Source File

SOURCE=.\SkyPropPage.h
# End Source File
# Begin Source File

SOURCE=.\SoundNode.h
# End Source File
# Begin Source File

SOURCE=.\SoundSettingsPage.h
# End Source File
# Begin Source File

SOURCE=.\SpawnerNode.h
# End Source File
# Begin Source File

SOURCE=.\SpawnPointNode.h
# End Source File
# Begin Source File

SOURCE=.\SpecSheet.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\SplashScreen.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StringLibraryDialog.h
# End Source File
# Begin Source File

SOURCE=.\StringPicker.h
# End Source File
# Begin Source File

SOURCE=.\StringPickerDialog.h
# End Source File
# Begin Source File

SOURCE=.\StringPickerMainDialog.h
# End Source File
# Begin Source File

SOURCE=.\StringsCategoryNameDialog.h
# End Source File
# Begin Source File

SOURCE=.\StringsCategoryViewDialog.h
# End Source File
# Begin Source File

SOURCE=.\stringsmgr.h
# End Source File
# Begin Source File

SOURCE=.\SunlightDialog.h
# End Source File
# Begin Source File

SOURCE=.\TerrainDefinition.h
# End Source File
# Begin Source File

SOURCE=.\TerrainLODPage.h
# End Source File
# Begin Source File

SOURCE=.\TerrainNode.h
# End Source File
# Begin Source File

SOURCE=.\TerrainSectionPersist.h
# End Source File
# Begin Source File

SOURCE=.\TGAToDXT.h
# End Source File
# Begin Source File

SOURCE=.\TileDefinition.h
# End Source File
# Begin Source File

SOURCE=.\TileNode.h
# End Source File
# Begin Source File

SOURCE=.\TransitionEditDialog.h
# End Source File
# Begin Source File

SOURCE=.\TransitionNode.h
# End Source File
# Begin Source File

SOURCE=.\TranslationExportDialog.h
# End Source File
# Begin Source File

SOURCE=.\UIThread.h
# End Source File
# Begin Source File

SOURCE=.\UndoMgr.h
# End Source File
# Begin Source File

SOURCE=.\UniqueList.h
# End Source File
# Begin Source File

SOURCE=.\UpdateAssetsDialog.h
# End Source File
# Begin Source File

SOURCE=.\UpdatePresetDialog.h
# End Source File
# Begin Source File

SOURCE=.\UpdatingDBDialog.h
# End Source File
# Begin Source File

SOURCE=.\Utils.h
# End Source File
# Begin Source File

SOURCE=.\ValueListDialog.h
# End Source File
# Begin Source File

SOURCE=.\Vector3Dialog.h
# End Source File
# Begin Source File

SOURCE=.\VisErrorReportDialog.h
# End Source File
# Begin Source File

SOURCE=.\VisGenProgress.h
# End Source File
# Begin Source File

SOURCE=.\VisLog.h
# End Source File
# Begin Source File

SOURCE=.\VisMgr.h
# End Source File
# Begin Source File

SOURCE=.\VisPointDefinition.h
# End Source File
# Begin Source File

SOURCE=.\VisPointGenerator.h
# End Source File
# Begin Source File

SOURCE=.\VisPointNode.h
# End Source File
# Begin Source File

SOURCE=.\VisSectorSampler.h
# End Source File
# Begin Source File

SOURCE=.\VisStatsDialog.h
# End Source File
# Begin Source File

SOURCE=.\VisualOptionsDialog.h
# End Source File
# Begin Source File

SOURCE=.\VisWindowDialog.h
# End Source File
# Begin Source File

SOURCE=.\vss.h
# End Source File
# Begin Source File

SOURCE=.\VSSClass.h
# End Source File
# Begin Source File

SOURCE=.\WaypathDefinition.h
# End Source File
# Begin Source File

SOURCE=.\WaypathInfoPage.h
# End Source File
# Begin Source File

SOURCE=.\WaypathNode.h
# End Source File
# Begin Source File

SOURCE=.\WaypointLine.h
# End Source File
# Begin Source File

SOURCE=.\WaypointNode.h
# End Source File
# Begin Source File

SOURCE=.\WeatherPropPage.h
# End Source File
# Begin Source File

SOURCE=.\WelcomeDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\wwlib\wwstring.h
# End Source File
# Begin Source File

SOURCE=.\ZoneEditDialog.h
# End Source File
# Begin Source File

SOURCE=.\ZoneInfoPage.h
# End Source File
# Begin Source File

SOURCE=.\ZoneNode.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ani_tool.bmp
# End Source File
# Begin Source File

SOURCE=.\arrowcop.cur
# End Source File
# Begin Source File

SOURCE=.\res\axis1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\axis2.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bottom_t.bmp
# End Source File
# Begin Source File

SOURCE=.\res\check1.ico
# End Source File
# Begin Source File

SOURCE=.\res\checkbox.bmp
# End Source File
# Begin Source File

SOURCE=.\res\conversa.bmp
# End Source File
# Begin Source File

SOURCE=.\res\convert1.ico
# End Source File
# Begin Source File

SOURCE=.\res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\Filecopy.avi
# End Source File
# Begin Source File

SOURCE=.\res\folder1.ico
# End Source File
# Begin Source File

SOURCE=.\res\folder_t.ico
# End Source File
# Begin Source File

SOURCE=.\res\hand_poi.cur
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00008.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00009.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00010.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00011.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00012.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00013.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00014.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00015.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00016.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00017.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00018.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00019.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00020.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00021.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00022.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00023.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00024.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00025.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00026.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00027.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00069.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico3dfil.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\idi_.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\instance.bmp
# End Source File
# Begin Source File

SOURCE=.\keyframe.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LevelEdit.ico
# End Source File
# Begin Source File

SOURCE=.\res\LevelEdit.rc2
# End Source File
# Begin Source File

SOURCE=.\res\LevelEditDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\link.cur
# End Source File
# Begin Source File

SOURCE=.\res\ltarrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ltarrowd.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\marker.bmp
# End Source File
# Begin Source File

SOURCE=.\res\openfold.ico
# End Source File
# Begin Source File

SOURCE=.\res\orator2.ico
# End Source File
# Begin Source File

SOURCE=.\res\orator3.ico
# End Source File
# Begin Source File

SOURCE=.\res\orator4.ico
# End Source File
# Begin Source File

SOURCE=.\res\orator5.ico
# End Source File
# Begin Source File

SOURCE=.\res\orator6.ico
# End Source File
# Begin Source File

SOURCE=.\res\orator7.ico
# End Source File
# Begin Source File

SOURCE=.\res\pathfind.ico
# End Source File
# Begin Source File

SOURCE=.\res\PhysTest.ico
# End Source File
# Begin Source File

SOURCE=.\res\pointer_.cur
# End Source File
# Begin Source File

SOURCE=.\res\preset_t.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pri_high.ico
# End Source File
# Begin Source File

SOURCE=.\res\pri_low.ico
# End Source File
# Begin Source File

SOURCE=.\res\pri_low1.ico
# End Source File
# Begin Source File

SOURCE=.\res\rtarrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rtarrowd.bmp
# End Source File
# Begin Source File

SOURCE=.\res\script.ico
# End Source File
# Begin Source File

SOURCE=.\res\sound.ico
# End Source File
# Begin Source File

SOURCE=.\res\splash.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sunlight.ico
# End Source File
# Begin Source File

SOURCE=.\res\terrain.ico
# End Source File
# Begin Source File

SOURCE=.\res\tile.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\transiti.ico
# End Source File
# Begin Source File

SOURCE=.\res\vol_low1.ico
# End Source File
# Begin Source File

SOURCE=.\res\vss.ico
# End Source File
# Begin Source File

SOURCE=.\res\vss_user.ico
# End Source File
# Begin Source File

SOURCE=.\res\WayMid.W3d
# End Source File
# Begin Source File

SOURCE=.\res\waypath.ico
# End Source File
# Begin Source File

SOURCE=.\res\WayStart.w3d
# End Source File
# Begin Source File

SOURCE=.\res\WayStop.w3d
# End Source File
# Begin Source File

SOURCE=.\res\welcome.bmp
# End Source File
# Begin Source File

SOURCE=.\res\zone.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\bodybox.w3d
# End Source File
# Begin Source File

SOURCE=.\res\buildingicon.w3d
# End Source File
# Begin Source File

SOURCE=.\res\Camera.w3d
# End Source File
# Begin Source File

SOURCE=.\res\carmarker.w3d
# End Source File
# Begin Source File

SOURCE=.\res\coverspot.w3d
# End Source File
# Begin Source File

SOURCE=.\res\dummy.w3d
# End Source File
# Begin Source File

SOURCE=.\res\grid.w3d
# End Source File
# Begin Source File

SOURCE=.\LevelEdit.reg
# End Source File
# Begin Source File

SOURCE=.\res\Light.w3d
# End Source File
# Begin Source File

SOURCE=.\res\Meter.tga
# End Source File
# Begin Source File

SOURCE=.\res\PointLight.w3d
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\Speaker.w3d
# End Source File
# Begin Source File

SOURCE=.\res\Speaker2.w3d
# End Source File
# Begin Source File

SOURCE=.\res\ta_cement.tga
# End Source File
# Begin Source File

SOURCE=.\res\ta_dummy.tga
# End Source File
# Begin Source File

SOURCE=.\res\ta_front.tga
# End Source File
# Begin Source File

SOURCE=.\res\transbox.w3d
# End Source File
# Begin Source File

SOURCE=.\res\way_b.w3d
# End Source File
# Begin Source File

SOURCE=.\res\way_g.w3d
# End Source File
# Begin Source File

SOURCE=.\res\way_r.w3d
# End Source File
# End Target
# End Project
