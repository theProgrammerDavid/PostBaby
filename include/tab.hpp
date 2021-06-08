#pragma once
#include <string>
#include <iostream>
#include <map>
#include <future>
#include <vector>
#include <cpr/cpr.h>
#include "imgui.h"
#include "util.hpp"
#include "constants.hpp"
#include <cpr/ssl_options.h>
#include <cpr/cprtypes.h>
#include <tidy.h>
#include <tidybuffio.h>
#include <stdio.h>
#include <errno.h>
using namespace cpr;

class KeyValuePair
{
private:
public:
    std::string value;
    std::string description;
    std::string key;
    KeyValuePair();

    void setKey(const std::string &constKey);
    void setKey(const char *constKey);
    int _id;
    bool enable;
};
class Tab
{

private:
    void constructRequest();
    int statusCode;
    float timeElapsed;    

public:
    Parameters _params;
    Response res;
    Header _headers{};
    Payload payload{};

    std::string formattedBody;
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
    void updateTitle();
    int getBodyType();
    int getStatusCode();
    double getTimeElapsed();
    const char *getResponse();
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
