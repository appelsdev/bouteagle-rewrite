#include "renderer/ui/UIRenderer.h"
#include "renderer/ui/hud/HUDRenderer.h"

static Sprite* s;

namespace HUDRenderer {
    void Init() {
        // TextureResource* tex = new TextureResource("assets/hud_status_back.tga");
        // tex->createGLTexture();
        // s = new Sprite(tex, 0, 0);
        // UIRenderer::AddSprite(s);
    }

    void Render() {
        UIRenderer::Render();
    }
}
