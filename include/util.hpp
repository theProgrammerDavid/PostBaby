#pragma once
#include <filesystem>
#include <string>
#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#else 
#include <unistd.h>
#endif

std::filesystem::path abs_exe_path();