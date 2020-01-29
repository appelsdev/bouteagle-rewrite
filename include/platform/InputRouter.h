#pragma once
#include <string>

namespace InputRouter {
    void HandleChar(int scancode);
    void HandleKeyDown(int scancode);
    void HandleKeyUp(int scancode);
    void Finish();
};
