include(FetchContent)

find_package(OpenGL REQUIRED)
if(UNIX)
  find_package(OpenSSL REQUIRED)
endif()
include_directories(${OPENGL_INCLUDE_DIRS})

include_directories("../include")
find_file(DEBIAN_FOUND debian_version debconf.conf PATHS /etc)
# set application icon
if(WIN32)
  set(ICON "${PROJECT_SOURCE_DIR}/assets/PostBaby.rc")
elseif(APPLE)
  set(ICON "${PROJECT_SOURCE_DIR}/assets/PostBaby.ico")
endif()

FetchContent_GetProperties(imgui)
if(imgui_POPULATED)
  include_directories(${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends
                      ${imgui_SOURCE_DIR}/misc/cpp)
endif()

FetchContent_GetProperties(pfd)
if(pfd_POPULATED)
include_directories(${pfd_SOURCE_DIR})
endif()

include_directories(${CMAKE_SOURCE_DIR}/extern/tidy/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/glew/include)
include_directories(${CMAKE_SOURCE_DIR}/include/platform_specific)

file(GLOB SOURCES "*.cpp")

if(WIN32)
  file(GLOB PLATFORM_SOURCES "platform_specific/windows.cpp")
elseif(APPLE)
  file(GLOB PLATFORM_SOURCES "platform_specific/apple.cpp")
else()
  message("using linux configs")
  file(GLOB PLATFORM_SOURCES "platform_specific/linux.cpp")
endif()

file(
  GLOB
  IMGUI_SOURCES
  "${imgui_SOURCE_DIR}/*.cpp"
  "${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp"
  "${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
  "${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp")
file(GLOB IMGUI_BACKEND)

# define executable target
add_executable(
  ${PROJECT_NAME} ${ICON} ${SOURCES} ${IMGUI_SOURCES} ${PLATFORM_SOURCES}
                  ${${PROJECT_NAME}_SOURCE_DIR}/assets/PostBaby.rc)
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC ${${PROJECT_NAME}_SOURCE_DIR}/include${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC ${OPENGL_LIBRARIES}
  PRIVATE nlohmann_json::nlohmann_json
          yaml-cpp
          tidy-static
          spdlog::spdlog
          SQLiteCpp
          sqlite3
          glfw
          cpr::cpr
          glew_s
          CURL::libcurl
          ${CMAKE_DL_LIBS})

if(UNIX)
  install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
  # https://stackoverflow.com/questions/51698076/why-cpack-generates-an-empty-package
  # RUNTIME DESTIONATION should be relative within the package
endif()
if(WIN32)
  install(
    TARGETS ${PROJECT_NAME}
    # CPack NSIS gives error if absolute path
    # so you can't use DESTINATION ${CMAKE_INSTALL_PREFIX}
    # https://cmake.org/pipermail/cmake/2013-May/054656.html
    RUNTIME DESTINATION bin)
endif()
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy_if_different
    ${PROJECT_SOURCE_DIR}/assets/JetBrainsMono-Medium.ttf
    ${PROJECT_SOURCE_DIR}/assets/ca.cer ${PROJECT_SOURCE_DIR}/assets/client.cer
    ${PROJECT_SOURCE_DIR}/assets/client.key
    ${PROJECT_SOURCE_DIR}/assets/cacert.pem $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# add_custom_command( TARGET ${PROJECT_NAME} POST_BUILD COMMAND
# $<$<CONFIG:release>:${CMAKE_STRIP} ${PROJECT_NAME}>)

if(UNIX)
  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_STRIP} ${PROJECT_SOURCE_DIR}/build/src/${PROJECT_NAME})
endif()

if(WIN32)
  install(
    FILES ${PROJECT_SOURCE_DIR}/assets/JetBrainsMono-Medium.ttf
          ${PROJECT_SOURCE_DIR}/assets/PostBaby.png
          # ${PROJECT_SOURCE_DIR}/assets/ca.cer
          # ${PROJECT_SOURCE_DIR}/assets/client.cer
          # ${PROJECT_SOURCE_DIR}/assets/client.key
    DESTINATION bin)
