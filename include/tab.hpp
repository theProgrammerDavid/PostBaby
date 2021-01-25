#pragma once
#include <string>
#include <iostream>
#include <map>
#include <future>
#include <vector>
#include <cpr/cpr.h>
#include <cpr/ssl_options.h>
#include "imgui.h"
#include "util.hpp"
#include "constants.hpp"
using namespace cpr;
extern std::unique_ptr<Constants> constants;

class KeyValuePair
{
private:


public:
    std::string value;
    std::string description;
    bool enable;
    std::string key;
    KeyValuePair();


    void setKey(const std::string &constKey);
    void setKey(const char *constKey);
    int _id;
};
class Tab
{

private:


    void constructRequest();
    // Url _url;
    Parameters _params;
    Response res;

public:
    std::string title;
    std::string url;
    std::string rawBody;
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
    // 
    void sendRequest();
    int getBodyType();
    const char* getResponse();
    void setBodyType(const int bodyType);



    std::vector<KeyValuePair> queryParams;
    std::vector<KeyValuePair> headers;
    std::vector<KeyValuePair> urlParams;
    std::vector<KeyValuePair> formData;

    bool isOpen;
    // char* getRawBodyRef();
    // const char *getTitle();
    // const char *getUrl();
    
    int currentHttpMethod;
    int currentBodyType;
    Tab(size_t index);
};
