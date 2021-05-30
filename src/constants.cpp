#include "constants.hpp"
namespace YAML
{
    template <>
    struct convert<ImVec4>
    {
        static Node encode(const ImVec4 &rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            return node;
        }

        static bool decode(const Node &node, ImVec4 &rhs)
        {
            if (!node.IsSequence() || node.size() != 4)
            {
                return false;
            }

            rhs.x = node[0].as<double>();
            rhs.y = node[1].as<double>();
            rhs.z = node[2].as<double>();
            rhs.w = node[3].as<double>();
            return true;
        }
    };
}

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
        try
        {
            config = YAML::LoadFile(this->configFilePath.c_str());
            if (config["PATH_TO_FONT"])
            {
                this->PATH_TO_FONT = config["PATH_TO_FONT"].as<std::string>();
            }
            // else
            // {
            //     this->PATH_TO_FONT = absolutePath() + "/JetBrainsMono-Medium.ttf";
            // }

            if (config["HTML_INDENT"])
            {
                this->htmlIndent = config["HTML_INDENT"].as<int>();
            }

            if (config["MOVEABLE_WINDOW"])
            {
                this->moveWindow = config["MOVEABLE_WINDOW"].as<int>();
                this->updateWindowFlags();
            }
            if (config["MAX_URL_SIZE"])
            {
                this->MAX_URL_SIZE = config["MAX_URL_SIZE"].as<int>();
            }
            if (config["FONT_SIZE"])
            {
                this->FONT_SIZE = config["FONT_SIZE"].as<float>();
            }
            if (config["WINDOW_HEIGHT"])
            {
                this->WINDOW_HEIGHT = config["WINDOW_HEIGHT"].as<int>();
            }
            if (config["WINDOW_WIDTH"])
            {
                this->WINDOW_WIDTH = config["WINDOW_WIDTH"].as<int>();
            }
            if (config["REQUEST_TIMEOUT"])
            {
                this->REQUEST_TIMEOUT = config["REQUEST_TIMEOUT"].as<int>();
            }
            if (config["CURRENT_THEME"])
            {
                this->CURRENT_THEME = config["CURRENT_THEME"].as<int>();
            }
            if(config["BACKGROUND"]){
                this->clear_color = config["BACKGROUND"].as<ImVec4>();
            }
            this->configError = false;
        }
        catch (YAML::Exception e)
        {
            std::cerr << "Error in yaml file";
            this->configError = true;
            std::cout << this->configError;
        }
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
    //this->isOnline = false;
    //this->highDPIscaleFactor = 1.0;
    this->configError = false;
    this->htmlIndent = true;
    this->clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

bool Constants::configFileExists()
{
    return fileExists(this->configFilePath.c_str());
}

void Constants::createConfigFile()
{
    std::ofstream fout(this->configFilePath.c_str());
    fout << "MAX_URL_SIZE: 256\nHTML_INDENT : 0\nMOVEABLE_WINDOW : 1\nFONT_SIZE : 18.0\nWINDOW_HEIGHT : 720\nWINDOW_WIDTH : 1280\nCURRENT_THEME : 0\nREQUEST_TIMEOUT : 5000 ";
    fout << "\nBACKGROUND : [ 0.45, 0.55, 0.60, 1.00 ]";
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
    writeToFile(fout, "HTML_INDENT", this->htmlIndent);
    writeToFile(fout, "FONT_SIZE", this->FONT_SIZE);
    writeToFile(fout, "WINDOW_HEIGHT", this->WINDOW_HEIGHT);
    writeToFile(fout, "WINDOW_WIDTH", this->WINDOW_WIDTH);
    writeToFile(fout, "REQUEST_TIMEOUT", this->REQUEST_TIMEOUT);
    writeToFile(fout, "CURRENT_THEME", this->CURRENT_THEME);
    writeToFile(fout, "MOVEABLE_WINDOW", this->moveWindow);
    fout << "BACKGROUND : [ "<<this->clear_color.x<<" , "<<this->clear_color.y<<" , "<<this->clear_color.z<<" , "<<this->clear_color.w<<" ] ";
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
