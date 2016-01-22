##########
# Find GLM
##########
find_package(glm REQUIRED)

message(STATUS "glm FOUND ${glm_FOUND}")
add_subdirectory(engine)
add_subdirectory(cl)
