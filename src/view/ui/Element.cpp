#include "view/ui/UIElement.h"
using namespace UI;

/*******************************************************************************
 * Getters
 ******************************************************************************/

/**
 * @return ElementType The type of the element.
 */
ElementType Element::getType() {
    return type;
}

/**
 * @return Vec2i Position of the UI element.
 */
Vec2i Element::getPos() {
    return pos;
}

/**
 * @return const std::string& The name of the element.
 */
const std::string& Element::getName() {
    if (name.empty())
        name = "<Unnamed>";
    return name;
}

/**
 * @return bool Whether the element will be kept after switching views.
 */
bool Element::isPersistant() {
    return persistant;
}


/*******************************************************************************
 * Setters
 ******************************************************************************/

/**
 * @param Vec2i
 */
void Element::setPos(Vec2i pos) {
    this->pos = pos;
}

/**
 * @param const std::string&
 */
void Element::setName(const std::string& name) {
    this->name = name;
}

/**
 * @param bool
 */
void Element::setPersistant(bool x) {
    persistant = x;
}
