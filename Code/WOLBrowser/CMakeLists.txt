set(SOURCES
    WOLBrowser_i.c
)

add_library(WOLBrowser STATIC ${SOURCES})
target_include_directories(WOLBrowser PUBLIC
    $<BUILD_INTERFACE:
        ${PROJECT_SOURCE_DIR}/Code/WOLBrowser
    >
)
