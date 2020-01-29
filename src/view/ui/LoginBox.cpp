#include "view/ui/UIElement.h"
using namespace UI;
LoginBox::LoginBox() : Container() {
    UI::Image* msg = new UI::Image();
    msg->setPos({275, 135});
    msg->assignTexture("data/ui/ui_110.tga");
    addElement(msg);

    UI::Animation* anim = new UI::Animation();
    anim->assignTexture("data/ui/ui_111.tga");
    anim->setFrames(10);
    anim->setPos({380, 201});
    addElement(anim);

    UI::Image* text = new Image();
    text->assignTexture("data/ui/ui_112.tga");
    text->setPos({356, 238});
    addElement(text);

    Button* cancel = new Button();
    cancel->setName("Cancel Login");
    cancel->assignTexture("data/ui/ui_802.tga");
    cancel->setPos({353, 286});
    cancel->setBounds({353, 286, 353+120, 286+45});
    addElement(cancel);

}
