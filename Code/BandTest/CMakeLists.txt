set(SOURCES
    BandTest.cpp
    BandTest.rc
)

add_library(BandTest SHARED ${SOURCES})
target_compile_definitions(BandTest PRIVATE
    _MBCS
    _USRDLL
    BANDTEST_EXPORTS
)
target_link_libraries(BandTest PRIVATE
    odbc32
    odbccp32
    ws2_32
    winmm
)
set_target_properties(BandTest PROPERTIES
        OUTPUT_NAME_DEBUG "BandTestD"
        OUTPUT_NAME_RELWITHDEBINFO "BandTestP"
)