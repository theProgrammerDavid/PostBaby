# set headers
set(header_path "../include")
include_directories("../include")
include_directories("${XP_SOURCE_DIR}/ext/imgui")	
file(GLOB SOURCES "*.cpp")	
file(GLOB IMGUI_SOURCES "${XP_SOURCE_DIR}/ext/imgui/*.cpp")
# configure config.hpp.in
configure_file("config.hpp.in" "${CMAKE_CURRENT_BINARY_DIR}/config_impl.hpp")

# define library target
add_executable(XP ${SOURCES} ${IMGUI_SOURCES})
target_include_directories(XP PUBLIC ${XP_SOURCE_DIR}/include${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_INSTALL_PREFIX /usr/local/bin)

install(TARGETS XP 
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
)