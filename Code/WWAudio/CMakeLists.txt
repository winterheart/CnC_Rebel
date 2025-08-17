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
    ListenerHandle.cpp
    Sound2DHandle.cpp
    Sound3DHandle.cpp
    SoundHandle.cpp
    SoundStreamHandle.cpp
)

add_library(WWAudio STATIC ${SOURCES})
target_include_directories(WWAudio PUBLIC
    $<BUILD_INTERFACE:
        ${PROJECT_SOURCE_DIR}/Code/WWAudio
    >
    PRIVATE
        ${PROJECT_SOURCE_DIR}/Code/WW3D2
)
target_link_libraries(WWAudio
    PRIVATE
        WWDebug
        WWLib
        WWMath
        WWSaveLoad
        winmm   # timeGetTime()
    PUBLIC
        milesstub
)
target_compile_definitions(WWAudio PRIVATE
    WINDOWS_IGNORE_PACKING_MISMATCH
    _MBCS
)

if(REBEL_ENABLE_EDITOR)
    add_library(WWAudioE STATIC ${SOURCES})
    target_include_directories(WWAudioE PUBLIC
        $<BUILD_INTERFACE:
            ${PROJECT_SOURCE_DIR}/Code/WWAudio
        >
        PRIVATE
            ${PROJECT_SOURCE_DIR}/Code/WW3D2
            ${MSS_INCLUDE_DIRS}
    )
    target_link_libraries(WWAudioE
        PRIVATE
            WWDebugE
            WWLib
            WWMath
            WWSaveLoadE
            winmm   # timeGetTime()
        PUBLIC
            milesstub
    )
    target_compile_definitions(WWAudioE PRIVATE
        WINDOWS_IGNORE_PACKING_MISMATCH
        _MBCS
        PARAM_EDITING_ON
    )
endif()
