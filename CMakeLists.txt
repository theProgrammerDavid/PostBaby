cmake_minimum_required(VERSION 3.0)
project(XP)


set(XP_VERSION_MAJOR 1 CACHE STRING "major version" FORCE)
set(XP_VERSION_MINOR 0 CACHE STRING "minor version" FORCE)
set(XP_VERSION ${XP_VERSION_MAJOR}.${XP_VERSION_MINOR} CACHE STRING "version" FORCE)

# add subdiretories
add_subdirectory(src)

set(CMAKE_INSTALL_PREFIX /usr/local/bin)
