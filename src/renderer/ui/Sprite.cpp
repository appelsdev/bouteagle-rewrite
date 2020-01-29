#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <GL/gl.h>
#include "resource/TextureResource.h"
#include "renderer/ui/Sprite.h"

/**
 * Constructor.
 *
 * @param TextureResource* tex The texture to use.
 * @param int              x   Initial X position.
 * @param int              y   Initial Y position.
 */
Sprite::Sprite(TextureResource* tex, int x, int y) {
    this->tex = tex;
    this->x   = x;
    this->y   = y;
}

/**
 * Draws the sprite on the screen.
 */
void Sprite::render() {
    this->tex->bind();
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();
}
