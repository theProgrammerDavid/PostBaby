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

char *Tab::getRawBodyRef()
{
    return (char *)this->rawBody.c_str();
}

int Tab::getBodyType()
{
    return currentBodyType;
}

void Tab::setBodyType(const int bodyType)
{
    this->currentBodyType = bodyType;
}
const char *Tab::getResponse()
{
    return this->res.text.c_str();
}

void Tab::constructRequest()
{
    _url = std::move(Url{this->url});
    for (auto i : this->queryParams)
    {
        this->_params.Add({i.getKey(), i.getValue()});
    }
    switch (currentHttpMethod)
    {
    case 0:
        //    GET
        this->res = std::move(cpr::Get(_url, _params));
        break;
    case 1:
        // POST
        break;
    case 2:
        // PUT
        break;

    case 3:
        //  DELETE
        break;

    case 4:
        // HEAD
        break;

    case 5:
        // OPTIONS
        break;
    }
}

void Tab::sendRequest()
{
    this->constructRequest();
}

Tab::Tab(size_t index)
{

    // this->title = "Title" + std::to_string((int)rand());
    this->title = "Untitled" + std::to_string(index);
    this->url = "http://localhost:1234/api";
    // this->response = "This is some response";
    isOpen = true;
    currentHttpMethod = 0;
    currentBodyType = 0;
    // KeyValuePair t;
    // queryParams.push_back(t);
}