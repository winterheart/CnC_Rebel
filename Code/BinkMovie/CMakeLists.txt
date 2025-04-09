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
    PRIVATE
        ${BINK_INCLUDE_DIRS}
        ${DirectX_INCLUDE_DIR}
)
target_link_libraries(BinkMovie PUBLIC
    WW3D2
    WWDebug
    WWLib
    ${BINK_LIBRARIES}
    ${DirectX_D3DX9_LIBRARY}
)
