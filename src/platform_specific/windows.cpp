#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

std::string POSTBABY_absolutePath() {
  wchar_t path[FILENAME_MAX] = {0};
  GetModuleFileNameW(nullptr, path, FILENAME_MAX);
  std::string tempString = std::filesystem::path(path).string();
  return tempString.substr(
      0, tempString.length() -
             (sizeof(PROJECT_NAME) + 3));  // PROJECT_NAME + ".exe"
}