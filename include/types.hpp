#pragma once
#include <cpr/cprtypes.h>
#include <vector>

class request
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
  request(const unsigned int _id, const std::string &_url,
           const int method)
      : id(_id), url(_url), method(method) {}
};

