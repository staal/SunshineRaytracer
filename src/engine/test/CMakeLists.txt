##########################################
# Tests
##########################################
set(TEST_NAME ${PROJECT_NAME}_test)
message(STATUS "Creating test ${TEST_NAME}")


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
set(TEST_SOURCES
        test_material.cpp)


##########################################
# Set up test binary and add it as a test
##########################################
add_executable(${TEST_NAME} main.cpp ${TEST_SOURCES})
add_test(NAME CommandlineTest COMMAND ${TEST_NAME})
add_dependencies(${TEST_BUILD_ALL} ${TEST_NAME})

target_include_directories(${TEST_NAME} 
    PRIVATE ${Boost_INCLUDE_DIRS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/.. #all headers from library to be included
    )
    
target_link_libraries(${TEST_NAME} 
    PRIVATE ${Boost_LIBRARIES}
    PRIVATE ssrt::engine
    )