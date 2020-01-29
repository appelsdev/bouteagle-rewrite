#pragma once
#include <vector>
#include "scene/Entity.h"
#include "scene/Player.h"

class Scene {
private:
    Player* activePlayer;
    std::vector<Entity*> entities;
public:
    Scene();
    ~Scene();
    void update();
    std::vector<Entity*>* getEntities();
    Player* getPlayer();
};
