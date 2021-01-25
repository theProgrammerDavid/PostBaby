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
    for (auto i : this->queryParams)
    {
        if(i.enable)
        this->_params.Add({i.key, i.value});
    }
    // std::thread t;
    // std::string baseDirPath = abs_exe_path();
    // std::string serverCertPath = baseDirPath + "server.cer";
    // std::string serverKeyPath = baseDirPath + "server.key";
    // SslOptions sslOpts =
    //     Ssl(ssl::CaPath{baseDirPath + "ca.cer"}, ssl::CertFile{baseDirPath + "client.cer"},
    //         ssl::KeyFile{baseDirPath + "client.key"}, ssl::VerifyPeer{false},
    //         ssl::VerifyHost{false}, ssl::VerifyStatus{false});

    switch (this->currentHttpMethod)
    {
    case 0:
        // t = std::thread([&] {
            // res = cpr::Get(_url, sslOpts, Verbose{}, _params, Timeout{constants->REQUEST_TIMEOUT});
            res = cpr::Get(Url{this->url.c_str()}, _params, Timeout{constants->REQUEST_TIMEOUT});
        // });
        // t.detach();
        break;
    case 1:
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

    // if (this->currentHttpMethod == 0)
    // {
    //     std::cout << "starting\n";
    //     std::thread t([&] {
    //         res = cpr::Get(_url, _params);
    //         std::cout << "done\n";
    //     });
    //     t.detach();
    //     std::cout << "finished\n";
    // }
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