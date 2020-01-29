#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include "renderer/VBO.h"

VBO::VBO() {
    glGenBuffers(1, &vbo);
}

VBO::~VBO() {
    glDeleteBuffers(1, &vbo);
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}
