/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__6D711A27_651E_11D2_9FC8_00104B791122__INCLUDED_)
#define AFX_MAINFRM_H__6D711A27_651E_11D2_9FC8_00104B791122__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "formtoolbar.h"
#include "maindialogbar.h"
#include "vector.h"
#include "wwstring.h"

//////////////////////////////////////////////////////////////////////////////////////////
// Forward declarations
//////////////////////////////////////////////////////////////////////////////////////////
class Vector3;
class CLevelEditDoc;

//////////////////////////////////////////////////////////////////////////////////////////
//
//	CMainFrame
//
//////////////////////////////////////////////////////////////////////////////////////////
class CMainFrame : public CFrameWnd {
protected: // create from serialization only
  CMainFrame();
  DECLARE_DYNCREATE(CMainFrame)

  // Attributes
public:
  // Operations
public:
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CMainFrame)
public:
  virtual BOOL PreCreateWindow(CREATESTRUCT &cs);
  virtual void OnFinalRelease();

protected:
  virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext);
  virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  //}}AFX_VIRTUAL

  // Implementation
public:
  virtual ~CMainFrame();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext &dc) const;
#endif

protected: // control bar embedded members
  CStatusBar m_wndStatusBar;
  CToolBar m_wndToolBar;

  // Generated message map functions
