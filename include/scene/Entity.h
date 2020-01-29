#pragma once
#include <cal3d.h>
#include "resource/ModelResource.h"
class Entity {
protected:
    int animId;
public:
    float x = 0.0f, y = 0.0f, z = 0.0f;
    CalModel* calModel;
    std::string modelName;
    Entity();
    ~Entity();
    void update();
    void attachModel(const std::string& modelName);
};
