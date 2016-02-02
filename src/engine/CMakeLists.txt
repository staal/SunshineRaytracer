##########################################
# Engine project
# Set version of engine here, is imported
# into the library.
##########################################
project (ssrt_engine VERSION 0.1.1)
message(STATUS "Creating library ${PROJECT_NAME}")


##########################################
# Find Boost
# Use boost for command line arguments
# Default to use static linking to Boost
##########################################
set(Boost_NO_BOOST_CMAKE ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS filesystem system)


##########################################
# Find GLM
##########################################
find_package(glm REQUIRED)


##########################################
# Configure a header file to pass some of 
# the CMake settings to the source code
##########################################
configure_file (
  "engineversion.h.in"
  "${PROJECT_BINARY_DIR}/engineversion.h"
  )
  

##########################################
# Source files for current project
##########################################
set(PROJECT_SOURCES
        image/tgafile.h
        image/tgafile.cpp
        geometry/obj/mtlgrammar.hpp
        geometry/obj/objgrammar.hpp
        geometry/obj/objdata.h
        geometry/obj/objdata.cpp
        geometry/obj/mtldata.h
        geometry/obj/mtldata.cpp
        geometry/obj/mtlfile.h
        geometry/obj/mtlfile.cpp
        geometry/objfile.h
        geometry/objfile.cpp
        geometry/boundingbox.h
        geometry/boundingbox.cpp
        geometry/surface.h
        geometry/surface.cpp
        geometry/material.h
        geometry/material.cpp
        geometry/triangle.h
        geometry/triangle.cpp
        scene/bvh.h
        scene/bvh.cpp
        scene/camera.h
        scene/camera.cpp
        scene/lightsource.h
        scene/lightsource.cpp
        image.h
        image.cpp
        pathtracer.h
        pathtracer.cpp
        ray.h
        scene.h
        scene.cpp
        scenegraph.h
        scenegraph.cpp
        rng.h
        rng.cpp)
           

##########################################
# Set up library linking, includes and
# the target itself
##########################################
#Adding engineversion.h here to avoid it getting indexed through create_vs_folders
add_library(${PROJECT_NAME} ${PROJECT_SOURCES} "${PROJECT_BINARY_DIR}/engineversion.h")
add_library(ssrt::engine ALIAS ${PROJECT_NAME})

#Include directory "${CMAKE_CURRENT_SOURCE_DIR}/.." is so headers are located at
#"engine/foo.h" instead of simply "foo.h"
target_include_directories(${PROJECT_NAME} 
    PUBLIC  ${GLM_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/..
    PRIVATE ${Boost_INCLUDE_DIRS}
    PRIVATE ${PROJECT_BINARY_DIR} #So version header can be located
    )    

target_link_libraries(${PROJECT_NAME} 
    PRIVATE ${Boost_LIBRARIES}
    )


##########################################
# Create folders for Visual studio project
##########################################
create_vs_folders("${PROJECT_SOURCES}")