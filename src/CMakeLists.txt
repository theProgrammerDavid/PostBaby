find_package(OpenGL REQUIRED)
if(UNIX)
find_package(OpenSSL REQUIRED)
endif()
include_directories( ${OPENGL_INCLUDE_DIRS}  )

include_directories("../include")

# set application icon
if (WIN32)
    set(ICON "${XP_SOURCE_DIR}/assets/xP.ico")
elseif (APPLE)
    set(ICON "${XP_SOURCE_DIR}/assets/xP.ico")
endif()

include_directories("${XP_SOURCE_DIR}/extern/imgui")	
file(GLOB SOURCES "*.cpp")	
file(GLOB IMGUI_SOURCES "${XP_SOURCE_DIR}/extern/imgui/*.cpp")

# configure config.hpp.in
configure_file("config.hpp.in" "${CMAKE_CURRENT_BINARY_DIR}/config_impl.hpp")

# define executable target
add_executable(xP 
${ICON}
${SOURCES} 
${IMGUI_SOURCES} 
)
target_include_directories(xP PUBLIC ${XP_SOURCE_DIR}/include${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(xP
  PUBLIC
  glad
  glfw
  ${OPENGL_LIBRARIES}
  PRIVATE
  cpr::cpr
  glew
  CURL::libcurl
  ${CMAKE_DL_LIBS})


install(TARGETS xP 
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
)
add_custom_command(TARGET xP POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                       ${XP_SOURCE_DIR}/assets/JetBrainsMono-Medium.ttf
                        ${XP_SOURCE_DIR}/assets/ca.cer
                        ${XP_SOURCE_DIR}/assets/client.cer
                        ${XP_SOURCE_DIR}/assets/client.key
                       $<TARGET_FILE_DIR:xP>
                   )

install(FILES 
${XP_SOURCE_DIR}/assets/JetBrainsMono-Medium.ttf 
${XP_SOURCE_DIR}/assets/ca.cer
${XP_SOURCE_DIR}/assets/client.cer
${XP_SOURCE_DIR}/assets/client.key
${XP_SOURCE_DIR}/assets/xP.png
DESTINATION ${CMAKE_INSTALL_PREFIX})

if(UNIX)
install( FILES
    ${XP_SOURCE_DIR}/assets/xP.desktop
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