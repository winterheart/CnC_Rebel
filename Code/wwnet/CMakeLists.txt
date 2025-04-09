set(SOURCES
    BWBalance.cpp
    connect.cpp
    lan.cpp
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
        ${PROJECT_SOURCE_DIR}/Code/wwnet
    >
    PRIVATE
        ${PROJECT_SOURCE_DIR}/Code          # Requires commando/nat.h
        ${PROJECT_SOURCE_DIR}/Code/wolapi
)
target_link_libraries(WWNet PUBLIC
    WWBitPack
    WWDebug
    WWLib
    WWMath
    WWSaveLoad
    WWUtil
)
