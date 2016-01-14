project (ssrt_cl VERSION 0.1.0)

set(SOURCES
        renderapplication.h
        renderapplication.cpp
        main.cpp)
        
       
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_INCLUDE_DIRS} ${SSRT_ENGINE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ssrt::engine)
    
    
create_vs_folders()

