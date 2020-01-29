#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Log.h"
#include "platform/Mouse.h"
#include "platform/MessageBus.h"
#include "platform/InputRouter.h"
#include "view/ViewManager.h"

static int s_keyHeld[255] = {0};

std::string g_keyboardString = "";

namespace InputRouter {
    void HandleChar(int scancode) {
        ViewManager::GetActiveView()->handleChar(scancode);
    }

    void HandleKeyDown(int scancode) {
        // key is pressed if key was not held yet
        if (!s_keyHeld[scancode]) {
            // send messages
            // Log::Log(Log::INFO, "pressed %i", scancode);
            /**/
        }
        // set key held state
        s_keyHeld[scancode] = 1;
    }

    void HandleKeyUp(int scancode) {
        s_keyHeld[scancode] = 0;
        // send messages
        // Log::Log(Log::INFO, "released %i", scancode);
        /**/
    }

    void Finish() {
        // iterate through all of the held keys
        for (int i = 0; i < 255; i++) {
            if (!s_keyHeld[i]) continue;

            // send messages
            // Log::Log(Log::INFO, "held %i", i);
            switch (i) {
                case VK_LEFT:
                    MessageBus::Post(WALK_LEFT);
                    break;
                case VK_RIGHT:
                    MessageBus::Post(WALK_RIGHT);
                    break;
                case VK_UP:
                    MessageBus::Post(WALK_UP);
                    break;
                case VK_DOWN:
                    MessageBus::Post(WALK_DOWN);
                    break;
            }
        }

        // update mouse state
        Mouse::Update();
    }
}
