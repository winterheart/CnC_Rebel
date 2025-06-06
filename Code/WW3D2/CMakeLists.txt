set(SOURCES
    aabtree.cpp
    aabtreebuilder.cpp
    agg_def.cpp
    animatedsoundmgr.cpp
    animobj.cpp
    assetmgr.cpp
    assetstatus.cpp
    bitmaphandler.cpp
    bmp2d.cpp
    boxrobj.cpp
    bwrender.cpp
    camera.cpp
    collect.cpp
    coltest.cpp
    composite.cpp
    dazzle.cpp
    ddsfile.cpp
    decalmsh.cpp
    decalsys.cpp
    distlod.cpp
    dx8caps.cpp
    dx8fvf.cpp
    dx8indexbuffer.cpp
    dx8polygonrenderer.cpp
    dx8renderer.cpp
    dx8rendererdebugger.cpp
    dx8texman.cpp
    dx8vertexbuffer.cpp
    dx8wrapper.cpp
    dynamesh.cpp
    font3d.cpp
    formconv.cpp
    framgrab.cpp
    hanim.cpp
    hanimmgr.cpp
    hcanim.cpp
    hlod.cpp
    hmdldef.cpp
    hmorphanim.cpp
    hrawanim.cpp
    htree.cpp
    htreemgr.cpp
    intersec.cpp
    layer.cpp
    light.cpp
    lightenvironment.cpp
    line3d.cpp
    linegrp.cpp
    mapper.cpp
    matinfo.cpp
    matpass.cpp
    matrixmapper.cpp
    mesh.cpp
    meshbuild.cpp
    meshdam.cpp
    meshgeometry.cpp
    meshmatdesc.cpp
    meshmdl.cpp
    meshmdlio.cpp
    metalmap.cpp
    missingtexture.cpp
    motchan.cpp
    nullrobj.cpp
    part_buf.cpp
    part_emt.cpp
    part_ldr.cpp
    pivot.cpp
    pointgr.cpp
    polyinfo.cpp
    # pot.cpp
    predlod.cpp
    prim_anim.cpp
    projector.cpp
    proto.cpp
    render2d.cpp
    render2dsentence.cpp
    renderobjectrecycler.cpp
    rendobj.cpp
    rinfo.cpp
    ringobj.cpp
    scene.cpp
    segline.cpp
    seglinerenderer.cpp
    shader.cpp
    shattersystem.cpp
    snappts.cpp
    sortingrenderer.cpp
    soundrobj.cpp
    sphereobj.cpp
    statistics.cpp
    stripoptimizer.cpp
    surfaceclass.cpp
    texfcach.cpp
    texproject.cpp
    # textdraw.cpp
    texture.cpp
    textureloader.cpp
    texturethumbnail.cpp
    txt.cpp
    vertmaterial.cpp
    visrasterizer.cpp
    w3d_dep.cpp
    w3d_util.cpp
    ww3d.cpp
    ww3dformat.cpp
)

add_library(WW3D2 STATIC ${SOURCES})
target_include_directories(WW3D2 PUBLIC
    $<BUILD_INTERFACE:
        ${PROJECT_SOURCE_DIR}/Code/WW3D2
    >
    PRIVATE
        ${MSS_INCLUDE_DIRS}
)
target_link_libraries(WW3D2
    PRIVATE
        WWAudio
        WWDebug
        WWLib
        WWMath
        WWSaveLoad
        Microsoft::D3DX9
        ${MSS_LIBRARIES}
        Vfw32
    INTERFACE
        WWMath
)
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(WW3D2 PRIVATE "/arch:SSE2")
endif()

if(REBEL_ENABLE_EDITOR)
    add_library(WW3D2E STATIC ${SOURCES})
    target_include_directories(WW3D2E PUBLIC
        $<BUILD_INTERFACE:
            ${PROJECT_SOURCE_DIR}/Code/WW3D2
        >
        PRIVATE
            ${MSS_INCLUDE_DIRS}
    )
    target_link_libraries(WW3D2E
        PRIVATE
            WWAudioE
            WWDebugE
            WWLib
            WWMath
            WWSaveLoadE
            Microsoft::D3DX9
            ${MSS_LIBRARIES}
            Vfw32
        INTERFACE
            WWMath
    )
    target_compile_definitions(WW3D2E PRIVATE
        PARAM_EDITING_ON
    )
    if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        target_compile_options(WW3D2E PRIVATE "/arch:SSE2")
    endif()
endif()
