cmake_minimum_required(VERSION 3.0)

include(cmake/CreateSourceFolders.cmake)
##########
# Find GLM
##########
find_package(GLM REQUIRED)

if(NOT GLM_FOUND)
    message(Error "GLM not found")
endif(NOT GLM_FOUND)

add_subdirectory(src)
