##########################################
# Sunshine Raytracer Project
##########################################
cmake_minimum_required(VERSION 3.2)
project(sunshine_raytracer VERSION 0.1.2)


##########################################
#CreateSourceFolders adds function create_vs_folders()
##########################################
include(cmake/CreateSourceFolders.cmake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


##########################################
#Compiler flags
##########################################
if(MSVC)
	#Set /MP which is multithreaded build
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
else(MSVC)
    #Enforce c++14 on non msvc compilers
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()


##########################################
# Projects are located in src
##########################################
add_subdirectory(src)


##########################################
# Doxygen
# Add a target to generate API documentation with Doxygen
##########################################
find_package(Doxygen)
if(DOXYGEN_FOUND)
    message(STATUS "Doxygen found: ${DOXYGEN_DOT_FOUND}")   
    
    #Warn about not having doxygen dot for creating UML
    if(NOT DOXYGEN_DOT_FOUND) 
        message(WARNING "Doxygen dot found: ${DOXYGEN_DOT_FOUND}. Set "
        "DOXYGEN_DOT_EXECUTABLE to locate it")    
    else(NOT DOXYGEN_DOT_FOUND)
        message(STATUS "Doxygen dot found: ${DOXYGEN_DOT_FOUND}")    
    endif(NOT DOXYGEN_DOT_FOUND)
    
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/documentation/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doxygen_documentation
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
else(DOXYGEN_FOUND)
    message(STATUS "Doxygen not found, documentation target will not be "
    "created. Set DOXYGEN_EXECUTABLE to locate it.")    
endif(DOXYGEN_FOUND)