set(SOURCES
    wwdebug.cpp
    wwmemlog.cpp
    wwprofile.cpp
)

add_library(WWDebug STATIC ${SOURCES})
target_include_directories(WWDebug PUBLIC
    $<BUILD_INTERFACE:
        ${PROJECT_SOURCE_DIR}/Code/wwdebug
    >
    PRIVATE
        ${PROJECT_SOURCE_DIR}/Code/wwlib
)
target_link_libraries(WWDebug PUBLIC
    winmm   # timeGetTime()
)
