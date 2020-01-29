#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Main.h"
#include "Log.h"
#include "platform/InputRouter.h"
#include "platform/Mouse.h"
#include "platform/Window.h"

static const int s_windowStyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
static const int s_windowStyleEx = WS_EX_LEFT;
static HWND s_hwnd;
static HDC s_hdc;
// static PAINTSTRUCT ps;

static LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    // handle close button
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;


    // focus
    case WM_SETFOCUS:
        return 0;
    case WM_KILLFOCUS:
        return 0;

    // input
    case WM_CHAR:
        InputRouter::HandleChar(wParam);
        return 0;
    case WM_KEYDOWN:
        InputRouter::HandleKeyDown(wParam);
        return 0;
    case WM_KEYUP:
        InputRouter::HandleKeyUp(wParam);
        return 0;
    case WM_LBUTTONDOWN:
        Mouse::HandleDown(Mouse::LEFT);
        return 0;
    case WM_LBUTTONUP:
        Mouse::HandleUp(Mouse::LEFT);
        return 0;
    case WM_RBUTTONDOWN:
        Mouse::HandleDown(Mouse::RIGHT);
        return 0;
    case WM_RBUTTONUP:
        Mouse::HandleUp(Mouse::RIGHT);
        return 0;

    default:
        // call Windows' default window proc
        return DefWindowProc(wnd, msg, wParam, lParam);
    }
}

namespace Window {
    void Init(const char* title) {
        // define the window class
        HINSTANCE inst = GetModuleHandle(NULL);
        WNDCLASSEX wc;
        wc.cbSize        = sizeof(wc);
        wc.style         = CS_CLASSDC;
        wc.lpfnWndProc   = WndProc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = inst;
        wc.hIcon         = LoadIcon(inst, MAKEINTRESOURCE(IDI_APPLICATION));
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = NULL;
        wc.lpszMenuName  = NULL;
        wc.lpszClassName = title;
        wc.hIconSm       = LoadIcon(inst, MAKEINTRESOURCE(IDI_APPLICATION));
        // register it
        if (!RegisterClassEx(&wc))
            Log::LogWinApi(Log::FATAL);

        // create window
        RECT r = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        AdjustWindowRectEx(&r, s_windowStyle, FALSE, s_windowStyleEx);
        int width = r.right - r.left;
        int height = r.bottom - r.top;
        HWND hwnd = CreateWindowEx(
            s_windowStyleEx,
            title,
            title,
            s_windowStyle,
            (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
            (GetSystemMetrics(SM_CYSCREEN) - height) / 2,
            width,
            height,
            NULL,
            NULL,
            inst,
            NULL
        );
        // check for errors
        if (!hwnd)
            Log::LogWinApi(Log::FATAL);
        // store the window handle
        s_hwnd = hwnd;

        // store the device context
        s_hdc = GetDC(hwnd);
        if (!s_hdc)
            Log::LogWinApi(Log::FATAL);
    }

    void Destroy() {
        DestroyWindow(s_hwnd);
    }

    void Show() {
        ShowWindow(s_hwnd, SW_SHOW);
    }

    void PumpMessages() {
        MSG msg = {0};
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (WM_QUIT == msg.message)
                Main::Abort();
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    HWND GetHwnd() {
        return s_hwnd;
    }

    HDC GetHdc() {
        return s_hdc;
    }

    int GetWidth() { return WINDOW_WIDTH; }
    int GetHeight() { return WINDOW_HEIGHT; }
}
