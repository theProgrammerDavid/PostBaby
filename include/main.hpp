#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cpr/cpr.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdio.h>

#include "config.hpp"
#include "constants.hpp"
#include "gui.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "tab.hpp"


void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mode);
const GLuint WIDTH = 800, HEIGHT = 600;
using namespace cpr;

bool checkOnline();
void PostBabyInit();
// Include glfw3.h after our OpenGL definitions

#if defined(_MSC_VER) && (_MSC_VER >= 1900) &&                                 \
    !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#define WINDOW_TITLE "PostBaby v" PostBaby_VERSION
const char *imguiIniFilePreset = "Collapsed=0\n"
                                 "\n"
                                 "[Window][config]\n"
                                 "Pos=2,3\n"
                                 "Size=1270,709\n"
                                 "Collapsed=0\n"
                                 "\n"
                                 "[Table][0x6416BC47,5]\n"
                                 "RefScale=22.5\n"
                                 "Column 0  Width=31\n"
                                 "Column 1  Weight=1.0000\n"
                                 "Column 2  Weight=1.0000\n"
                                 "Column 3  Weight=1.0000\n"
                                 "Column 4  Width=31\n";
