#pragma once
#include "platform/Window.h"
#include "platform/GLContext.h"
namespace DisplayDevice {
    void Init();
    void Destroy();
    void Swap();
    void InitGL();
}
