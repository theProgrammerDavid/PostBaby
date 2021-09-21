#pragma once
#include "config.hpp"
#include "yaml-cpp/yaml.h"
#include <filesystem>
#include <stdio.h>
#include <string>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

/**
 * @return location of application
 **/
std::string absolutePath();
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