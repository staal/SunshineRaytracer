##########################################
# Tests
##########################################
project (test_ssrt_engine)
message(STATUS "Creating ${PROJECT_NAME}")


##########################################
# Find Boost
# Use boost for command line arguments
# Default to use static linking to Boost
##########################################
set(Boost_NO_BOOST_CMAKE ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS unit_test_framework )


##########################################
# Source files for current project
##########################################  
set(PROJECT_SOURCES
        main.cpp
        test_material.cpp)


##########################################
# Set up test binary and add it as a test
##########################################
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
add_test(NAME EngineTest COMMAND ${PROJECT_NAME})
add_dependencies(${TEST_BUILD_ALL} ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} 
    PRIVATE ${Boost_INCLUDE_DIRS}
    )
    
target_link_libraries(${PROJECT_NAME} 
    PRIVATE ${Boost_LIBRARIES}
    PRIVATE ssrt::engine
    )