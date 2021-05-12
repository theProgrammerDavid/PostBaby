#include "constants.hpp"

void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
void Constants::setOnlineStatus(bool status)
{
    this->isOnline = status;
}
Constants::Constants()
{
    this->windowFlags = ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY | ImGuiTableFlags_ScrollX;
    windowFlags = ImGuiWindowFlags_NoTitleBar;
    this->sslOpts = Ssl(ssl::CaPath{absolutePath() + "ca.cer"}, ssl::CertFile{absolutePath() + "client.cer"},
                  ssl::KeyFile{absolutePath() + "client.key"}, ssl::VerifyPeer{false},
                  ssl::VerifyHost{false}, ssl::VerifyStatus{false});

#if _WIN32
    this->workingDir = getenv("AppData");
    this->workingDir += "\\xP";
    this->configFilePath = this->workingDir + "\\xP.yml";
    this->iniFilePath = this->workingDir + "\\imgui.ini";
#elif __linux__
    this->workingDir = getenv("HOME");
    this->workingDir += "/.config/xP";
    this->configFilePath = this->workingDir + "/xP.yml";
    this->iniFilePath = this->workingDir + "/imgui.ini";

#endif
    this->defaultValues();
    if (fileExists(this->configFilePath))
    {
        config = YAML::LoadFile(this->configFilePath.c_str());

        if (config["PATH_TO_FONT"])
        {
            this->PATH_TO_FONT = config["PATH_TO_FONT"].as<std::string>();
        }
        else
        {
            this->PATH_TO_FONT = absolutePath() + "/JetBrainsMono-Medium.ttf";
        }
        if (config["MOVEABLE_WINDOW"])
        {
            this->moveWindow = config["MOVEABLE_WINDOW"].as<int>();
            this->updateWindowFlags();
        }
        this->MAX_URL_SIZE = config["MAX_URL_SIZE"].as<int>();
        this->FONT_SIZE = config["FONT_SIZE"].as<float>();
        this->WINDOW_HEIGHT = config["WINDOW_HEIGHT"].as<int>();
        this->WINDOW_WIDTH = config["WINDOW_WIDTH"].as<int>();
        this->REQUEST_TIMEOUT = config["REQUEST_TIMEOUT"].as<int>();
        this->configError = false;
        this->CURRENT_THEME = config["CURRENT_THEME"].as<int>();
    }
}

void Constants::updateWindowFlags()
{
    if (!this->moveWindow)
    {
        this->windowFlags |= ImGuiWindowFlags_NoMove;
    }
    else
    {
        this->windowFlags &= ~ImGuiWindowFlags_NoMove;
    }
}

ImGuiWindowFlags Constants::getWindowFlags()
{
    return this->windowFlags;
}

const char *Constants::getWorkingDir()
{
    return this->workingDir.c_str();
}
const char *Constants::getConfigFilePath()
{
    return this->configFilePath.c_str();
}
const char *Constants::getIniFilePath()
{
    return this->iniFilePath.c_str();
}
void Constants::defaultValues()
{
    this->MAX_URL_SIZE = 256;
    this->moveWindow = true;
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
    return fileExists(this->configFilePath.c_str());
}

void Constants::createConfigFile()
{
    std::ofstream fout(this->configFilePath.c_str());
    fout << "MAX_URL_SIZE: 256\nMOVEABLE_WINDOW : 1\nFONT_SIZE : 18.0\nWINDOW_HEIGHT : 720\nWINDOW_WIDTH : 1280\nCURRENT_THEME : 0\nREQUEST_TIMEOUT : 5000 ";
    fout.close();
}

template <class T>
void Constants::writeToFile(std::ofstream &fout, const char *key, const T &value)
{
    fout << key << " : " << value << "\n";
}

void Constants::writeConfig()
{
    std::ofstream fout(this->configFilePath.c_str());
    writeToFile(fout, "MAX_URL_SIZE", this->MAX_URL_SIZE);
    writeToFile(fout, "FONT_SIZE", this->FONT_SIZE);
    writeToFile(fout, "WINDOW_HEIGHT", this->WINDOW_HEIGHT);
    writeToFile(fout, "WINDOW_WIDTH", this->WINDOW_WIDTH);
    writeToFile(fout, "REQUEST_TIMEOUT", this->REQUEST_TIMEOUT);
    writeToFile(fout, "CURRENT_THEME", this->CURRENT_THEME);
    writeToFile(fout, "MOVEABLE_WINDOW", this->moveWindow);
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
