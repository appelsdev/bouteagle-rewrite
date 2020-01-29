#pragma once
#include <unordered_map>
#include <string>
#include "resource/ModelResource.h"
#include "resource/TextureResource.h"

namespace ResourceManager {
    void LoadModel(const std::string& filename);
    ModelResource* FindModel(const std::string& filename);

    TextureResource* LoadTexture(const std::string& filename);
    TextureResource* FindTexture(const std::string& filename);
    std::unordered_map<std::string, TextureResource*> GetTextures();
}
