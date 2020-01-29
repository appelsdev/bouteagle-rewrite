#pragma once
#include "scene/Entity.h"

class Player: public Entity {
public:
    Player();
    ~Player();
    void walkLeft();
    void walkRight();
    void walkUp();
    void walkDown();
};
