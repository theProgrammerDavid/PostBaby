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

std::string absolutePath();
const char *formattedTime();

bool fileExists(const std::string &fileName);
bool dirExists(const std::string &dirName_in);