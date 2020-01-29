#include "system/ExceptionHandler.h"
#include "resource/ResourceManager.h"
#include "view/ui/UIElement.h"
#include "view/View.h"

void View::addUIElement(UI::Element* e) {
    uiElements.insert(uiElements.end(), e);
    if (e->getType() == UI::EDITBOX) {
        editBoxes.insert(editBoxes.end(), (UI::EditBox*)e);
    }
}

void View::removeUIElement(const std::string& name) {
    UI::Element* e = NULL;
    std::vector<UI::Element*>::iterator it = uiElements.begin();
    while (it != uiElements.end()) {
        e = *it;
        if (e->getName() == name) {
            e->destroy();
            it = uiElements.erase(it);
        } else ++it;
    }
}

std::string View::getEditBoxValue(const std::string& name) {
    UI::EditBox* box = NULL;
    for (UI::EditBox* b : editBoxes) {
        box = (b->getName() == name) ? b : box;
    }
    return box->getText();
}

void View::selectEditBox(const std::string& name) {
    UI::EditBox* box = NULL;
    for (editBoxIterator = editBoxes.begin(); editBoxIterator != editBoxes.end(); ++editBoxIterator) {
        box = *editBoxIterator;
        if (box->getName() == name)
            break;
    }
    if (!box) {
        THROW_EXCEPTION(ViewException, "Unable to select edit box '" + name + "'.");
    }
}

void View::updateUIElements() {
    for (UI::Element* e : uiElements) {
        e->update();
    }
}

const std::vector<UI::Element*>& View::getUIElements() const {
    return uiElements;
}

const std::vector<UI::Element*> View::getPersistantUIElements() const {
    std::vector<UI::Element*> elements;
    for (UI::Element* e : uiElements) {
        if (e->isPersistant()) {
            Log::Log(Log::INFO, "Persistant element %s" , e->getName().c_str());
            elements.insert(elements.begin(), e);
        }
    }
    return elements;
}

void View::handleChar(int scancode) {
    if (!*editBoxIterator) return;
    if (0x09 == scancode) { // tab
        // select next edit box
        editBoxIterator++;
        if (editBoxIterator == editBoxes.end())
            editBoxIterator = editBoxes.begin();
    } else {
        ((UI::EditBox*)*editBoxIterator)->handleChar(scancode);
    }
}

UI::EditBox* View::getSelectedEditBox() {
    return (editBoxIterator == editBoxes.end()) ? NULL : *editBoxIterator;
}

void View::setBackground(const std::string& filename) {
    if (!background) {
        background = new UI::Image();
    }
    background->setName("Background");
    background->setPos({0, 0});
    background->assignTexture(filename);
    addUIElement(background);
}

void View::processPackets() {
    const char* err = Ace_GetErrorString();
    if (NULL != err)
        Log::Log(Log::FATAL, err);

    AcePacket packet;
    while (Ace_Poll(&packet)) {
        handlePacket(packet);
    }
}
