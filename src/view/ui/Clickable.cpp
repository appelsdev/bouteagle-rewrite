#include "platform/Mouse.h"
#include "view/ui/UIElement.h"
#include "Log.h"
using namespace UI;

int Clickable::getIndex() {
    return index;
}

bool Clickable::updateStateAndCheckClicked() {
    if (isHovered()) {
        if (Mouse::IsPressed(Mouse::LEFT)) {
            clicked = true;
            index = 2;
        } else if (clicked) {
            if (!Mouse::IsHeld(Mouse::LEFT)) {
                clicked = false;
                index = 1;
                return true;
            } else {
                index = 2;
            }
        } else {
            index = 1;
        }
    } else if (clicked && Mouse::IsHeld(Mouse::LEFT)) {
        index = 1;
    } else {
        clicked = false;
        index = 0;
    }
    return false;
}
