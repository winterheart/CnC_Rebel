set(SOURCES
    CNCModeSettings.cpp
    SoundEnvironment.cpp
    WeatherMgr.cpp
    action.cpp
    activeconversation.cpp
    airstripgameobj.cpp
    animcontrol.cpp
    armedgameobj.cpp
    assetdep.cpp
    assets.cpp
    backgroundmgr.cpp
    basecontroller.cpp
    basegameobj.cpp
    beacongameobj.cpp
    bones.cpp
    building.cpp
    buildingaggregate.cpp
    buildingmonitor.cpp
    buildingstate.cpp
    bullet.cpp
    c4.cpp
    ccamera.cpp
    characterclasssettings.cpp
    cheatmgr.cpp
    cinematicgameobj.cpp
    clientcontrol.cpp
    colors.cpp
    combat.cpp
    combatdazzle.cpp
    combatmaterialeffectmanager.cpp
    combatsaveload.cpp
    combatsound.cpp
    comcentergameobj.cpp
    control.cpp
    conversation.cpp
    conversationmgr.cpp
    conversationremark.cpp
    cover.cpp
    crandom.cpp
    csdamageevent.cpp
    damage.cpp
    damageablegameobj.cpp
    damageablestaticphys.cpp
    damagezone.cpp
    debug.cpp
    diaglog.cpp
    dialogue.cpp
    directinput.cpp
    doors.cpp
    dynamicspeechanim.cpp
    effectrecycler.cpp
    elevator.cpp
    encyclopediamgr.cpp
    evasettings.cpp
    explosion.cpp
    ffactorylist.cpp
    gameobjmanager.cpp
    gameobjobserver.cpp
    gametype.cpp
    globalsettings.cpp
    harvester.cpp
    hud.cpp
    hudinfo.cpp
    humanrecoil.cpp
    humanstate.cpp
    input.cpp
    inventory.cpp
    mapmgr.cpp
    mendozabossgameobj.cpp
    messagewindow.cpp
    muzzlerecoil.cpp
    objectives.cpp
    objectivesviewer.cpp
    objlibrary.cpp
    orator.cpp
    oratortypes.cpp
    pathaction.cpp
    persistentgameobjobserver.cpp
    physicalgameobj.cpp
    pilot.cpp
    playerdata.cpp
    playerterminal.cpp
    playertype.cpp
    powerplantgameobj.cpp
    powerup.cpp
    purchasesettings.cpp
    radar.cpp
    raveshawbossgameobj.cpp
    refinerygameobj.cpp
    reflist.cpp
    repairbaygameobj.cpp
    sakurabossgameobj.cpp
    samsite.cpp
    savegame.cpp
    scexplosionevent.cpp
    scobeliskevent.cpp
    screenfademanager.cpp
    scriptablegameobj.cpp
    scriptcommands.cpp
    scripts.cpp
    scriptzone.cpp
    simplegameobj.cpp
    smartgameobj.cpp
    sniper.cpp
    soldier.cpp
    soldierfactorygameobj.cpp
    soldierobserver.cpp
    spawn.cpp
    specialeffectsgameobj.cpp
    statemachine.cpp
    staticnetworkobject.cpp
    surfaceeffects.cpp
    systeminfolog.cpp
    teampurchasesettings.cpp
    textwindow.cpp
    timemgr.cpp
    transition.cpp
    transitiongameobj.cpp
    unitcoordinationzonemgr.cpp
    vehicle.cpp
    vehicledriver.cpp
    vehiclefactorygameobj.cpp
    viseme.cpp
    warfactorygameobj.cpp
    weaponbag.cpp
    weaponmanager.cpp
    weapons.cpp
    weaponview.cpp
)

add_library(Combat STATIC ${SOURCES})
target_include_directories(Combat PUBLIC
    $<BUILD_INTERFACE:
        ${PROJECT_SOURCE_DIR}/Code/Combat
    >
    PRIVATE
        ${MSS_INCLUDE_DIRS}
)
target_link_libraries(Combat
    PRIVATE
        WW3D2
        WWAudio
        WWDebug
        WWLib
        WWNet
        WWPhys
        WWSaveLoad
        WWTranslateDb
        WWUi
        Microsoft::D3DX9
        ${MSS_LIBRARIES}
    INTERFACE
        WWAudio
)
target_compile_definitions(Combat PRIVATE
    _MBCS
    WINDOWS_IGNORE_PACKING_MISMATCH
)

if(REBEL_ENABLE_EDITOR)
    add_library(CombatE STATIC ${SOURCES})
    target_include_directories(CombatE PUBLIC
        $<BUILD_INTERFACE:
            ${PROJECT_SOURCE_DIR}/Code/Combat
        >
        PRIVATE
            ${MSS_INCLUDE_DIRS}
    )
    target_link_libraries(CombatE
        PRIVATE
            WW3D2E
            WWAudioE
            WWDebugE
            WWLib
            WWNet
            WWPhysE
            WWSaveLoadE
            WWTranslateDb
            WWUi
            Microsoft::D3DX9
            ${MSS_LIBRARIES}
        INTERFACE
            WWAudioE
            WWNet
    )
    target_compile_definitions(CombatE PRIVATE
        _MBCS
        WINDOWS_IGNORE_PACKING_MISMATCH
        PARAM_EDITING_ON
    )
endif()
