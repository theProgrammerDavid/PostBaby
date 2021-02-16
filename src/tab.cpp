#include "tab.hpp"

KeyValuePair::KeyValuePair()
{
    this->enable = true;
    this->key = "key";
    this->value = "value";
    this->description = "descp";
    this->_id = (int)rand();
}

void KeyValuePair::setKey(const char *setKey)
{
    this->key = setKey;
}

void KeyValuePair::setKey(const std::string &setKey)
{
    this->key = setKey;
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
    // return this->asyncRes.get().text.c_str();
}

void Tab::constructRequest()
{
    this->_params = Parameters{};
    this->payload = Payload{};
    this->_headers = Header{};

    for (auto i : this->queryParams)
    {
        if (i.enable)
            this->_params.Add({i.key, i.value});
    }

    for (auto i : this->headers)
    {
        if (i.enable)
        {
            this->_headers.insert({i.key, i.value});
        }
    }
    switch (this->currentHttpMethod)
    {
    case 0: //GET REQUEST

        break;
    case 1: //POST REQUEST
        for (auto i : this->formData)
        {
            if (i.enable)
                this->payload.Add({i.key, i.value});
        }
        break;

    case 2:
        break;

    case 3:
        break;

    case 4:
        break;

    case 5:
        break;
    };
}

void Tab::sendRequest()
{
    this->constructRequest();
    switch (this->currentHttpMethod)
    {
    case 0: //GET REQUEST
        res = cpr::Get(Url{this->url.c_str()}, _params, Timeout{constants->REQUEST_TIMEOUT});
        break;
    case 1: //POST REQUEST
        res = cpr::Post(Url{this->url.c_str()}, this->payload, _params, this->_headers, Timeout{constants->REQUEST_TIMEOUT});

        break;

    case 2:
        // PUT
        break;

    case 3:
        // DELETE
        break;

    case 4:
        // HEAD
        res = cpr::Head(Url{this->url.c_str()}, Timeout{constants->REQUEST_TIMEOUT});
        break;

    case 5:
        // OPTIONS
        break;
    };
}

Tab::Tab(size_t index)
{

    this->title = "Untitled" + std::to_string(index);
    this->url = "http://localhost:1234";
    isOpen = true;
    currentHttpMethod = 0;
    currentBodyType = 0;
}