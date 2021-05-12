cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
# Multi-Language Vulkan/GL/GLES/EGL/GLX/WGL Loader-Generator based on
# the official specs. http://glad.dav1d.de/
#https://github.com/Dav1dde/glad/issues/174
include(FetchContent)

if(WIN32)
  set(USE_OPENSSL OFF)
  set(USE_WINSSL ON)
  set(CMAKE_USE_OPENSSL OFF)
  set(BUILD_CPR_TESTS OFF) #testing. if enabled, needs PERL
endif()

FetchContent_Declare(
  extern_glad

  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        v0.1.27)

FetchContent_GetProperties(extern_glad)
if(NOT extern_glad_POPULATED)
  FetchContent_Populate(extern_glad)

  set(GLAD_INSTALL ON)
  add_subdirectory(
    ${extern_glad_SOURCE_DIR}
    ${extern_glad_BINARY_DIR}
    EXCLUDE_FROM_ALL)
endif()

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 0b9e48fa3df9c184ff1abfb2452fd1a4b696ecd8) 
FetchContent_MakeAvailable(glfw)

# glew 
FetchContent_Declare(
  GLEW
  URL            https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.zip
  SOURCE_DIR     ${CMAKE_SOURCE_DIR}/extern/glew
)

FetchContent_GetProperties(glew)
if(NOT glew_POPULATED)
  FetchContent_Populate(glew)
  add_subdirectory(${CMAKE_SOURCE_DIR}/extern/glew/build/cmake)
endif()

# imgui
# FetchContent_Declare(
#   imgui
#   GIT_REPOSITORY https://github.com/ocornut/imgui.git
#   SOURCE_DIR     ${CMAKE_SOURCE_DIR}/extern/imgui
#   GIT_TAG        626e3e2b3bc1d3802ef177b497b00c5da98e93ee

# )
# FetchContent_GetProperties(imgui)
# if(NOT imgui_POPULATED)
#   FetchContent_Populate(imgui)
# endif()

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/whoshuu/cpr.git GIT_TAG e538269b0705a46f7e56255421f8e97261f2909a)
FetchContent_MakeAvailable(cpr)

include(FetchContent)
FetchContent_Declare(yamlcpp GIT_REPOSITORY https://github.com/jbeder/yaml-cpp GIT_TAG a6bbe0e50ac4074f0b9b44188c28cf00caf1a723)
FetchContent_MakeAvailable(yamlcpp)

if(NOT yamlcpp_POPULATED)
  FetchContent_Populate(yamlcpp)
  add_subdirectory(${yamlcpp_SOURCE_DIR} ${yamlcpp_BINARY_DIR})
endif()

set(SUPPORT_CONSOLE_APP OFF)
set(BUILD_SHARED_LIB OFF)

FetchContent_Declare(
  tidy
  GIT_REPOSITORY https://github.com/htacg/tidy-html5.git
  SOURCE_DIR     ${CMAKE_SOURCE_DIR}/extern/tidy
  GIT_TAG        f6376f82c8d75a2b88d0860497ae39a150ef97e4
  
  )
  FetchContent_GetProperties(tidy)
  if(NOT tidy_POPULATED)
  FetchContent_Populate(tidy)
  endif()
  add_subdirectory(${CMAKE_SOURCE_DIR}/extern/tidy)