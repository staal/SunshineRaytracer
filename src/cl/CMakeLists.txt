project (ssrt_cl VERSION 0.1.0)

# configure a header file to pass some of the CMake settings to the source code
configure_file (
  "clversion.h.in"
  "${PROJECT_BINARY_DIR}/clversion.h"
  )
  
set(PROJECT_SOURCES
        renderapplication.h
        renderapplication.cpp
        main.cpp)
       
message(STATUS "Creating Executable ${PROJECT_NAME}")

#Adding clconfig.h here to avoid it getting indexed through create_vs_folders
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} "${PROJECT_BINARY_DIR}/clversion.h")

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${GLM_INCLUDE_DIRS} ${SSRT_ENGINE_INCLUDE_DIRS}
    PRIVATE ${PROJECT_BINARY_DIR} #So version header can be located
    )
    
target_link_libraries(${PROJECT_NAME} 
    PRIVATE ssrt::engine
    )
    
create_vs_folders("${PROJECT_SOURCES}")

