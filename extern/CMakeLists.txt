cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

include(FetchContent)

set(YAML_CPP_BUILD_TESTS
    OFF
    CACHE BOOL "disable yaml tests")
set(YAML_CPP_BUILD_TOOLS
    OFF
    CACHE BOOL "disable yaml tools")
set(YAML_CPP_BUILD_CONTRIB
    OFF
    CACHE BOOL "disable yaml contrib")

set(GLFW_BUILD_DOCS
    OFF
    CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS
    OFF
    CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES
    OFF
    CACHE BOOL "" FORCE)
set(JSON_BuildTests
    OFF
    CACHE INTERNAL "")

set(CPR_BUILD_TESTS_SSL OFF)
set(CPR_BUILD_TESTS OFF) # testing. if enabled, needs PER
if(WIN32)
  set(CPR_FORCE_WINSSL_BACKEND ON)
endif()

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 0b9e48fa3df9c184ff1abfb2452fd1a4b696ecd8)
FetchContent_MakeAvailable(glfw)

# glew
FetchContent_Declare(
  GLEW
  URL https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip
      SOURCE_DIR
      ${CMAKE_SOURCE_DIR}/extern/glew)

FetchContent_GetProperties(glew)
if(NOT glew_POPULATED)
  FetchContent_Populate(glew)
  add_subdirectory(${CMAKE_SOURCE_DIR}/extern/glew/build/cmake)
endif()

# imgui
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG 677fe33990ac02d925da3d5a929bbbb6f01800bd)
FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
  FetchContent_Populate(imgui)
endif()

FetchContent_Declare(
  cpr
  GIT_REPOSITORY https://github.com/whoshuu/cpr.git
  GIT_TAG f4622efcb59d84071ae11404ae61bd821c1c344b)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG 8826011c81b69e1f8427be520b357c19c74ea480)
FetchContent_MakeAvailable(spdlog)
if(NOT spdlog_POPULATED)
  FetchContent_Populate(spdlog)
  add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
endif()

set(SQLITECPP_RUN_CPPCHECK
    OFF
    CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT
    OFF
    CACHE BOOL "" FORCE)
set(SQLITECPP_USE_STATIC_RUNTIME
    OFF
    CACHE BOOL "" FORCE)

FetchContent_Declare(
  sqlite3
  GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
  GIT_TAG 44bd9c4f38e7552f411944a3208cddfa759406ce)
FetchContent_MakeAvailable(sqlite3)

FetchContent_Declare(
  yamlcpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp
  GIT_TAG a6bbe0e50ac4074f0b9b44188c28cf00caf1a723)
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
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/extern/tidy
  GIT_TAG f6376f82c8d75a2b88d0860497ae39a150ef97e4)
FetchContent_GetProperties(tidy)
if(NOT tidy_POPULATED)
  FetchContent_Populate(tidy)
endif()
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/tidy)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# portable file dialogs (pfd)
FetchContent_Declare(
  pfd
  GIT_REPOSITORY https://github.com/samhocevar/portable-file-dialogs.git
  GIT_TAG dea8520de18af09eefdbc18aaf7c24409d18491b)

FetchContent_GetProperties(pfd)
if(NOT pfd_POPULATED)
  FetchContent_Populate(pfd)
  add_subdirectory(${pfd_SOURCE_DIR} ${pfd_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()