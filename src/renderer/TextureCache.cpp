#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <GL/gl.h>
#include "Log.h"
#include "resource/ResourceManager.h"
#include "renderer/TextureCache.h"

namespace TextureCache {
    void Init() {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        Build();
    }

    void Build() {
        for (auto const& it : ResourceManager::GetTextures()) {
            // Log::Log(Log::INFO, "%s", it.first.c_str());
            TextureResource* tex = it.second;
            tex->createGLTexture();
        }
    }

    void RebuildWhereNecessary() {
        for (auto const& it : ResourceManager::GetTextures()) {
            TextureResource* tex = it.second;
            if (GL_INVALID_VALUE == tex->texId)
                tex->createGLTexture();
        }
    }
}
