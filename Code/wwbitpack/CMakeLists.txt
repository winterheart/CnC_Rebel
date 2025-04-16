set(SOURCES
    BitPacker.cpp
    bitstream.cpp
    encoderlist.cpp
    encodertypeentry.cpp
)

add_library(WWBitPack STATIC ${SOURCES})
target_include_directories(WWBitPack PUBLIC
    $<BUILD_INTERFACE:
        ${PROJECT_SOURCE_DIR}/Code/wwbitpack
    >
)
target_link_libraries(WWBitPack PRIVATE
        WWDebug
        WWLib
        WWUtil
    INTERFACE
        WWUtil
)
