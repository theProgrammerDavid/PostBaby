#include "util.hpp"

std::string abs_exe_path()
{
#if defined(_MSC_VER)
    wchar_t path[FILENAME_MAX] = {0};
    GetModuleFileNameW(nullptr, path, FILENAME_MAX);
    std::string tempString = std::filesystem::path(path).string();
    return tempString.substr(0, tempString.length()-6);
#else
    char path[FILENAME_MAX];
    ssize_t count = readlink("/proc/self/exe", path, FILENAME_MAX);
    std::string tempString = std::filesystem::path(std::string(path, (count > 0) ? count : 0));
    return tempString.substr(0, tempString.length() - 2);
#endif
}
