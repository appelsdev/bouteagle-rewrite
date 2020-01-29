#include <string>
#include "resource/ResourceManager.h"
#include "view/ui/UIElement.h"
using namespace UI;
Image::Image() {
    type = IMAGE;
}

void Image::assignTexture(const std::string& filename) {
    ResourceManager::LoadTexture(filename);
    texName = filename;
}

const std::string& Image::getTexName() {
    return texName;
}
