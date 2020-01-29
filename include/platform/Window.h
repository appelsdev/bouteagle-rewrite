#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

namespace Window {
    void Init(const char* title);
    void Destroy();
    void Show();
    void PumpMessages();
    HWND GetHwnd();
    HDC GetHdc();
    int GetWidth();
    int GetHeight();
}
