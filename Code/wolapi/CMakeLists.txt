set(SOURCES
    WOLAPI_i.c
)

add_library(WOLAPI STATIC ${SOURCES})
target_include_directories(WOLAPI PUBLIC
    $<BUILD_INTERFACE:
        ${PROJECT_SOURCE_DIR}/Code/wolapi
    >
)
#target_link_libraries(WOLAPI PUBLIC
#        WWDebug
#        WWLib
#)
