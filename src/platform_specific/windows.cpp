#include "platform_specific/windows.hpp"

std::string POSTBABY_absolutePath() {
  wchar_t path[FILENAME_MAX] = {0};
  GetModuleFileNameW(nullptr, path, FILENAME_MAX);
  std::string tempString = std::filesystem::path(path).string();
  return tempString.substr(
      0, tempString.length() -
             (sizeof(PROJECT_NAME) + 3));  // PROJECT_NAME + ".exe"
}

const std::string absoluteFontPath() {
    std::filesystem::path dir(POSTBABY_absolutePath());
    std::filesystem::path fontFile("JetBrainsMono-Medium.ttf");

    const std::filesystem::path fontPath = dir / fontFile;
    const std::string s = fontPath.string();

    return s;
}