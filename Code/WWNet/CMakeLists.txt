set(SOURCES
    BWBalance.cpp
    connect.cpp
    #lan.cpp
    msgstat.cpp
    msgstatlist.cpp
    msgstatlistgroup.cpp
    netstats.cpp
    netutil.cpp
    networkobject.cpp
    networkobjectfactory.cpp
    networkobjectfactorymgr.cpp
    networkobjectmgr.cpp
    packetmgr.cpp
    rhost.cpp
    singlepl.cpp
    wwpacket.cpp
)

add_library(WWNet STATIC ${SOURCES})
target_include_directories(WWNet PUBLIC
    $<BUILD_INTERFACE:
        ${PROJECT_SOURCE_DIR}/Code/WWNet
    >
    PRIVATE
        ${PROJECT_SOURCE_DIR}/Code          # Requires commando/nat.h
)
target_link_libraries(WWNet
    PRIVATE
        WWBitPack
        WWDebug
        WWLib
        WWMath
        WWSaveLoad
        WWUtil
    INTERFACE
        WWBitPack
)
# FIXME: Blast from the past: unresolved bug from 2002
# With /Ob2 on Release Renegade.exe produces 0xc0000005 exception on exit
target_compile_options(WWNet PRIVATE "$<$<CONFIG:Release>:/Ob1>")
