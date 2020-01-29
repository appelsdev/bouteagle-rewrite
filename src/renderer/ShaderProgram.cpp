#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include "renderer/ShaderProgram.h"
#include "Log.h"

void ShaderProgram::checkCompileErrors(GLuint handle) {
    GLint status;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
    if (GL_FALSE == status) {
        GLint length;
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
        char* logStr = (char*)malloc(length);
        glGetShaderInfoLog(handle, length, NULL, logStr);
        Log::Log(Log::FATAL, "Shader compilation failed:\n%s", logStr);
        free(logStr);
    }
}

void ShaderProgram::checkLinkErrors() {
    GLint status;
    glGetProgramiv(this->program, GL_LINK_STATUS, &status);
    if (GL_FALSE == status) {
        // allocate the OpenGL log string
        GLint length;
        glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &length);
        char* logStr = (char*)malloc(length);
        // retrieve log
        glGetProgramInfoLog(this->program, length, NULL, logStr);
        // print error
        Log::Log(Log::FATAL, "Shader linkage failed:\n%s", logStr);
        // free log string
        free(logStr);
    }

    int error;
    if ((error = glGetError()) != GL_NO_ERROR) {
        Log::Log(Log::FATAL, "Linkage error code: %xh.", error);
        return;
    }
}

bool ShaderProgram::checkFramebufferStatus() {
    GLenum status = (GLenum)glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    switch(status) {
    case GL_FRAMEBUFFER_COMPLETE_EXT:
        return true;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
        Log::Log(Log::FATAL, "Framebuffer incomplete, incomplete attachment");
        return false;
    case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
        Log::Log(Log::FATAL, "Unsupported framebuffer format");
        return false;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
        Log::Log(Log::FATAL, "Framebuffer incomplete, missing attachment");
        return false;
    case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
        Log::Log(Log::FATAL, "Framebuffer incomplete, attached images must have same dimensions");
        return false;
    case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
        Log::Log(Log::FATAL, "Framebuffer incomplete, attached images must have same format");
        return false;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
        Log::Log(Log::FATAL, "Framebuffer incomplete, missing draw buffer");
        return false;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
        Log::Log(Log::FATAL, "Framebuffer incomplete, missing read buffer");
        return false;
    }
    return false;
}



ShaderProgram::ShaderProgram() {
    this->program = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(this->program);
}

void ShaderProgram::use() {
    glUseProgram(this->program);
}

void ShaderProgram::addStage(const char* source, ShaderStage stage) {
    // Compile shader
    GLuint shader = glCreateShader(stage);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    checkCompileErrors(shader);

    // Attach shader to program
    glAttachShader(this->program, shader);
    VERTEX == stage ? this->vert = shader : this->frag = shader;
}

void ShaderProgram::link() {
    glLinkProgram(this->program);
    checkLinkErrors();
    if (this->frag) { glDetachShader(this->program, this->frag); glDeleteShader(this->frag); }
    if (this->vert) { glDetachShader(this->program, this->vert); glDeleteShader(this->vert); }
}
