project (ssrt_engine VERSION 0.1.1)

# configure a header file to pass some of the CMake settings to the source code
configure_file (
  "engineversion.h.in"
  "${PROJECT_BINARY_DIR}/engineversion.h"
  )
  
#Source files for current project
set(PROJECT_SOURCES
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
           
message(STATUS "Creating library ${PROJECT_NAME}")

#Adding clconfig.h here to avoid it getting indexed through create_vs_folders
add_library(${PROJECT_NAME} ${PROJECT_SOURCES} "${PROJECT_BINARY_DIR}/engineversion.h")
add_library(ssrt::engine ALIAS ${PROJECT_NAME})

#Include directory "${CMAKE_CURRENT_SOURCE_DIR}/.." is so headers are located at
#"engine/foo.h" instead of simply "foo.h"
target_include_directories(${PROJECT_NAME} 
    PUBLIC  ${GLM_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/..
    PRIVATE ${PROJECT_BINARY_DIR} #So version header can be located
    )

create_vs_folders("${PROJECT_SOURCES}")
