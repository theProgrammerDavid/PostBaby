#include "util.hpp"

bool fileExists(const std::string &fileName)
{
  return std::filesystem::exists(fileName);
}

std::string absolutePath()
{
#if defined(_MSC_VER)
  wchar_t path[FILENAME_MAX] = {0};
  GetModuleFileNameW(nullptr, path, FILENAME_MAX);
  std::string tempString = std::filesystem::path(path).string();
  return tempString.substr(0, tempString.length() - (sizeof(PROJECT_NAME) + 3)); // PROJECT_NAME + ".exe"
#else
  char path[FILENAME_MAX];
  ssize_t count = readlink("/proc/self/exe", path, FILENAME_MAX);
  std::string tempString = std::string(std::string(path, (count > 0) ? count : 0));
  return tempString.substr(0, tempString.length() - sizeof(PROJECT_NAME));
#endif
}

bool dirExists(const std::string &dirName_in)
{
  return std::filesystem::exists(dirName_in);
}