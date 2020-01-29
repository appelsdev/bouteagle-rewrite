#pragma once
#include <GL/gl.h>
#include <GL/glext.h>

enum ShaderStage {
    FRAGMENT = GL_FRAGMENT_SHADER_ARB, VERTEX = GL_VERTEX_SHADER_ARB
};

class ShaderProgram {
protected:
    GLuint frag, vert, program;

    void checkCompileErrors(GLuint handle);
    void checkLinkErrors();
    bool checkFramebufferStatus();
public:
    ShaderProgram();
    ~ShaderProgram();
    void use();
    void addStage(const char* source, ShaderStage stage);
    void link();
    GLuint getProgram() { return program; };
};
