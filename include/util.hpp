#pragma once
#include <filesystem>
#include <string>
#include <stdio.h>
#ifdef _Win32
#include <unistd.h>
#endif

std::filesystem::path abs_exe_path();