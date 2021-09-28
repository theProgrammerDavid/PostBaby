#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include <unordered_map>

#include "util.hpp"
namespace fs = std::filesystem;

class fontManager
{
public:
    enum class operatingSystem
    {
        WINDOWS,
        MACOS,
        LINUX
    };

    std::unordered_map<std::string, std::string> fonts;
    bool loadFonts();
    fontManager();

private:
    const std::vector<std::string> fontDirs = {
        "C:\\Windows\\Fonts",
        "/usr/fonts"};

#ifdef _WIN32
    operatingSystem os = operatingSystem::WINDOWS;
#elif __APPLE__
    operatingSystem os = operatingSystem::APPLE;
#else
    operatingSystem os = operatingSystem::LINUX;
#endif
};