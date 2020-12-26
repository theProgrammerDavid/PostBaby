#include "tab.hpp"

const char *Tab::getTitle()
{
    return this->title.c_str();
}

const char *Tab::getUrl()
{
    return this->url.c_str();
}

const char *Tab::getResponse()
{
    return this->response.c_str();
}

Tab::Tab()
{
    
    this->title = "Title" + std::to_string((int)rand());
    this->url = "http://localhost:1234/api";
    this->response = "This is some response";
    isOpen = true;
}