set(SOURCES
    servercontrol.cpp
    servercontrolsocket.cpp
)

add_library(SControl STATIC ${SOURCES})
target_include_directories(SControl PUBLIC
    $<BUILD_INTERFACE:
        ${PROJECT_SOURCE_DIR}/Code/SControl
    >
)
target_link_libraries(SControl PRIVATE
    WWDebug
    WWLib
)
target_compile_definitions(SControl PRIVATE
    _MBCS
)
