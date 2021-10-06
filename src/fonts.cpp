#include "fonts.hpp"

std::string FontManager::getPathToSelectedFont() {
  auto it = this->fonts.find(this->selectedFont);
  return it->second;
}

void FontManager::setSelectedFontFromPath(const std::string &path) {
  this->selectedFont = getFileNameFromPath(path);
}

bool FontManager::loadFonts() {
  for (auto _font : this->fontDirs) {
    if (dirExists(_font)) {

      // now we iterate through all the files in that dir
      for (const auto &entry : fs::directory_iterator(_font)) {
        const std::string filePath = entry.path().string();
        const std::string extension =
            filePath.substr(filePath.find_last_of("."));

        if (extension == ".ttf" || extension == ".ttc") {
          const std::string fileName = getFileNameFromPath(filePath);
          this->fonts.insert({fileName, filePath});
        }
      }
    }
  }

  return false;
}

FontManager::FontManager() {}