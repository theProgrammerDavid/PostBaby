#include "fonts.hpp"

bool fontManager::loadFonts()
{
    for (auto it = fontDirs.begin(); it != fontDirs.end(); ++it)
    {
        if (dirExists(*it))
        {

            //now we iterate through all the files in that dir
            for (const auto &entry : fs::directory_iterator(*it))
            {
                std::cout << entry.path() << std::endl;
            }
        }
    }

    return false;
}

fontManager::fontManager()
{
    
}