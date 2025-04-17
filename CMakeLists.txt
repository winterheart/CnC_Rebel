cmake_minimum_required(VERSION 3.20)

project(CnC_Rebel VERSION 1.037.2)
set(REBEL_CODENAME "TECHNICIAN")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(REBEL_ENABLE_DEBUG_MESSAGES "Enable debug messages (WWDEBUG)" ON)
option(REBEL_ENABLE_EDITOR "Enable editor building" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(dxsdk-d3dx CONFIG REQUIRED)
find_package(MSS REQUIRED)
find_package(BINK REQUIRED)
if(REBEL_ENABLE_EDITOR)
    find_package(NVDXTLIB REQUIRED)
endif()
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Globally set Mt(d) since whole project depends on it
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_compile_definitions(
    "$<$<BOOL:${REBEL_ENABLE_DEBUG_MESSAGES}>:WWDEBUG>"
    "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:_CRT_SECURE_NO_WARNINGS;_CRT_NONSTDC_NO_DEPRECATE;WINVER=0x0601;WIN32;_WINDOWS>"
)

add_compile_options(
    "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/Gy;/GF;/W4;/Zc:inline;/Zc:wchar_t>"
)

add_subdirectory(Code)