protected:
  //{{AFX_MSG(CMainFrame)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnClose();
  afx_msg void OnObjectManipulate();
  afx_msg void OnUpdateObjectManipulate(CCmdUI *pCmdUI);
  afx_msg void OnModeCamera();
  afx_msg void OnUpdateModeCamera(CCmdUI *pCmdUI);
  afx_msg void OnDeleteSelection();
  afx_msg void OnModeOrbit();
  afx_msg void OnUpdateModeOrbit(CCmdUI *pCmdUI);
  afx_msg void OnCoordWorld();
  afx_msg void OnUpdateCoordWorld(CCmdUI *pCmdUI);
  afx_msg void OnCoordView();
  afx_msg void OnUpdateCoordView(CCmdUI *pCmdUI);
  afx_msg void OnCoordObject();
  afx_msg void OnUpdateCoordObject(CCmdUI *pCmdUI);
  afx_msg void OnRestrictX();
  afx_msg void OnRestrictY();
  afx_msg void OnRestrictZ();
  afx_msg void OnUpdateRestrictZ(CCmdUI *pCmdUI);
  afx_msg void OnUpdateRestrictY(CCmdUI *pCmdUI);
  afx_msg void OnUpdateRestrictX(CCmdUI *pCmdUI);
  afx_msg void OnCameraFront();
  afx_msg void OnCameraBack();
  afx_msg void OnCameraLeft();
  afx_msg void OnCameraRight();
  afx_msg void OnCameraTop();
  afx_msg void OnCameraBottom();
  afx_msg void OnDropToGround();
  afx_msg void OnUpdateDropToGround(CCmdUI *pCmdUI);
  afx_msg void OnModeWalkthrough();
  afx_msg void OnUpdateModeWalkthrough(CCmdUI *pCmdUI);
  afx_msg void OnViewChangeDevice();
  afx_msg void OnLevelExport();
  afx_msg void OnViewFullscreen();
  afx_msg void OnUpdateViewFullscreen(CCmdUI *pCmdUI);
  afx_msg void OnViewAmbientLightDlg();
  afx_msg void OnUpdateViewAmbientLightDlg(CCmdUI *pCmdUI);
  afx_msg void OnUpdateViewToolbarCameraSettings(CCmdUI *pCmdUI);
  afx_msg void OnViewToolbarCameraSettings();
  afx_msg void OnCameraDepthLess();
  afx_msg void OnCameraDepthMore();
  afx_msg void OnSavePresets();
  afx_msg void OnUpdateSavePresets(CCmdUI *pCmdUI);
  afx_msg void OnToggleSnappoints();
  afx_msg void OnUpdateToggleSnappoints(CCmdUI *pCmdUI);
  afx_msg void OnAlwaysExport();
  afx_msg void OnDestroy();
  afx_msg void OnChangeBase();
  afx_msg void OnCamSpeedIncrease();
  afx_msg void OnCamSpeedDecrease();
  afx_msg void OnCamReset();
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnGenVis();
  afx_msg void OnToggleVisWindow();
  afx_msg void OnAniBackFrame();
  afx_msg void OnAniFirstFrame();
  afx_msg void OnAniFwdFrame();
  afx_msg void OnAniLastFrame();
  afx_msg void OnAniPause();
  afx_msg void OnAniPlay();
  afx_msg void OnAniStop();
  afx_msg void OnEditUndo();
  afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
  afx_msg void OnEditCopy();
  afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
  afx_msg void OnEditCut();
  afx_msg void OnUpdateEditCut(CCmdUI *pCmdUI);
  afx_msg void OnEditPaste();
  afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
  afx_msg void OnCreateGroup();
  afx_msg void OnUpdateCreateGroup(CCmdUI *pCmdUI);
  afx_msg void OnToggleLights();
  afx_msg void OnUpdateToggleLights(CCmdUI *pCmdUI);
  afx_msg void OnRepartition();
  afx_msg void OnAllowAutoUpdates();
  afx_msg void OnUpdateAllowAutoUpdates(CCmdUI *pCmdUI);
  afx_msg void OnRotateLeft();
  afx_msg void OnRotateRight();
  afx_msg void OnCalcAllLights();
  afx_msg void OnCalcSelLights();
  afx_msg void OnUpdateCalcSelLights(CCmdUI *pCmdUI);
  afx_msg void OnLockObjects();
  afx_msg void OnUnlockObjects();
  afx_msg void OnUpdateLockObjects(CCmdUI *pCmdUI);
  afx_msg void OnUpdateUnlockObjects(CCmdUI *pCmdUI);
  afx_msg void OnEditIncludes();
  afx_msg void OnVolDec();
  afx_msg void OnVolInc();
  afx_msg void OnBackgroundSettings();
  afx_msg void OnToggleMusic();
  afx_msg void OnUpdateToggleMusic(CCmdUI *pCmdUI);
  afx_msg void OnToggleSounds();
  afx_msg void OnUpdateToggleSounds(CCmdUI *pCmdUI);
  afx_msg void OnViewAggregateChildren();
  afx_msg void OnUpdateViewAggregateChildren(CCmdUI *pCmdUI);
  afx_msg void OnToggleSunlight();
  afx_msg void OnUpdateToggleSunlight(CCmdUI *pCmdUI);
  afx_msg void OnEditSunlight();
  afx_msg void OnAutoGenVis();
  afx_msg void OnVisualOptions();
  afx_msg void OnVisInvert();
  afx_msg void OnViewVisPoints();
  afx_msg void OnUpdateViewVisPoints(CCmdUI *pCmdUI);
  afx_msg void OnSpecifyAssetDatabase();
  afx_msg void OnUpdateVisInvert(CCmdUI *pCmdUI);
  afx_msg void OnToggleBackfaces();
  afx_msg void OnUpdateToggleBackfaces(CCmdUI *pCmdUI);
  afx_msg void OnToggleWireframeMode();
  afx_msg void OnUpdateToggleWireframeMode(CCmdUI *pCmdUI);
  afx_msg void OnViewVisErrors();
  afx_msg void OnUseVisCamera();
  afx_msg void OnUpdateUseVisCamera(CCmdUI *pCmdUI);
  afx_msg void OnGenerateObstacleVolumes();
  afx_msg void OnVisDisable();
  afx_msg void OnUpdateVisDisable(CCmdUI *pCmdUI);
  afx_msg void OnDisplayPaths();
  afx_msg void OnUpdateDisplayPaths(CCmdUI *pCmdUI);
  afx_msg void OnTestPathfind();
  afx_msg void OnDisplayPathfindSectors();
  afx_msg void OnUpdateDisplayPathfindSectors(CCmdUI *pCmdUI);
  afx_msg void OnDisplayPathfindPortals();
  afx_msg void OnUpdateDisplayPathfindPortals(CCmdUI *pCmdUI);
  afx_msg void OnDisplayPathfindRawData();
  afx_msg void OnUpdateDisplayPathfindRawData(CCmdUI *pCmdUI);
  afx_msg void OnExportPathfind();
  afx_msg void OnImportPathfind();
  afx_msg void OnImportVis();
  afx_msg void OnExportVis();
  afx_msg void OnViewVisWindow();
  afx_msg void OnUpdateViewVisWindow(CCmdUI *pCmdUI);
  afx_msg void OnToggleManVisPoints();
  afx_msg void OnUpdateToggleManVisPoints(CCmdUI *pCmdUI);
  afx_msg void OnDiscardPathfind();
  afx_msg void OnDoDebug1();
  afx_msg void OnDoDebug2();
  afx_msg void OnImportDynObjs();
  afx_msg void OnExportDynObjs();
  afx_msg void OnTestGoto();
  afx_msg void OnImportStatic();
  afx_msg void OnExportStatic();
  afx_msg void OnDisplayWeb();
  afx_msg void OnUpdateDisplayWeb(CCmdUI *pCmdUI);
  afx_msg void OnUpdateDisplayFullPaths(CCmdUI *pCmdUI);
  afx_msg void OnDisplayFullPaths();
  afx_msg void OnEscape();
  afx_msg void OnDisplayVisGrid();
  afx_msg void OnUpdateDisplayVisGrid(CCmdUI *pCmdUI);
  afx_msg void OnDisplayVisSectors();
  afx_msg void OnUpdateDisplayVisSectors(CCmdUI *pCmdUI);
  afx_msg void OnPrelitMultipass();
  afx_msg void OnUpdatePrelitMultipass(CCmdUI *pCmdUI);
  afx_msg void OnPrelitMultitex();
  afx_msg void OnUpdatePrelitMultitex(CCmdUI *pCmdUI);
  afx_msg void OnPrelitVertex();
  afx_msg void OnUpdatePrelitVertex(CCmdUI *pCmdUI);
  afx_msg void OnDebugScriptsMode();
  afx_msg void OnUpdateDebugScriptsMode(CCmdUI *pCmdUI);
  afx_msg void OnImportLights();
  afx_msg void OnViewSoundSpheres();
  afx_msg void OnUpdateViewSoundSpheres(CCmdUI *pCmdUI);
  afx_msg void OnViewLightSpheres();
  afx_msg void OnUpdateViewLightSpheres(CCmdUI *pCmdUI);
  afx_msg void OnImportSunlight();
  afx_msg void OnDiscardVis();
  afx_msg void OnIncreaseSphere();
  afx_msg void OnUpdateIncreaseSphere(CCmdUI *pCmdUI);
  afx_msg void OnDecreaseSphere();
  afx_msg void OnUpdateDecreaseSphere(CCmdUI *pCmdUI);
  afx_msg void OnRunJob();
  afx_msg void OnGotoLocation();
  afx_msg void OnExportThumbnails();
  afx_msg void OnVisStats();
  afx_msg void OnSetNodeIdStart();
  afx_msg void OnBuildDynaCullsys();
  afx_msg void OnImportVisRemapData();
  afx_msg void OnExportVisRemapData();
  afx_msg void OnUpdateBulkReplace(CCmdUI *pCmdUI);
  afx_msg void OnBulkReplace();
  afx_msg void OnCheckIds();
  afx_msg void OnExportLights();
  afx_msg void OnOptimizeVisData();
  afx_msg void OnDisplayVisGridLittleBoxes();
  afx_msg void OnUpdateDisplayVisGridLittleBoxes(CCmdUI *pCmdUI);
  afx_msg void OnEditStringsTable();
  afx_msg void OnExportStringIds();
  afx_msg void OnImportStringIds();
  afx_msg void OnBuildFlightInfo();
  afx_msg void OnToggleAttenuationSpheres();
  afx_msg void OnUpdateToggleAttenuationSpheres(CCmdUI *pCmdUI);
  afx_msg void OnFixIdCollisions();
  afx_msg void OnResetDynaCullSystem();
  afx_msg void OnDisplayLightVectors();
  afx_msg void OnUpdateDisplayLightVectors(CCmdUI *pCmdUI);
  afx_msg void OnDisplayStaticAnimObjects();
  afx_msg void OnUpdateDisplayStaticAnimObjects(CCmdUI *pCmdUI);
  afx_msg void OnEditConversations();
  afx_msg void OnBuildingPowerOn();
  afx_msg void OnUpdateBuildingPowerOn(CCmdUI *pCmdUI);
  afx_msg void OnCreateProxies();
  afx_msg void OnUpdateCreateProxies(CCmdUI *pCmdUI);
  afx_msg void OnCheckInPresetChanges();
  afx_msg void OnUpdateCheckInPresetChanges(CCmdUI *pCmdUI);
  afx_msg void OnImmediatePresetCheckin();
  afx_msg void OnUpdateImmediatePresetCheckin(CCmdUI *pCmdUI);
  afx_msg void OnRemapIds();
  afx_msg void OnUpdateRemapIds(CCmdUI *pCmdUI);
  afx_msg void OnVerifyCulling();
  afx_msg void OnEnableVisSectorFallback();
  afx_msg void OnUpdateEnableVisSectorFallback(CCmdUI *pCmdUI);
  afx_msg void OnRunManualVisPoints();
  afx_msg void OnShowEditorObjects();
  afx_msg void OnUpdateShowEditorObjects(CCmdUI *pCmdUI);
  afx_msg void OnAddChildNode();
  afx_msg void OnUpdateAddChildNode(CCmdUI *pCmdUI);
  afx_msg void OnCheckMemlog();
  afx_msg void OnMakeVisPoint();
  afx_msg void OnExportStringTable();
  afx_msg void OnGotoObject();
  afx_msg void OnExportPresets();
  afx_msg void OnImportPresets();
  afx_msg void OnBatchExport();
  afx_msg void OnLockVisSamplePoint();
  afx_msg void OnUpdateLockVisSamplePoint(CCmdUI *pCmdUI);
  afx_msg void OnToggleTerrainSelection();
  afx_msg void OnUpdateToggleTerrainSelection(CCmdUI *pCmdUI);
  afx_msg void OnExportPresetFileDependencies();
  afx_msg void OnImportStrings();
  afx_msg void OnExportTileList();
  afx_msg void OnRemapUnimportantIds();
  afx_msg void OnEditLevelSettings();
  afx_msg void OnExportTranslationData();
  afx_msg void OnImportTranslationData();
  afx_msg void OnCompressTextures();
  afx_msg void OnUpdateCompressTextures(CCmdUI *pCmdUI);
  afx_msg void OnExportFileUsageReport();
  afx_msg void OnExportMissingTranslationReport();
  afx_msg void OnExportLanguage();
  afx_msg void OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu);
  afx_msg void OnAlwaysLocalExport();
  afx_msg void OnExportInstallerLanguageVersion();
  afx_msg void OnExtractInstallerRcStrings();
  afx_msg void OnExtractRcStrings();
  afx_msg void OnCameraPerspective();
  afx_msg void OnCameraOrthographic();
  afx_msg void OnUpdateCameraOrthographic(CCmdUI *pCmdUI);
  afx_msg void OnUpdateCameraPerspective(CCmdUI *pCmdUI);
  afx_msg void OnModExport();
  afx_msg void OnSaveLevel();
  afx_msg void OnComputeVertexSolve();
  afx_msg void OnModeHeightEdit();
  afx_msg void OnUpdateModeHeightEdit(CCmdUI *pCmdUI);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

