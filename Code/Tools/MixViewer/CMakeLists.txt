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

set(CMAKE_MFC_FLAG 1)

add_executable(MixViewer WIN32 ${SOURCES} MixViewer.rc)
target_link_libraries(MixViewer
    PRIVATE
        WWDebug
        WWLib
)
