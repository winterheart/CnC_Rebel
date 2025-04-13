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
        ${PROJECT_SOURCE_DIR}/Code/wwsaveload
    >
)
target_link_libraries(WWSaveLoad PRIVATE
    WWDebug
    WWLib
    WWMath
    winmm   # timeGetTime()
)

if(REBEL_ENABLE_EDITOR)
    add_library(WWSaveLoadEditor STATIC ${SOURCES})
    target_include_directories(WWSaveLoadEditor PUBLIC
        $<BUILD_INTERFACE:
            ${PROJECT_SOURCE_DIR}/Code/wwsaveload
        >
    )
    target_link_libraries(WWSaveLoadEditor PUBLIC
        WWDebug
        WWLib
        WWMath
    )
    target_compile_definitions(WWSaveLoadEditor PRIVATE PARAM_EDITING_ON)
endif()
