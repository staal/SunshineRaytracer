project (SPTracer)

include_directories(${GLM_INCLUDE_DIRS})
link_directories(${GLM_LIBRARY_DIRS})
add_definitions(${GLM_DEFINITIONS})

set(SOURCES
        io/tgafile.h
        io/tgafile.cpp
        io/objfile.h
        io/objfile.cpp
        scene/bvh.h
        scene/bvh.cpp
        scene/camera.h
        scene/camera.cpp
        scene/lightsource.h
        scene/lightsource.cpp
        scene/surface.h
        scene/surface.cpp
        scene/triangle.h
        scene/triangle.cpp
        image.h
        image.cpp
        pathtracer.h
        pathtracer.cpp
        rayutil.h
        renderapplication.h
        renderapplication.cpp
        scene.h
        scene.cpp
        scenegraph.h
        scenegraph.cpp
        rng.h
        rng.cpp
        main.cpp)
  

add_executable(SPTracer ${SOURCES})
create_vs_folders()