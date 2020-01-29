#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/gl.h>
#include "system/ExceptionHandler.h"
#include "resource/TGA.h"
#include "resource/TextureResource.h"

TextureResource::TextureResource(const std::string& filename) {
    tga = new TGA();
    tga->readFile(("assets/" + filename).c_str());
}

TextureResource::~TextureResource() {
    delete tga;
    // TODO: delete texture? (make sure itll be done in the render thread)
}

void TextureResource::createGLTexture() {
    glGenTextures(1, &this->texId);
    glBindTexture(GL_TEXTURE_2D, this->texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLint format = (3 == tga->getDepth()) ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, tga->getWidth(), tga->getHeight(), 0, format, GL_UNSIGNED_BYTE, (char*)tga->getPointer());
}

void TextureResource::bind() {
    glBindTexture(GL_TEXTURE_2D, texId);
}

int TextureResource::getWidth() {
    return tga->getWidth();
}

int TextureResource::getHeight() {
    return tga->getHeight();
}
