#pragma once
#include <iostream>
#include <memory>

void glfw_error_callback(int error, const char *description);

class Constants
{
    private:
        /* Here will be the instance stored. */
        // static Constants* instance;

        /* Private constructor to prevent instancing. */
        // Constants();

    public:
        Constants();
        int MAX_URL_SIZE;
        const char *request_type[6] = {"GET", "POST", "PUT", "DELETE", "HEAD", "OPTIONS"};

        /* Static access method. */
        // static Constants* getInstance();
};
