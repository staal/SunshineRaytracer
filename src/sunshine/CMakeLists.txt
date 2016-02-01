##########################################
# Main Sunshine application
# Set version of engine here, is imported
# into the application.
##########################################
project (sunshine VERSION 0.0.1)
message(STATUS "Creating application ${PROJECT_NAME}")


##########################################
# Configure a header file to pass some of 
# the CMake settings to the source code
##########################################
configure_file (
  "sunshineversion.h.in"
  "${PROJECT_BINARY_DIR}/sunshineversion.h"
  )
  

##########################################
# Source files for current project
##########################################
set(PROJECT_SOURCES
        main.cpp)


##########################################
# Set up library linking, includes and
# the target itself
##########################################
#Adding sunshineversion.h here to avoid it getting indexed through create_vs_folders
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} "${PROJECT_BINARY_DIR}/sunshineversion.h")



##########################################
# Create folders for Visual studio project
##########################################
create_vs_folders("${PROJECT_SOURCES}")