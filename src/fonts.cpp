#include "fonts.hpp"

std::string FontManager::getPathToSelectedFont(){
    auto it = this->fonts.find(this->selectedFont);
    return it->second;
}

void FontManager::setSelectedFontFromPath(const std::string& path){
#ifdef _WIN32
    const std::string sepChar = "\\";
#else
    const std::string sepChar = "/";
#endif

    // const std::string fileName = path.substr(path.find_last_of(sepChar)+1);
    this->selectedFont = path.substr(path.find_last_of(sepChar)+1);
    // auto it = this->fonts.find(fileName);

    // if(it != this->fonts.end()){
    //     this->selectedFont = 
    // }
}

bool FontManager::loadFonts()
{
#ifdef _WIN32
    const std::string sepChar = "\\";
#else
    const std::string sepChar = "/";
#endif

    for (auto _font:this->fontDirs)
    {
        if (dirExists(_font))
        {

            //now we iterate through all the files in that dir
            for (const auto &entry : fs::directory_iterator(_font))
            {
                const std::string filePath = entry.path().string();
                const std::string extension = filePath.substr(filePath.find_last_of("."));

                if (extension == ".ttf" || extension == ".ttc")
                {
                    const std::string fileName = filePath.substr(filePath.find_last_of(sepChar)+1);
                    this->fonts.insert({fileName, filePath});
                }
            }
        }
    }
    return false;
}

FontManager::FontManager()
{
}