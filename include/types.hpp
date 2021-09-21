#pragma once
#include <cpr/cprtypes.h>
#include <vector>

class _history
{
public:
  unsigned int id;
  std::string url;
  int method;

  /**
   * @param _id auto gen unique id
   * @param _url HTTP Target url
   * @param method HTTP request method
   * */
  _history(const unsigned int _id, const std::string &_url,
           const int method)
      : id(_id), url(_url), method(method) {}

  /**
   * @param _history does a copy of member variables
   * */
  _history(const _history &&h)
  {
    this->id = h.id;
    this->url = h.url;
    this->method = h.method;
  }
};

using History = std::vector<_history>;

/**
   * @param _id auto gen unique id
   * @param _url HTTP Target url
   * @param method HTTP request method
   * 
   * @return object of type _history
   * */
_history makeHistory(const unsigned int _id, const std::string &_url,
                     const int method);
