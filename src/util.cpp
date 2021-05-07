#include "util.hpp"

bool fileExists(const std::string& fileName){
  return std::filesystem::exists(fileName);
}

std::string absolutePath()
{
#if defined(_MSC_VER)
  wchar_t path[FILENAME_MAX] = {0};
  GetModuleFileNameW(nullptr, path, FILENAME_MAX);
  std::string tempString = std::filesystem::path(path).string();
  return tempString.substr(0, tempString.length() - 6);
#else
  char path[FILENAME_MAX];
  ssize_t count = readlink("/proc/self/exe", path, FILENAME_MAX);
  std::string tempString = std::string(std::string(path, (count > 0) ? count : 0));
  return tempString.substr(0, tempString.length() - 2);
#endif
}

bool dirExists(const std::string &dirName_in)
{
#if _WIN32
  DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;
  return false;

#endif
}