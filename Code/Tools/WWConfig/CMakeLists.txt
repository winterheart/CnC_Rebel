set(SOURCES
    AudioConfigDialog.cpp
    DriverVersionWarning.cpp
    EZGIMEX.cpp
    locale.cpp
    Locale_API.cpp
    PerformanceConfigDialog.cpp
    StdAfx.cpp
    VideoConfigDialog.cpp
    WWConfig.cpp
    WWConfigDlg.cpp
    ../../wwlib/ramfile.cpp
)

set(CMAKE_MFC_FLAG 1)
add_executable(WWConfig WIN32 ${SOURCES} WWConfig.rc)
target_include_directories(WWConfig PRIVATE
    ${MSS_INCLUDE_DIRS}
)
target_link_libraries(WWConfig PRIVATE
    Microsoft::D3DX9
    WW3D2
    WWAudio
    WWDebug
    WWLib
    WWPhys
)
target_compile_definitions(WWConfig PRIVATE
    _MBCS
)
set_target_properties(WWConfig PROPERTIES
    OUTPUT_NAME_DEBUG "WWConfigD"
    OUTPUT_NAME_RELWITHDEBINFO "WWConfigP"
)
