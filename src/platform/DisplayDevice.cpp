#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Log.h"
#include "platform/Window.h"
#include "platform/DisplayDevice.h"

static const PIXELFORMATDESCRIPTOR s_PFD = {
    sizeof(PIXELFORMATDESCRIPTOR),
    1, // version

    PFD_SUPPORT_OPENGL | // must support OpenGL
    PFD_DRAW_TO_WINDOW | // must support window drawing
    PFD_DOUBLEBUFFER,    // must support double buffering

    PFD_TYPE_RGBA, // RGBA format
    32, // 32-bit color depth
    0, 0, 0, 0, 0, 0, // skip color bits
    0, // no alpha buffer
    0, // skip shift bit

    0, // no accumulation buffer
    0, 0, 0, 0, // skip accumulation bits

    24, // 24-bit depth buffer
    8, // 8-bit stencil buffer
    0, // no auxiliary buffer
    PFD_MAIN_PLANE, // main drawing layer
    0, // reserved
    0, 0, 0 // skip layer masks
};

namespace DisplayDevice {
    void Init() {
        HDC dc = Window::GetHdc();
        // choose a suitable pixel format
        int pf = ChoosePixelFormat(dc, &s_PFD);
        if (!pf)
            Log::LogWinApi(Log::FATAL);
        // set pixel format
        if (!SetPixelFormat(dc, pf, &s_PFD))
            Log::LogWinApi(Log::FATAL);
    }

    void Destroy() {
        GLContext::Destroy();
    }

    void Swap() {
        SwapBuffers(Window::GetHdc());
    }

    void InitGL() {
        GLContext::Create();
    }
}
