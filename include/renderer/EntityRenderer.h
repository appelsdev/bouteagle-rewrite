#pragma once
#include "scene/Scene.h"

class EntityRenderer {
private:
public:
    EntityRenderer(Scene* scene);
    ~EntityRenderer();
    void render(Scene* scene);
};