public:
  /////////////////////////////////////////////////////////////////////////
  //	Public methods
  /////////////////////////////////////////////////////////////////////////
  FormToolbarClass &Get_Output_Toolbar(void) { return m_OutputToolbar; }
  FormToolbarClass &Get_Camera_Toolbar(void) { return m_CameraSettingsToolbar; }
  FormToolbarClass &Get_Ambient_Light_Toolbar(void) { return m_AmbientLightToolbar; }
  MainDialogBarClass &Get_Main_Dialog_Bar(void) { return m_TestBar; }
  CLevelEditDoc *Get_Current_Document(void) { return m_pCurrentDoc; }
  void Show_Ani_Toolbar(bool bshow);
  void Update_Ani_Frame(int frame, int max_frames);
  void Update_Poly_Count(void);
  void Update_Texture_Mem(void);
  void Update_Camera_Location(const Vector3 &position);
  CImageList *Get_Image_List(void) { return &m_ImageList; }
  void Expand_Attenuation_Spheres(float amount);
  void Toggle_Static_Anims(void) { OnDisplayStaticAnimObjects(); }

protected:
  /////////////////////////////////////////////////////////////////////////
  //	Protected methods
  /////////////////////////////////////////////////////////////////////////
  void Create_Toolbars(void);
  void Adjust_Growth_Rate(void);
  void Restore_Window_State(void);
  void Configure_File_Factories(void);
  void Create_Camera_Menu(void);

private:
  /////////////////////////////////////////////////////////////////////////
  //	Private member data
  /////////////////////////////////////////////////////////////////////////
  FormToolbarClass m_OutputToolbar;
  FormToolbarClass m_AmbientLightToolbar;
  FormToolbarClass m_CameraSettingsToolbar;
  CToolBar m_wndBottomToolBar;
  CToolBar m_AniToolbar;
  CReBar m_DialogBar;
  CLevelEditDoc *m_pCurrentDoc;
  CImageList m_ImageList;
  MainDialogBarClass m_TestBar;
  DWORD m_UpdateTimer;
  float m_GrowthRate;
  int m_MaxCamProfiles;
  DynamicVectorClass<StringClass> m_CameraProfiles;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__6D711A27_651E_11D2_9FC8_00104B791122__INCLUDED_)
