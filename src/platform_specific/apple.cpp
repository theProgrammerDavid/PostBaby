#include "platform_specific/apple.hpp"

std::string POSTBABY_absolutePath() {
  char path[FILENAME_MAX];
  ssize_t count = readlink("/proc/self/exe", path, FILENAME_MAX);
  std::string tempString =
      std::string(std::string(path, (count > 0) ? count : 0));
  return tempString.substr(0, tempString.length() - sizeof(PROJECT_NAME));
}
