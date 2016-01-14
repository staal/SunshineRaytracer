##########
# Find GLM
##########
find_package(GLM REQUIRED)

message(STATUS "GLM FOUND ${GLM_FOUND}")
add_subdirectory(engine)
add_subdirectory(cl)
