#pragma once

#ifdef _WIN32
#include "platform_specific/windows.hpp"
#define SEP_CHAR "\\"
#elif __APPLE__
#include "platform_specific/apple.hpp"
#define SEP_CHAR "/"
#else
#include "platform_specific/linux.hpp"
#define SEP_CHAR "/"
#endif

std::string POSTBABY_absolutePath();