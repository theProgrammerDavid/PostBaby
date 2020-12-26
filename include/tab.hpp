#pragma once
#include <string>
#include "imgui.h"
#include <map>

class Tab
{

private:
public:
    std::string title;
    std::string url;
    std::string response;

    std::map<std::string, std::string> params;
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> body;

    bool isOpen;

    const char *getTitle();
    const char *getUrl();
    const char *getResponse();

    Tab();
};
