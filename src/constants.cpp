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
void Constants::setOnlineStatus(bool status)
{
    this->isOnline = status;
}
Constants::Constants()
{
    if (fileExists(CONFIG_FILE))
    {
        YAML::Node config = YAML::LoadFile(CONFIG_FILE);
        
        if (config["PATH_TO_FONT"])
        {
            this->PATH_TO_FONT = config["PATH_TO_FONT"].as<std::string>();
        }
        else
        {
            this->PATH_TO_FONT = absolutePath() + "/JetBrainsMono-Medium.ttf";
        }

        this->MAX_URL_SIZE = config["MAX_URL_SIZE"].as<int>();
        this->FONT_SIZE = config["FONT_SIZE"].as<float>();
        this->WINDOW_HEIGHT = config["WINDOW_HEIGHT"].as<int>();
        this->WINDOW_WIDTH = config["WINDOW_WIDTH"].as<int>();
        this->REQUEST_TIMEOUT = config["REQUEST_TIMEOUT"].as<float>();
        this->configError = false;
    }
    else
    {
        this->defaultValues();
    }
}

void Constants::defaultValues()
{
    this->MAX_URL_SIZE = 256;
    this->isOnline = false;
    this->PATH_TO_FONT = absolutePath() + "/JetBrainsMono-Medium.ttf";
    this->FONT_SIZE = 18.0f;
    this->WINDOW_HEIGHT = 720;
    this->WINDOW_WIDTH = 1280;
    this->CURRENT_THEME = DARK;
    this->REQUEST_TIMEOUT = 5000;
    this->isOnline = false;
    this->highDPIscaleFactor = 1.0;
    this->configError = false;
}

bool Constants::configFileExists()
{
    return fileExists(CONFIG_FILE);
}

void Constants::createConfigFile()
{
    std::cout << "creating config file\n";
    std::ofstream fout(CONFIG_FILE);
    fout << "MAX_URL_SIZE: 256\nFONT_SIZE : 18.0\nWINDOW_HEIGHT : 720\nWINDOW_WIDTH : 1280\nCURRENT_THEME : DARK\nREQUEST_TIMEOUT : 5000 ";
    fout.close();
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
