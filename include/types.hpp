#pragma once
#include <cpr/cprtypes.h>
#include <vector>

class _history
{
public:
    unsigned int id;
    std::string url;
    std::string method;

    _history(const unsigned int _id, const std::string &_url, const std::string &method) : id(_id), url(_url), method(method)
    {
    }
    _history(const _history &&h)
    {
        this->id = h.id;
        this->url = h.url;
        this->method = h.method;
    }
};

using History = std::vector<_history>;

_history makeHistory(const unsigned int _id, const std::string &_url, const std::string &method);
