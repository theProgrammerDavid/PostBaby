#include "constants.hpp"

void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
// Constants *Constants::instance = 0;

// Constants *Constants::getInstance()
// {
//     if (instance == 0)
//     {
//         instance = new Constants();
//     }

//     return instance;
// }

Constants::Constants()
{
    this->MAX_URL_SIZE = 256;
    this->PATH_TO_FONT = std::string(abs_exe_path().u8string()) + "/JetBrainsMono-Medium.ttf";
    this->FONT_SIZE = 18.0f;
    this->WINDOW_HEIGHT = 720;
    this->WINDOW_WIDTH = 1280;
    this->CURRENT_THEME = DARK;
}

void Constants::setTheme()
{
    if (this->CURRENT_THEME == this->DARK)
        ImGui::StyleColorsDark();
    else if (this->CURRENT_THEME == this->LIGHT)
        ImGui::StyleColorsLight();
    else
        ImGui::StyleColorsClassic();
}

// Constants *constants = constants->getInstance();
// std::unique_ptr<Constants> constants{constants->getInstance()};
std::unique_ptr<Constants> constants{new Constants()};