#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include "Log.h"
#include "platform/GLContext.h"

static HGLRC s_context;

namespace GLContext {
    void Create() {
        // create context
        HDC dc = Window::GetHdc();
        s_context = wglCreateContext(dc);
        if (!s_context)
            Log::LogWinApi(Log::FATAL);

        // make context current
        if (!wglMakeCurrent(dc, s_context))
            Log::LogWinApi(Log::FATAL);

        // verify min. OpenGL version
        GLint major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        if (!(major >= 3 && minor >= 0)) {
            Log::Log(Log::WARNING, "Outdated OpenGL version %i,%i.", major, minor);
        }
        Log::Log(Log::INFO, "Using OpenGL version %i,%i.", major, minor);

        // init GLEW
        GLenum err = glewInit();
        if (GLEW_OK != err)
            Log::Log(Log::FATAL, "GLEW failed to initialise.");

        // setup GL parameters
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Destroy() {
        wglMakeCurrent(wglGetCurrentDC(), NULL);
        wglDeleteContext(s_context);
    }
}
