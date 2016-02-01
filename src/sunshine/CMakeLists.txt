##########################################
# Main Sunshine application
# Set version of engine here, is imported
# into the application.
##########################################
project (sunshine VERSION 0.0.1)
message(STATUS "Creating application ${PROJECT_NAME}")


##########################################
# Windows handling
##########################################
if(WIN32)
    set (BUILD_WITH_WIN32 FALSE CACHE BOOL "Build with win32 flag or not")
    
    if(BUILD_WITH_WIN32)
        set(USEWIN32 WIN32)
    endif(BUILD_WITH_WIN32)
endif(WIN32)

##########################################
# Find Qt
##########################################
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)


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
        ${USEWIN32}
        main.cpp)



##########################################
# Set up library linking, includes and
# the target itself
##########################################
#Adding sunshineversion.h here to avoid it getting indexed through create_vs_folders
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} "${PROJECT_BINARY_DIR}/sunshineversion.h")


target_link_libraries(${PROJECT_NAME} 
    PRIVATE Qt5::Widgets
    )
    
##########################################
# Create folders for Visual studio project
##########################################
create_vs_folders("${PROJECT_SOURCES}")