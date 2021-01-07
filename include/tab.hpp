#pragma once
#include <string>
#include "imgui.h"
#include <map>
#include <cpr/cpr.h>

class KeyValuePair
{
private:
    std::string key;
    std::string value;
    std::string description;
    bool enable;

public:
    KeyValuePair();

    char *getKey();
    void setKey(const std::string &constKey);
    void setKey(const char *constKey);
    bool *getEnableRef();
    char *getValue();
    char *getDescription();
    int _id;
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
    std::vector<KeyValuePair> headers;

    bool isOpen;

    const char *getTitle();
    const char *getUrl();
    const char *getResponse();
    int current_http_method;
    Tab();
};
