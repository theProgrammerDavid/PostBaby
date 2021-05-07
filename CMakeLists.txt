cmake_minimum_required(VERSION 3.14)
project(xP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
message("Setting Debug profile")
add_compile_definitions(XP_SHOW_IMGUI_DEMO_WINDOW=1)
else()
message("Setting Release profile")
endif()

set(${PROJECT_NAME}_VERSION_MAJOR 1 CACHE STRING "major version" FORCE)
set(${PROJECT_NAME}_VERSION_MINOR 0 CACHE STRING "minor version" FORCE)
set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR} CACHE STRING "version" FORCE)

configure_file("${${PROJECT_NAME}_SOURCE_DIR}/include/config.hpp.in" "${${PROJECT_NAME}_SOURCE_DIR}/include/config.hpp")

set(CMAKE_INSTALL_PREFIX /usr/local/bin)

# add subdiretories
add_subdirectory(extern EXCLUDE_FROM_ALL)
add_subdirectory(src)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

