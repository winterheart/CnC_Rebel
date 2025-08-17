set(SOURCES
    BINKMovie.cpp
    subtitle.cpp
    subtitlemanager.cpp
    subtitleparser.cpp
)

add_library(BinkMovie STATIC ${SOURCES})
target_include_directories(BinkMovie PUBLIC
    $<BUILD_INTERFACE:
        ${PROJECT_SOURCE_DIR}/Code/BinkMovie
    >
)
target_link_libraries(BinkMovie
    PRIVATE
        WW3D2
        WWDebug
        WWLib
        Microsoft::D3DX9
    PUBLIC
        binkstub
)
