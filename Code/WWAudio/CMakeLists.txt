set(SOURCES
    AudibleSound.cpp
    AudioEvents.cpp
    AudioSaveLoad.cpp
    FilteredSound.cpp
    Listener.cpp
    LogicalListener.cpp
    LogicalSound.cpp
    Sound3D.cpp
    SoundBuffer.cpp
    SoundPseudo3D.cpp
    SoundScene.cpp
    SoundSceneObj.cpp
    Threads.cpp
    Utils.cpp
    WWAudio.cpp
    listenerhandle.cpp
    sound2dhandle.cpp
    sound3dhandle.cpp
    soundhandle.cpp
    soundstreamhandle.cpp
)

add_library(WWAudio STATIC ${SOURCES})
target_include_directories(WWAudio PUBLIC
    $<BUILD_INTERFACE:
        ${PROJECT_SOURCE_DIR}/Code/WWAudio
    >
    PRIVATE
        ${PROJECT_SOURCE_DIR}/Code/ww3d2
        ${MSS_INCLUDE_DIRS}
)
target_link_libraries(WWAudio PUBLIC
    WWDebug
    WWLib
    WWMath
    WWSaveLoad
    ${MSS_LIBRARIES}
    winmm   # timeGetTime()
)
target_compile_definitions(WWAudio PRIVATE
    WINDOWS_IGNORE_PACKING_MISMATCH
)
target_compile_definitions(WWAudio PRIVATE
    _MBCS
)
