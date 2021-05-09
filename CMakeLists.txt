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

set(XP_VERSION_MAJOR 1 CACHE STRING "major version" FORCE)
set(XP_VERSION_MINOR 0 CACHE STRING "minor version" FORCE)
set(XP_VERSION ${XP_VERSION_MAJOR}.${XP_VERSION_MINOR} CACHE STRING "version" FORCE)

if(WIN32)
else()
    set(CMAKE_INSTALL_PREFIX /usr/local/bin)
    set(INI_FILE "$ENV{HOME}/.config/${PROJECT_NAME}.ini")
    set(CONFIG_FILE "$ENV{HOME}/.config/${PROJECT_NAME}.yml")
endif()

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
