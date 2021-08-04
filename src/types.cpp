#include "types.hpp"

_history makeHistory(const unsigned int _id, const std::string &_url)
{
    _history h(_id, _url);
    return h;
}