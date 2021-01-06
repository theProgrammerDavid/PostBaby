#pragma once
#include <string>
#include "imgui.h"
#include <map>
#include <cpr/cpr.h>

class KeyValuePair
{

public:
    KeyValuePair();

    char* getKey();
    bool* getEnableRef();
    char* getValue();
    char* getDescription();
    int _id;

    std::string key;
    std::string value;
    std::string description;
    bool enable;
};
class Tab
{

private:
    cpr::Url _url;
    cpr::Parameters _param;
    cpr::Response _resp;

    void construct_request();

public:
    std::string title;
    std::string url;
    cpr::Response r;
    // cpr::Payload();
    // cpr::Parameters();

    std::vector<KeyValuePair> queryParams;

    bool isOpen;

    const char *getTitle();
    const char *getUrl();
    const char *getResponse();
    int current_http_method;
    Tab();
};
