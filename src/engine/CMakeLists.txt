project (ssrt_engine VERSION 0.1.0)

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
        scene.h
        scene.cpp
        scenegraph.h
        scenegraph.cpp
        rng.h
        rng.cpp)
           
add_library(${PROJECT_NAME} ${SOURCES})
add_library(ssrt::engine ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC  ${GLM_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/..)

create_vs_folders()
