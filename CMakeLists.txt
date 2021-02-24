cmake_minimum_required(VERSION 3.14)
project(XP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
message("Setting Debug profile")
add_compile_definitions(XP_SHOW_IMGUI_DEMO_WINDOW=1)
else()
message("Setting Release profile")
endif()

set(XP_VERSION_MAJOR 1 CACHE STRING "major version" FORCE)
set(XP_VERSION_MINOR 0 CACHE STRING "minor version" FORCE)
set(XP_VERSION ${XP_VERSION_MAJOR}.${XP_VERSION_MINOR} CACHE STRING "version" FORCE)

set(CMAKE_INSTALL_PREFIX /usr/local/bin)
set(CMAKE_INSTALL_RPATH /usr/local/bin)

# add subdiretories
add_subdirectory(extern EXCLUDE_FROM_ALL)
add_subdirectory(src)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

