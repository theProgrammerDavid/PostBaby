#include "types.hpp"

_history makeHistory(const unsigned int _id, const std::string &_url,
                     const std::string &method) {
  _history h(_id, _url, method);
  return h;
}