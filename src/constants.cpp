#include "constants.hpp"

void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
Constants *Constants::instance = 0;

Constants *Constants::getInstance()
{
    if (instance == 0)
    {
        instance = new Constants();
    }

    return instance;
}

Constants::Constants()
{
    MAX_URL_SIZE = 256;
}

Constants *constants = constants->getInstance();