#include "util.hpp"

bool fileExists(const std::string &fileName) {
  return std::filesystem::exists(fileName);
}

const char *getHttpMethod(const int method) {
  switch (method) {
    case 0:
      return "GET";
    case 1:
      return "POST";
    case 2:
      return "PUT";
    case 3:
      return "DELETE";
    case 4:
      return "HEAD";
    case 5:
      return "OPTIONS";
    default:
      break;
  }
}

std::string absolutePath() { return POSTBABY_absolutePath(); }

bool dirExists(const std::string &dirName_in) {
  return std::filesystem::exists(dirName_in);
}

const std::string getFileNameFromPath(const std::string &filePath) {
  return filePath.substr(filePath.find_last_of(SEP_CHAR) + 1);
}

bool hasEnding(std::string const &fullString, std::string const &ending)
{
  if (fullString.length() >= ending.length())
  {
    return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
  }
  else
  {
    return false;
  }
}