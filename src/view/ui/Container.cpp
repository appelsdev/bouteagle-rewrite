#include "view/ui/UIElement.h"
using namespace UI;
Container::Container() {
    type = CONTAINER;
}

std::vector<Element*> Container::getChildren() {
    return children;
}

void Container::addElement(Element* e) {
    children.insert(children.end(), e);
}

void Container::update() {
    for (Element* e : children) {
        e->update();
    }
}

void Container::destroy() {
    for (int i = 0; i < children.size(); i++) {
        children[i]->destroy();
        children.erase(children.begin() + i);
    }
}
