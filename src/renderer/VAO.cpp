#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include "renderer/VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &vao);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &vao);
}

void VAO::bind() {
    glBindVertexArray(vao);
}
