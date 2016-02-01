project (ssrt_engine VERSION 0.1.1)
message(STATUS "Creating library ${PROJECT_NAME}")

#Use boost for command line arguments
#Default to use static linking to Boost
set(Boost_NO_BOOST_CMAKE ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS filesystem system)
  
 
# configure a header file to pass some of the CMake settings to the source code
configure_file (
  "engineversion.h.in"
  "${PROJECT_BINARY_DIR}/engineversion.h"
  )
  
#Source files for current project
set(PROJECT_SOURCES
        image/tgafile.h
        image/tgafile.cpp
        geometry/obj/mtlgrammar.hpp
        geometry/obj/objgrammar.hpp
        geometry/obj/objdata.h
        geometry/obj/objdata.cpp
        geometry/obj/objfile.h
        geometry/obj/objfile.cpp
        geometry/obj/mtlfile.h
        geometry/obj/mtlfile.cpp
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
        rayutil.h
        scene.h
        scene.cpp
        scenegraph.h
        scenegraph.cpp
        rng.h
        rng.cpp)
           

#Adding clconfig.h here to avoid it getting indexed through create_vs_folders
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

create_vs_folders("${PROJECT_SOURCES}")
