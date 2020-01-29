#include "view/ViewManager.h"
#include "view/ui/UIElement.h"
using namespace UI;
namespace UI {
static Container* s_box = NULL;


void ShowMessageBox(const std::string& text) {
    s_box = new Container();
    s_box->setName("MessageBox");

    UI::Image* img = new UI::Image();
    img->setPos({275, 135});
    img->assignTexture("assets/data/ui/ui_110.tga");
    s_box->addElement(img);

    UI::Text* t = new Text();
    t->setText(text);
    t->setPos({312, 238});
    t->setColor({0.0, 0.0, 0.0, 1.0});
    s_box->addElement(t);

    UI::Button* ok = new UI::Button();
    ok->setName("MessageBox OK");
    ok->assignTexture("assets/data/ui/ui_801.tga");
    ok->setPos({353, 286});
    ok->setBounds({353, 286, 353+120, 286+45});
    s_box->addElement(ok);

    ViewManager::GetActiveView()->addUIElement(s_box);
}

void RemoveMessageBoxes() {
    ViewManager::GetActiveView()->removeUIElement("MessageBox");
}
}
