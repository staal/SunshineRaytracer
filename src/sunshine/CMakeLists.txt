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
        MainSceneWidget.h
        MainSceneWidget.cpp
        )

##########################################
# Set up library linking, includes and
# the target itself
##########################################
#Adding sunshineversion.h here to avoid it getting indexed through create_vs_folders
add_library(${PROJECT_NAME}_lib ${PROJECT_SOURCES} "${PROJECT_BINARY_DIR}/sunshineversion.h")
add_library(ssrt::sunshine::lib ALIAS ${PROJECT_NAME}_lib)

target_include_directories(${PROJECT_NAME}_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    )

target_link_libraries(${PROJECT_NAME}_lib
    PUBLIC Qt5::Widgets
    ) 
    

##########################################
# Create the main application itself
##########################################
add_executable(${PROJECT_NAME} ${USEWIN32} main.cpp)
      
target_link_libraries(${PROJECT_NAME}
    PRIVATE ssrt::sunshine::lib
    )
    

##########################################
# Compiler flags for application
##########################################
if(MSVC)
	#Set /MP which is multithreaded build
    target_compile_options(${PROJECT_NAME}
        PUBLIC /MP)
    target_compile_options(${PROJECT_NAME}_lib
        PUBLIC /MP)        
else(MSVC)
    #Enforce c++14 on non msvc compilers
    target_compile_options(${PROJECT_NAME}
        PUBLIC -std=c++14)
    target_compile_options(${PROJECT_NAME}_lib
        PUBLIC -std=c++14)        
endif()    

    
##########################################
# Create folders for Visual studio project
##########################################
create_vs_folders("${PROJECT_SOURCES}")