find_package(OpenGL REQUIRED)
if(UNIX)
find_package(OpenSSL REQUIRED)
endif()
include_directories( ${OPENGL_INCLUDE_DIRS}  )

include_directories("../include")

# set application icon
if (WIN32)
    set(ICON "${PROJECT_SOURCE_DIR}/assets/xP.rc")
elseif (APPLE)
    set(ICON "${PROJECT_SOURCE_DIR}/assets/xP.ico")
endif()

include_directories("${PROJECT_SOURCE_DIR}/extern/imgui")	
file(GLOB SOURCES "*.cpp")	
file(GLOB IMGUI_SOURCES "${PROJECT_SOURCE_DIR}/extern/imgui/*.cpp")

# define executable target
add_executable(xP 
${ICON}
${SOURCES} 
${IMGUI_SOURCES}
${PROJECT_SOURCE_DIR}/assets/xP.rc
)
target_include_directories(xP PUBLIC ${PROJECT_SOURCE_DIR}/include${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(xP
  PUBLIC
  ${OPENGL_LIBRARIES}
  PRIVATE
  glad
  yaml-cpp
  glfw
  cpr::cpr
  glew
  CURL::libcurl
  ${CMAKE_DL_LIBS})

if(UNIX)
    install(TARGETS xP 
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
    )
endif()
if(WIN32)
    install(TARGETS xP 
        # CPack NSIS gives error if absolute path
        # so you can't use DESTINATION ${CMAKE_INSTALL_PREFIX} 
        # https://cmake.org/pipermail/cmake/2013-May/054656.html
        RUNTIME DESTINATION bin
    )
endif()
add_custom_command(TARGET xP POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                       ${PROJECT_SOURCE_DIR}/assets/JetBrainsMono-Medium.ttf
                        ${PROJECT_SOURCE_DIR}/assets/ca.cer
                        ${PROJECT_SOURCE_DIR}/assets/client.cer
                        ${PROJECT_SOURCE_DIR}/assets/client.key
                       $<TARGET_FILE_DIR:xP>
                   )

if(WIN32)
    install(FILES 
    ${PROJECT_SOURCE_DIR}/assets/JetBrainsMono-Medium.ttf 
    ${PROJECT_SOURCE_DIR}/assets/ca.cer
    ${PROJECT_SOURCE_DIR}/assets/client.cer
    ${PROJECT_SOURCE_DIR}/assets/client.key
    ${PROJECT_SOURCE_DIR}/assets/xP.png
    DESTINATION bin
    )
else()
    install(FILES 
    ${PROJECT_SOURCE_DIR}/assets/JetBrainsMono-Medium.ttf 
    ${PROJECT_SOURCE_DIR}/assets/ca.cer
    ${PROJECT_SOURCE_DIR}/assets/client.cer
    ${PROJECT_SOURCE_DIR}/assets/client.key
    ${PROJECT_SOURCE_DIR}/assets/xP.png
    DESTINATION ${CMAKE_INSTALL_PREFIX})
endif()

if(UNIX)
    install( FILES
        ${PROJECT_SOURCE_DIR}/assets/xP.desktop
        DESTINATION
    /usr/share/applications
    )

    SET(CPACK_GENERATOR "DEB")
    SET(CPACK_DEBIAN_PACKAGE_NAME "xP")
    SET(CPACK_DEBIAN_PACKAGE_VERSION "1.0")
    SET(CPACK_PACKAGE_CONTACT "me@davidvelho.tech")
    SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.1-6), libgcc1 (>= 1:3.4.2-12)")
    set(CPACK_PACKAGE_NAME "xP")
    set(CPACK_PACKAGE_VENDOR "theProgrammerDavid")
    set(CPACK_VERBATIM_VARIABLES true)
    set(CPACK_PACKAGE_VERSION_MAJOR ${XP_VERSION_MAJOR})
    set(CPACK_PACKAGE_VERSION_MINOR ${XP_VERSION_MINOR})
    # set(CPACK_PACKAGE_VERSION_PATCH 0)
    include(CPack)
endif()

if(WIN32)
    message(" ######################################using nsis for windows###########################")
    include(InstallRequiredSystemLibraries)
    set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "xP")
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
    set(CPACK_PACKAGE_VERSION "${XP_VERSION_MAJOR}.${XP_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "0")
    set(CPACK_PACKAGE_VENDOR "David Velho")
    set (CPACK_NSIS_MODIFY_PATH "ON")
    set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY ${PROJECT_NAME})

    set(CPACK_NSIS_MUI_ICON "${PROJECT_SOURCE_DIR}/assets/xP.ico")
    set(CPACK_NSIS_MUI_UNICON "${PROJECT_SOURCE_DIR}/assets/xP.ico")
    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL "ON")

    set(CPACK_SOURCE_GENERATOR "TGZ")
    set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
    set(CPACK_SOURCE_IGNORE_FILES ${CPACK_IGNORE_FILES})
    
    set(CPACK_NSIS_CREATE_ICONS_EXTRA
    "CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\xP.lnk' '$INSTDIR\\\\bin\\\\xP.exe' "
    )
    set(CPACK_NSIS_DELETE_ICONS_EXTRA
    "Delete '$SMPROGRAMS\\\\$START_MENU\\\\xP.lnk'"
    )
    set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
    CreateShortCut '$DESKTOP\\\\xP.lnk' '$INSTDIR\\\\bin\\\\xP.exe'
    ")
    set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
    Delete '$DESKTOP\\\\xP.lnk'
    ")
    set(CPACK_NSIS_INSTALLED_ICON_NAME "${PROJECT_SOURCE_DIR}/assets/xP.ico")
    set(CPACK_NSIS_HELP_LINK "https://github.com/theProgrammerDavid/xP")
    set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/theProgrammerDavid/xP")
    set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/assets/nsis ${CMAKE_MODULE_PATH})
    include(CPack)

    configure_file(
    ${PROJECT_SOURCE_DIR}/assets/nsis/NSIS.definitions.nsh.in
    ${CMAKE_CURRENT_BINARY_DIR}/assets/nsis/NSIS.definitions.nsh
    )   
endif()
