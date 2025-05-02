set(SOURCES
    AVAssetSuck.cpp
    duplicatecombiner.cpp
    MainFrm.cpp
    MakeMixFileDialog.cpp
    MixCombiningDialog.cpp
    MixPatchMaker.cpp
    MixViewer.cpp
    MixViewerDoc.cpp
    MixViewerView.cpp
    StdAfx.cpp
)

add_executable(MixViewer WIN32 ${SOURCES} MixViewer.rc)
target_link_libraries(MixViewer
    PRIVATE
        WWDebug
        WWLib
)

set_target_properties(MixViewer PROPERTIES
    MFC_FLAG 1
)
