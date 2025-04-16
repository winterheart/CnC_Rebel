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
target_link_libraries(WWDebug PRIVATE
    winmm   # timeGetTime()
)

if(REBEL_ENABLE_EDITOR)
    add_library(WWDebugE STATIC ${SOURCES})
    target_include_directories(WWDebugE PUBLIC
        $<BUILD_INTERFACE:
            ${PROJECT_SOURCE_DIR}/Code/wwdebug
        >
        PRIVATE
            ${PROJECT_SOURCE_DIR}/Code/wwlib
    )
    target_link_libraries(WWDebugE PRIVATE
        winmm   # timeGetTime()
    )
    target_compile_definitions(WWDebugE
        PRIVATE
            PARAM_EDITING_ON
    )
endif()
