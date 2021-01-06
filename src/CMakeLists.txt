find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  )

include_directories("../include")

# set application icon
if (WIN32)
    set(ICON "${XP_SOURCE_DIR}/assets/xP.ico")
elseif (APPLE)
    set(ICON "${XP_SOURCE_DIR}/assets/xP.ico")
endif()

include_directories("${XP_SOURCE_DIR}/ext/imgui")	
file(GLOB SOURCES "*.cpp")	
file(GLOB IMGUI_SOURCES "${XP_SOURCE_DIR}/ext/imgui/*.cpp")
# configure config.hpp.in
configure_file("config.hpp.in" "${CMAKE_CURRENT_BINARY_DIR}/config_impl.hpp")
include_directories("${XP_SOURCE_DIR}/ext/imgui/backends")
file(GLOB IMGUI_BACKEND "${XP_SOURCE_DIR}/ext/imgui/backends/imgui_impl_glfw.cpp" "${XP_SOURCE_DIR}/ext/imgui/backends/imgui_impl_opengl3.cpp")

# gl3w
# include_directories("${XP_SOURCE_DIR}/ext/imgui/examples/libs/gl3w")
# file(GLOB GL3W_SOURCE "${XP_SOURCE_DIR}/ext/imgui/examples/libs/gl3w/GL/gl3w.c")

#glew
include_directories("${XP_SOURCE_DIR}/extern/glew/include")	
file(GLOB GLEW_SOURCES "${XP_SOURCE_DIR}/extern/glew/src")

# define library target
add_executable(xP 
${ICON}
${GLEW_SOURCES} 
${SOURCES} 
${IMGUI_SOURCES} 
${IMGUI_BACKEND}
)
target_include_directories(xP PUBLIC ${XP_SOURCE_DIR}/include${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_INSTALL_PREFIX /usr/local/bin)

target_link_libraries(xP
  PUBLIC
  glad
  glfw
  ${OPENGL_LIBRARIES}
  glew
  PRIVATE
  cpr::cpr
  ${CMAKE_DL_LIBS})


install(TARGETS xP 
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
)
add_custom_command(TARGET xP POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                       ${XP_SOURCE_DIR}/assets/JetBrainsMono-Medium.ttf
                       $<TARGET_FILE_DIR:xP>
                   )

install(FILES ${XP_SOURCE_DIR}/assets/JetBrainsMono-Medium.ttf DESTINATION ~)