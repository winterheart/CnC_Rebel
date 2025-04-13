set(SOURCES
    mathutil.cpp
    miscutil.cpp
    stackdump.cpp
)

add_library(WWUtil STATIC ${SOURCES})
target_include_directories(WWUtil PUBLIC
    $<BUILD_INTERFACE:
        ${PROJECT_SOURCE_DIR}/Code/wwutil
    >
)
target_link_libraries(WWUtil
    PRIVATE
        WWDebug
        WWLib
        WWMath
)
target_compile_definitions(WWUtil PRIVATE
    _MBCS
)
