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
bool Tab::isHttps()
{
    return this->url.rfind("https", 0) == 0;
}

void Tab::sendRequest()
{

    this->constructRequest();

    switch (this->currentHttpMethod)
    {
    case 0: //GET REQUEST
        if (this->isHttps())
            res = cpr::Get(Url{this->url.c_str()}, _params, this->_headers, sslOpts, Timeout{constants->REQUEST_TIMEOUT});
        else
            res = cpr::Get(Url{this->url.c_str()}, _params, this->_headers, Timeout{constants->REQUEST_TIMEOUT});

        break;
    case 1: //POST REQUEST
        if (this->isHttps())
            res = cpr::Post(Url{this->url.c_str()}, this->payload, sslOpts, _params, this->_headers, Timeout{constants->REQUEST_TIMEOUT});
        else
            res = cpr::Post(Url{this->url.c_str()}, this->payload, _params, this->_headers, Timeout{constants->REQUEST_TIMEOUT});

        break;

    case 2:
        // PUT
        if (this->isHttps())
            res = cpr::Put(Url{this->url.c_str()}, _params, this->_headers, sslOpts, Timeout{constants->REQUEST_TIMEOUT});
        else
            res = cpr::Put(Url{this->url.c_str()}, _params, this->_headers, Timeout{constants->REQUEST_TIMEOUT});

        break;

    case 3:
        // DELETE
        if (this->isHttps())
            res = cpr::Delete(Url{this->url.c_str()}, _params, this->_headers, sslOpts, Timeout{constants->REQUEST_TIMEOUT});
        else
            res = cpr::Delete(Url{this->url.c_str()}, Timeout{constants->REQUEST_TIMEOUT});

        break;

    case 4:
        // HEAD
        if (this->isHttps())
            res = cpr::Head(Url{this->url.c_str()}, _params, this->_headers, sslOpts, Timeout{constants->REQUEST_TIMEOUT});
        else
            res = cpr::Head(Url{this->url.c_str()}, _params, this->_headers, Timeout{constants->REQUEST_TIMEOUT});

        break;

    case 5:
        // OPTIONS
        if (this->isHttps())
            res = cpr::Options(Url{this->url.c_str()}, _params, this->_headers, sslOpts, Timeout{constants->REQUEST_TIMEOUT});
        else
            res = cpr::Options(Url{this->url.c_str()}, _params, this->_headers, Timeout{constants->REQUEST_TIMEOUT});

        break;
    };
}

void Tab::updateTitle()
{
    this->title = this->url + "##" + std::to_string(rand());
}
double Tab::getTimeElapsed()
{
    return res.elapsed;
}
int Tab::getStatusCode()
{
    return res.status_code;
}
Tab::Tab(size_t index)
{
    sslOpts = Ssl(ssl::CaPath{absolutePath() + "ca.cer"}, ssl::CertFile{absolutePath() + "client.cer"},
                  ssl::KeyFile{absolutePath() + "client.key"}, ssl::VerifyPeer{false},
                  ssl::VerifyHost{false}, ssl::VerifyStatus{false});
    this->title = "Untitled" + std::to_string(index);
    this->url = "http://localhost:1234";
    isOpen = true;
    statusCode = 0;
    currentHttpMethod = 0;
    currentBodyType = 0;
    timeElapsed = 0;
}