#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include <unordered_map>

#include "util.hpp"
namespace fs = std::filesystem;

class FontManager
{
public:
    std::string selectedFont;
    std::unordered_map<std::string, std::string> fonts;
    bool loadFonts();
    FontManager();
    static FontManager *getInstance();
    void setSelectedFontFromPath(const std::string& font);
    std::string getPathToSelectedFont();

private:
    static FontManager *instance;
    const std::vector<std::string> fontDirs = {
        "C:\\Windows\\Fonts",
        "/usr/fonts",
        "~/.local/share/fonts"
        };
};