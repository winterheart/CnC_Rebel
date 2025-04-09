set(SOURCES
    stringtwiddler.cpp
    tdbcategory.cpp
    translatedb.cpp
    translateobj.cpp
)

add_library(WWTranslateDb STATIC ${SOURCES})
target_include_directories(WWTranslateDb PUBLIC
    $<BUILD_INTERFACE:
        ${PROJECT_SOURCE_DIR}/Code/wwtranslatedb
    >
)
target_link_libraries(WWTranslateDb PUBLIC
    WWDebug
    WWLib
    WWMath
    WWSaveLoad
)
target_compile_definitions(WWTranslateDb PRIVATE
    _MBCS
)
