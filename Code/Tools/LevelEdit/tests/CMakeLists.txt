set(CMAKE_MFC_FLAG 0)

add_executable(tgatodxt_tests
    tgatodxt_tests.cpp
    ../TGAToDXT.cpp
)
target_link_libraries(tgatodxt_tests
    PRIVATE
        GTest::gtest_main
        WWDebug
        WWLib
        crnlib
        stb
)
target_include_directories(tgatodxt_tests
    PRIVATE
        ..
)
gtest_discover_tests(tgatodxt_tests
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Code/Tools/LevelEdit/tests
)
