#pragma once
#include <string>
#include <cpr/cpr.h>
#include "imgui.h"
#include <iostream>
#include <map>
#include <vector>
using namespace cpr;
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


    void constructRequest();

public:
    enum BodyType
    {
        BODY_NONE,
        BODY_FORM_DATA,
        BODY_URL_ENCODED,
        BODY_RAW,
        BODY_BINARY,
        BODY_GRAPHQL
    };
    //  networking stuff
    Url _url;
    Parameters _params;
    Response res;
    // 
    void sendRequest();
    int getBodyType();
    const char* getResponse();
    void setBodyType(const int bodyType);

    std::string title;
    std::string url;
    std::string rawBody;


    std::vector<KeyValuePair> queryParams;
    std::vector<KeyValuePair> headers;
    std::vector<KeyValuePair> urlParams;
    std::vector<KeyValuePair> formData;

    bool isOpen;
    char* getRawBodyRef();
    const char *getTitle();
    const char *getUrl();
    
    int currentHttpMethod;
    int currentBodyType;
    Tab(size_t index);
};
