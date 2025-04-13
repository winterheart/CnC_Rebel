set(SOURCES
    # Common.cpp
    DLLmain.cpp
    DPrint.cpp
    DrMobius.cpp
    #Group.cpp
    #GroupControl.cpp
    #GroupScript.cpp
    Mission00.cpp
    Mission01.cpp
    Mission02.cpp
    Mission03.cpp
    Mission04.cpp
    Mission05.cpp
    Mission06.cpp
    Mission07.cpp
    Mission09.cpp
    Mission10.cpp
    Mission11.cpp
    MissionDemo.cpp
    #MissionS04.cpp
    MissionX0.cpp
    #PRDemo.cpp
    ScriptFactory.cpp
    ScriptRegistrar.cpp
    Test_BMG.cpp
    Test_Cinematic.cpp
    Test_DAK.cpp
    Test_DAY.cpp
    Test_DEL.cpp
    Test_DLS.cpp
    #Test_DLS_M03.cpp
    Test_DME.cpp
    Test_GTH.cpp
    Test_JDG_EVA.cpp
    Test_PDS.cpp
    Test_RAD.cpp
    Test_RMV.cpp
    Test_RMV_Toolkit.cpp
    Toolkit.cpp
    Toolkit_Actions.cpp
    Toolkit_Animations.cpp
    Toolkit_Broadcaster.cpp
    Toolkit_Explosions.cpp
    Toolkit_Objectives.cpp
    Toolkit_Objects.cpp
    Toolkit_Powerup.cpp
    Toolkit_Siege.cpp
    Toolkit_Sounds.cpp
    Toolkit_Spawners.cpp
    Toolkit_Triggers.cpp
    mission08.cpp
    scripts.cpp
    strtrim.cpp
    #unitcombat.cpp
)

add_library(Scripts SHARED ${SOURCES})
target_include_directories(Scripts PUBLIC
    $<BUILD_INTERFACE:
        ${PROJECT_SOURCE_DIR}/Code/Scripts
    >
    PRIVATE
        ${PROJECT_SOURCE_DIR}/Code/Combat
)
target_link_libraries(Scripts PRIVATE
    WWDebug
    WWLib
)
target_compile_definitions(Scripts PRIVATE
    BUILDING_DLL
)
set_target_properties(Scripts PROPERTIES
    OUTPUT_NAME_DEBUG "ScriptsD"
)
