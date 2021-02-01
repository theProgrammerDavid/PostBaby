find_package(OpenGL REQUIRED)
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

set(CMAKE_INSTALL_PREFIX /usr/local/bin)

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
                       $<TARGET_FILE_DIR:xP>
                   )

install(FILES ${XP_SOURCE_DIR}/assets/JetBrainsMono-Medium.ttf DESTINATION ~)