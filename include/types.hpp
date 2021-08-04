#pragma once
#include <cpr/cprtypes.h>
#include <vector>

class _history
{
public:
    unsigned int id;
    std::string url;

    _history(const unsigned int _id, const std::string &_url) : id(_id), url(_url)
    {
    }
    _history(const _history &&h)
    {
        this->id = h.id;
        this->url = h.url;
    }
};

using History = std::vector<_history>;

_history makeHistory(const unsigned int _id, const std::string &_url);
