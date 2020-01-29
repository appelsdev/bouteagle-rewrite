#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <GL/gl.h>
#include <string>
#include "resource/TGA.h"

class TextureResource {
private:
    TGA* tga;
public:
    GLuint texId = GL_INVALID_VALUE;
    TextureResource(const std::string& filename);
    ~TextureResource();
    void createGLTexture();
    void bind();
    int getWidth();
    int getHeight();
};
