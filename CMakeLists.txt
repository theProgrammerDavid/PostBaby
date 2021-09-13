cmake_minimum_required(VERSION 3.14)
project(PostBaby)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Setting Debug profile")
    add_compile_definitions(DEBUG_BUILD=1)
else()
message("Setting Release profile")
add_compile_definitions(RELEASE_BUILD=1)
endif()

set(PostBaby_VERSION_MAJOR 1 CACHE STRING "major version" FORCE)
set(PostBaby_VERSION_MINOR 0 CACHE STRING "minor version" FORCE)
set(PostBaby_VERSION ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR} CACHE STRING "version" FORCE)

configure_file("${${PROJECT_NAME}_SOURCE_DIR}/include/config.hpp.in" "${${PROJECT_NAME}_SOURCE_DIR}/include/config.hpp")

configure_file("${PROJECT_SOURCE_DIR}/include/config.hpp.in" "${PROJECT_SOURCE_DIR}/include/config.hpp")

# add subdiretories
add_subdirectory(extern EXCLUDE_FROM_ALL)
add_subdirectory(src)
