##########################################
# Custom test target which also builds
##########################################
set(TEST_BUILD_ALL test_and_build_all)
add_custom_target(${TEST_BUILD_ALL} ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1
        ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    

##########################################
# Add all test subfolders
##########################################
add_subdirectory(engine)
add_subdirectory(cl)
add_subdirectory(sunshine)

