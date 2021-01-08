#include "tab.hpp"

KeyValuePair::KeyValuePair()
{
    this->enable = true;
    this->key = "key";
    this->value = "value";
    this->description = "descp";
    this->_id = (int)rand();
}

char *KeyValuePair::getKey()
{
    return (char *)this->key.c_str();
}

void KeyValuePair::setKey(const char *setKey)
{
    this->key = setKey;
}

void KeyValuePair::setKey(const std::string &setKey)
{
    this->key = setKey;
}

char *KeyValuePair::getValue()
{
    return (char *)this->value.c_str();
}

char *KeyValuePair::getDescription()
{
    return (char *)this->description.c_str();
}

bool *KeyValuePair::getEnableRef()
{
    return &this->enable;
}

const char *Tab::getTitle()
{
    return this->title.c_str();
}

const char *Tab::getUrl()
{
    return this->url.c_str();
}

const char *Tab::getResponse()
{
    // return this->response.c_str();
}

char *Tab::getRawBodyRef()
{
    return (char *)this->rawBody.c_str();
}

int Tab::getBodyType()
{
    return currentBodyType;
}

int Tab::setBodyType(const int bodyType)
{
    this->currentBodyType = bodyType;
}

Tab::Tab()
{

    this->title = "Title" + std::to_string((int)rand());
    this->url = "http://localhost:1234/api";
    // this->response = "This is some response";
    isOpen = true;
    currentHttpMethod = 0;
    currentBodyType = 0;
    // KeyValuePair t;
    // queryParams.push_back(t);
}