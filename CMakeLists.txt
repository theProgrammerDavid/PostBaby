cmake_minimum_required(VERSION 3.14)
project(XP)


set(XP_VERSION_MAJOR 1 CACHE STRING "major version" FORCE)
set(XP_VERSION_MINOR 0 CACHE STRING "minor version" FORCE)
set(XP_VERSION ${XP_VERSION_MAJOR}.${XP_VERSION_MINOR} CACHE STRING "version" FORCE)

# add subdiretories
add_subdirectory(src)
add_subdirectory(extern)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


add_subdirectory("${XP_SOURCE_DIR}/ext/glfw")
add_subdirectory("${XP_SOURCE_DIR}/ext/glew-cmake/build/cmake")
set(CMAKE_INSTALL_PREFIX /usr/local/bin)
