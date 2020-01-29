#include "platform/Mouse.h"
#include "view/ui/UIElement.h"
#include "Log.h"
using namespace UI;
bool Hoverable::isHovered() {
    if (Mouse::GetX() >= bounds.left
     && Mouse::GetX() <  bounds.right
     && Mouse::GetY() >= bounds.top
     && Mouse::GetY() <  bounds.bottom) {
        return true;
    }
    return false;
}

void Hoverable::setBounds(Vec4i bounds) {
    this->bounds = bounds;
}

Vec4i Hoverable::getBounds() {
    return bounds;
}
