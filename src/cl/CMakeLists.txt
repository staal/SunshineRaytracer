##########################################
# Command line project
##########################################
project (ssrt_cl)
message(STATUS "Creating application ${PROJECT_NAME}")


##########################################
# Find Boost
# Use boost for command line arguments
# Default to use static linking to Boost
##########################################
set(Boost_NO_BOOST_CMAKE ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS program_options filesystem system )


##########################################
# Source files for current project
##########################################  
set(PROJECT_SOURCES
        renderapplication.h
        renderapplication.cpp
        commandlinehandler.h
        commandlinehandler.cpp
        )


##########################################
# Set up library linking, includes and
# the target itself
##########################################
add_library(${PROJECT_NAME}_lib STATIC ${PROJECT_SOURCES})
add_library(ssrt::cl::lib ALIAS ${PROJECT_NAME}_lib)

target_include_directories(${PROJECT_NAME}_lib 
    PUBLIC ${Boost_INCLUDE_DIRS}
    )
    
target_link_libraries(${PROJECT_NAME}_lib
    PUBLIC ssrt::engine
    PRIVATE ${Boost_LIBRARIES}
    )


##########################################
# Create the main application itself
##########################################
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ssrt::cl::lib
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


##########################################
# Tests
##########################################
add_subdirectory(test)