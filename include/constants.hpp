#pragma once
#include <iostream>
#include <memory>
#include "util.hpp"
#include "imgui.h"

#ifdef _Win32
#include <Windows.h>
#endif

void glfw_error_callback(int error, const char *description);

class Constants
{
private:
    /* Here will be the instance stored. */
    // static Constants* instance;

    /* Private constructor to prevent instancing. */
    // Constants();

public:
    Constants();
    enum 
    {
        DARK,
        LIGHT,
        CLASSIC
    };
    void setTheme();
    int MAX_URL_SIZE;
    int WINDOW_WIDTH;
    int WINDOW_HEIGHT;
    int CURRENT_THEME;
    float FONT_SIZE;
    std::string PATH_TO_FONT;
    const char *REQUEST_TYPE[6] = {"GET", "POST", "PUT", "DELETE", "HEAD", "OPTIONS"};
    const char *THEMES[3] = {"DARK", "LIGHT", "CLASSIC"};

    /* Static access method. */
    // static Constants* getInstance();
};
