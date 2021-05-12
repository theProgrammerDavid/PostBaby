cmake_minimum_required(VERSION 3.14)
project(xP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Setting Debug profile")
    add_compile_definitions(XP_SHOW_IMGUI_DEMO_WINDOW=1)
    add_compile_definitions(DEBUG_BUILD=1)
else()
message("Setting Release profile")
add_compile_definitions(RELEASE_BUILD=1)
endif()

set(xP_VERSION_MAJOR 1 CACHE STRING "major version" FORCE)
set(xP_VERSION_MINOR 0 CACHE STRING "minor version" FORCE)
set(xP_VERSION ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR} CACHE STRING "version" FORCE)

configure_file("${${PROJECT_NAME}_SOURCE_DIR}/include/config.hpp.in" "${${PROJECT_NAME}_SOURCE_DIR}/include/config.hpp")

configure_file("${PROJECT_SOURCE_DIR}/include/config.hpp.in" "${PROJECT_SOURCE_DIR}/include/config.hpp")

set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "disable yaml tests")
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "disable yaml tools")
set(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "disable yaml contrib")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# add subdiretories
add_subdirectory(extern EXCLUDE_FROM_ALL)
add_subdirectory(src)
