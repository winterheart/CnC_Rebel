add_subdirectory(WWConfig)
if(REBEL_ENABLE_EDITOR)
    add_subdirectory(LevelEdit)
endif()

if(REBEL_ENABLE_TOOLS)
    add_subdirectory(MixViewer)
    add_subdirectory(W3DView)
endif()
