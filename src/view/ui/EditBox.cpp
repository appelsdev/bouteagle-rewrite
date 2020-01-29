#include "view/ViewManager.h"
#include "view/ui/UIElement.h"
#include "Log.h"
using namespace UI;
EditBox::EditBox() {
    type = EDITBOX;
}

/*******************************************************************************
 * Getters
 ******************************************************************************/
int EditBox::getMaxChars() {
    return maxChars;
}

bool EditBox::isProtected() {
    return protect;
}

const std::string& EditBox::getText() {
    return text;
}

/*******************************************************************************
 * Setters
 ******************************************************************************/
void EditBox::setMaxChars(int num) {
    maxChars = num;
}

void EditBox::setProtected(bool protect) {
    this->protect = protect;
}

/*******************************************************************************
 * Methods
 ******************************************************************************/
void EditBox::handleChar(int scancode) {
    switch (scancode) {
    case 0x08: // backspace
        text.erase(text.end() - 1);
        break;
    case 0x0A: // linefeed
        Log::Log(Log::INFO, "LINEFEED");
        break;
    case 0x1B: // escape
        break;
    case 0x0D: // carriage return
        ViewManager::GetActiveView()->doAction(name);
        break;
    default: // displayable characters
        if (text.size() < maxChars)
            text += scancode;
        break;
    }
}

void EditBox::update() {
    updateStateAndCheckClicked();
    if (clicked) {
        ViewManager::GetActiveView()->selectEditBox(name);
    }
}

void EditBox::clearText() {
    text.clear();
}
