#include "util.hpp"

std::filesystem::path abs_exe_path()
{//TODO: Test on Windows 
#if defined(_MSC_VER)
    wchar_t path[FILENAME_MAX] = {0};
    GetModuleFileNameW(nullptr, path, FILENAME_MAX);
    return std::filesystem::path(path);
#else
    char path[FILENAME_MAX];
    ssize_t count = readlink("/proc/self/exe", path, FILENAME_MAX);
    std::string tempString = std::filesystem::path(std::string(path, (count > 0) ? count : 0));
    return tempString.substr(0, tempString.length() - 2);
#endif
}