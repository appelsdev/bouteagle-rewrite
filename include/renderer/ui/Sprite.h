#pragma once
#include "resource/TextureResource.h"

// Sprite base class.
class Sprite {
public:
    Sprite(TextureResource* tex, int x, int y);
    void render();

    int x, y;
private:
    TextureResource* tex;
};
