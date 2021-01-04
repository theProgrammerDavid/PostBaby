cmake_minimum_required(VERSION 3.14)
project(XP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX)
find_package(X11 REQUIRED)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

else(WIN32)

set(CMAKE_CXX_FLAGS "/Wall")
set(CMAKE_CXX_FLAGS_RELEASE "/O3")

endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


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
