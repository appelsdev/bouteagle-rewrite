#pragma once
#include <string>
#include <cal3d.h>
using namespace cal3d;

class ModelResource {
private:
    void parseModelConfig(const std::string& filename);
public:
    ModelResource(const std::string& filename);
    ~ModelResource();
    CalCoreModel* coreModel;
    float scale;
};
