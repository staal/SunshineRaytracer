project (ssrt_cl)
message(STATUS "Creating Executable ${PROJECT_NAME}")

#Use boost for command line arguments
#Default to use static linking to Boost
set(Boost_NO_BOOST_CMAKE ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS program_options filesystem system )
  
set(PROJECT_SOURCES
        renderapplication.h
        renderapplication.cpp
        commandlinehandler.h
        commandlinehandler.cpp
        main.cpp)
       

#Adding clconfig.h here to avoid it getting indexed through create_vs_folders
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${GLM_INCLUDE_DIRS} ${SSRT_ENGINE_INCLUDE_DIRS}
    PRIVATE ${PROJECT_BINARY_DIR} #So version header can be located
    PRIVATE ${Boost_INCLUDE_DIRS}
    )
    
target_link_libraries(${PROJECT_NAME} 
    PRIVATE ssrt::engine
    PRIVATE ${Boost_LIBRARIES}
    )
    
create_vs_folders("${PROJECT_SOURCES}")

