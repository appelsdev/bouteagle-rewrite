#include <string>
#include "math/Types.h"
#include "resource/ResourceManager.h"
#include "view/ui/UIElement.h"
using namespace UI;
Text::Text() {
    type = TEXT;
}

void Text::setColor(Vec4f color) {
    this->color = color;
}

void Text::setText(const std::string& text) {
    this->text = text;
}

const std::string& Text::getText() {
    return text;
}

Vec4f Text::getColor() {
    return color;
}
