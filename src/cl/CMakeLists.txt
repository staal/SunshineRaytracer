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
        main.cpp)


##########################################
# Set up library linking, includes and
# the target itself
##########################################
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} 
    PRIVATE ${SSRT_ENGINE_INCLUDE_DIRS}
    PRIVATE ${Boost_INCLUDE_DIRS}
    )
    
target_link_libraries(${PROJECT_NAME} 
    PRIVATE ssrt::engine
    PRIVATE ${Boost_LIBRARIES}
    )


##########################################
# Create folders for Visual studio project
##########################################
create_vs_folders("${PROJECT_SOURCES}")