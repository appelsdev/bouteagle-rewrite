#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Engine.h"
#include <stdio.h>

static Engine* s_engine;

// Request usage of dedicated GFX card by default
__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001; // NVIDIA
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;   // AMD Radeon


int CALLBACK WinMain(HINSTANCE inst, HINSTANCE instPrev, LPSTR cmdLine, int cmdShow) {
    s_engine = new Engine();
    s_engine->init();
    while (s_engine->isRunning()) {
        s_engine->update();
        Sleep(1); // CPU-yield
    }
    s_engine->cleanup();
    return 0;
}

#ifdef DEBUG
int main(int argc, char** argv) {
    AttachConsole(ATTACH_PARENT_PROCESS);
    printf("test\n");
    return WinMain(GetModuleHandle(NULL), NULL, GetCommandLine(), SW_SHOW);
}
#endif

namespace Main {
    void Abort() {
        ExitProcess(0);
    }

    Engine* GetEngine() {
        return s_engine;
    }
}
