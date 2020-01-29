#include "resource/ResourceManager.h"
#include "view/ViewManager.h"
#include "view/ui/UIElement.h"
#include "Log.h"
using namespace UI;

Button::Button() {
    type = BUTTON;
}

void Button::update() {
    if (updateStateAndCheckClicked()) {
        ViewManager::GetActiveView()->doAction(name);
    }
}

void Button::setParts(int parts) {
    this->parts = parts;
}

int Button::getParts() {
    return parts;
}

void Button::setPos(Vec2i pos) {
    TextureResource* tex = ResourceManager::FindTexture(texName);
    bounds.x0 = pos.x;
    bounds.y0 = pos.y;
    bounds.x1 = pos.x + tex->getWidth();
    bounds.y1 = pos.y + (tex->getHeight() / parts);
    this->pos = pos;
}
