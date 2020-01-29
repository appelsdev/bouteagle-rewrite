#pragma once
#include <vector>
#include <string>
#include "network/Packet.h"
#include "view/ui/UIElement.h"
#include "acegames/acegames.h"

class View {
private:
    std::vector<UI::Element*> uiElements;
    std::vector<UI::EditBox*> editBoxes;
    std::vector<UI::EditBox*>::iterator editBoxIterator = editBoxes.begin();
    UI::Image* background = NULL;

public:
    virtual void prepare() {};
    virtual void cleanup() {};
    virtual void doAction(const std::string& name) {};
    virtual void handlePacket(AcePacket p) {};

    // UI elements
    void addUIElement(UI::Element* e);
    void removeUIElement(const std::string& name);
    void updateUIElements();
    const std::vector<UI::Element*>& getUIElements() const;
    const std::vector<UI::Element*> getPersistantUIElements() const;
    void setBackground(const std::string& filename);

    std::string getEditBoxValue(const std::string& name);
    void selectEditBox(const std::string& name);
    UI::EditBox* getSelectedEditBox();


    void handleChar(int scancode);

    void processPackets();


    std::string name;

};
