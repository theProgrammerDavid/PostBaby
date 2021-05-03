#pragma once
#include <filesystem>
#include <string>
#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#else 
#include <unistd.h>
#endif

std::string absolutePath();
const char* formattedTime();

bool dirExists(const std::string& dirName_in);