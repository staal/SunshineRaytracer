project (SPTracer)

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
message("${PROJECT_NAME}")
target_include_directories(SPTracer PUBLIC  ${GLM_INCLUDE_DIRS})

create_vs_folders()
