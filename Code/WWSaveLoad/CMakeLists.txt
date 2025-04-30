set(SOURCES
    definition.cpp
    definitionfactory.cpp
    definitionfactorymgr.cpp
    definitionmgr.cpp
    parameter.cpp
    persistfactory.cpp
    pointerremap.cpp
    saveload.cpp
    saveloadstatus.cpp
    saveloadsubsystem.cpp
    twiddler.cpp
    wwsaveload.cpp
)

add_library(WWSaveLoad STATIC ${SOURCES})
target_include_directories(WWSaveLoad PUBLIC
    $<BUILD_INTERFACE:
        ${PROJECT_SOURCE_DIR}/Code/WWSaveLoad
    >
)
target_link_libraries(WWSaveLoad PRIVATE
    WWDebug
    WWLib
    WWMath
    winmm   # timeGetTime()
)

if(REBEL_ENABLE_EDITOR)
    add_library(WWSaveLoadE STATIC ${SOURCES})
    target_include_directories(WWSaveLoadE PUBLIC
        $<BUILD_INTERFACE:
            ${PROJECT_SOURCE_DIR}/Code/WWSaveLoad
        >
    )
    target_link_libraries(WWSaveLoadE PUBLIC
        WWDebugE
        WWLib
        WWMath
    )
    target_compile_definitions(WWSaveLoadE
        PRIVATE
            PARAM_EDITING_ON
    )
endif()
