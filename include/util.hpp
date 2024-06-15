#pragma once
#include <stdio.h>

#include <filesystem>
#include <string>

#include "config.hpp"
#include "platform_specific.hpp"
#include "yaml-cpp/yaml.h"

/**
 * @return location of application
 **/

const char *formattedTime();

/**
 * @param fileName checks if file exists
 * */
bool fileExists(const std::string &fileName);

/**
 * @param dirName_in checks if directory exists
 * */
bool dirExists(const std::string &dirName_in);

/**
 * @param method type of http method
 * 0 - GET
 * 1 - POST
 * 2 - PUT
 * 3 - DELETE
 * 4 - HEAD
 * 5 - OPTIONS
 *
 * @return string representation of HTTP method
 * */
const char *getHttpMethod(const int method);

/**
 * @param filePath absolute path to file
 * @return const std::string
 * */
const std::string getFileNameFromPath(const std::string &filePath);


/**
 * @brief checks if string ends with substring
 * @param fullString main string
 * @param ending ending substring
 * @return bool
 * 
 */
bool hasEnding(std::string const &fullString, std::string const &ending);