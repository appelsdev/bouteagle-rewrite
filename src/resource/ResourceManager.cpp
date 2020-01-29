#include <unordered_map>
#include "system/ExceptionHandler.h"
#include "resource/ResourceManager.h"

static std::unordered_map<std::string, ModelResource*> s_models;
static std::unordered_map<std::string, TextureResource*> s_textures;

namespace ResourceManager {
    void LoadModel(const std::string& filename) {
        ModelResource* model = new ModelResource("assets/" + filename);
        s_models.insert(std::pair<std::string, ModelResource*>(filename, model));
    }

    ModelResource* FindModel(const std::string& filename) {
        try {
            std::unordered_map<std::string, ModelResource*>::iterator it = s_models.find(filename);
            if (s_models.end() == it)
                throw ResourceManagerException("Model resource '" + filename + "' not found.");
            return (*it).second;
        } catch (BoutEagleException& e) {
            ExceptionHandler::Handle(e);
            return NULL;
        }
    }


    TextureResource* LoadTexture(const std::string& filename) {
        // @TODO: Deny filenames that are already loaded
        TextureResource* texture = new TextureResource(filename);
        s_textures.insert(std::pair<std::string, TextureResource*>(filename, texture));
        return texture;
    }

    TextureResource* FindTexture(const std::string& filename) {
        try {
            std::unordered_map<std::string, TextureResource*>::iterator it = s_textures.find(filename);
            if (s_textures.end() == it)
                throw ResourceManagerException("Texture resource '" + filename + "' not found.");
            return (*it).second;
        } catch (BoutEagleException& e) {
            ExceptionHandler::Handle(e);
            return NULL;
        }
    }

    std::unordered_map<std::string, TextureResource*> GetTextures() {
        return s_textures;
    }
}
