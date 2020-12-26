#pragma once
#include <iostream>

void glfw_error_callback(int error, const char *description);

class Constants
{
    private:
        /* Here will be the instance stored. */
        static Constants* instance;

        /* Private constructor to prevent instancing. */
        Constants();

    public:
        int MAX_URL_SIZE;
        /* Static access method. */
        static Constants* getInstance();
};