else()
  install(
    FILES ${PROJECT_SOURCE_DIR}/assets/JetBrainsMono-Medium.ttf
          ${PROJECT_SOURCE_DIR}/assets/PostBaby.png
          ${PROJECT_SOURCE_DIR}/assets/ca.cer
          ${PROJECT_SOURCE_DIR}/assets/client.cer
          ${PROJECT_SOURCE_DIR}/assets/cacert.pem
          ${PROJECT_SOURCE_DIR}/assets/client.key
    DESTINATION bin)
  # https://stackoverflow.com/questions/51698076/why-cpack-generates-an-empty-package
  # RUNTIME DESTIONATION should be relative within the package
endif()

if(DEBIAN_FOUND)
  install(FILES ${PROJECT_SOURCE_DIR}/assets/PostBaby.desktop
          DESTINATION /usr/share/applications)

  set(CPACK_GENERATOR "DEB")
  set(CPACK_DEBIAN_PACKAGE_NAME "${PROJECT_NAME}")
  set(CPACK_DEBIAN_PACKAGE_VERSION "1.0")
  set(CPACK_DEBIAN_PACKAGE_DEPENDS
      "libc6 (>= 2.3.1-6), libgcc1 (>= 1:3.4.2-12)")
  set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
  set(CPACK_PACKAGE_VENDOR "theProgrammerDavid")
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "David Velho")
  set(CPACK_VERBATIM_VARIABLES true)
  set(CPACK_PACKAGE_VERSION_MAJOR ${${PROJECT_NAME}_VERSION_MAJOR})
  set(CPACK_PACKAGE_VERSION_MINOR ${${PROJECT_NAME}_VERSION_MINOR})
  # set(CPACK_PACKAGE_VERSION_PATCH 0)
  include(CPack)
elseif(WIN32)
  message(
    " ######################################using nsis for windows###########################"
  )
  include(InstallRequiredSystemLibraries)
  set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}")
  set(CPACK_GENERATOR "NSIS")
  set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
  set(CPACK_PACKAGE_VERSION
      "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}")
  set(CPACK_PACKAGE_VERSION_PATCH "0")
  set(CPACK_PACKAGE_VENDOR "David Velho")
  set(CPACK_NSIS_MODIFY_PATH "ON")
  set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY ${PROJECT_NAME})

  set(CPACK_NSIS_MUI_ICON "${PROJECT_SOURCE_DIR}/assets/PostBaby.ico")
  set(CPACK_NSIS_MUI_UNICON "${PROJECT_SOURCE_DIR}/assets/PostBaby.ico")
  set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL "ON")

  set(CPACK_SOURCE_GENERATOR "TGZ")
  set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
  set(CPACK_SOURCE_PACKAGE_FILE_NAME
      "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
  set(CPACK_SOURCE_IGNORE_FILES ${CPACK_IGNORE_FILES})

  set(CPACK_NSIS_CREATE_ICONS_EXTRA
      "CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${PROJECT_NAME}.lnk' '$INSTDIR\\\\bin\\\\${PROJECT_NAME}.exe' "
  )
  set(CPACK_NSIS_DELETE_ICONS_EXTRA
      "Delete '$SMPROGRAMS\\\\$START_MENU\\\\${PROJECT_NAME}.lnk'")
  set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS
      "
    CreateShortCut '$DESKTOP\\\\${PROJECT_NAME}.lnk' '$INSTDIR\\\\bin\\\\${PROJECT_NAME}.exe'
    ")
  set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS
      "
    Delete '$DESKTOP\\\\${PROJECT_NAME}.lnk'
    ")
  set(CPACK_NSIS_INSTALLED_ICON_NAME
      "${PROJECT_SOURCE_DIR}/assets/PostBaby.ico")
  set(CPACK_NSIS_HELP_LINK "https://github.com/theProgrammerDavid/PostBaby")
  set(CPACK_NSIS_URL_INFO_ABOUT
      "https://github.com/theProgrammerDavid/PostBaby")
  set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/assets/nsis ${CMAKE_MODULE_PATH})
  include(CPack)

  configure_file(${PROJECT_SOURCE_DIR}/assets/nsis/NSIS.definitions.nsh.in
                 ${CMAKE_CURRENT_BINARY_DIR}/assets/nsis/NSIS.definitions.nsh)

else()
  # UNIX
  install(FILES ${PROJECT_SOURCE_DIR}/assets/PostBaby.desktop
          DESTINATION /usr/share/applications)
  message("#### linux ####")
  set(CPACK_GENERATOR "ZIP")
  set(CPACK_ARCHIVE_FILE_NAME "PostBaby.zip")
  set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
  include(CPack)
endif()
