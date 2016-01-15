cmake_minimum_required(VERSION 3.2)
project(sunshine_raytracer)

#CreateSourceFolders adds function create_vs_folders()
include(cmake/CreateSourceFolders.cmake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(src)
