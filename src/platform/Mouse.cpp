#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "platform/Window.h"
#include "platform/Mouse.h"
#include "Log.h"

typedef enum {
    RELEASED = 0, PRESSED = 1, HELD = 2
} MOUSESTATE;

static POINT s_pos;
static MOUSESTATE s_buttons[2] = { RELEASED, RELEASED };

namespace Mouse {
    void HandleDown(MOUSEBUTTON btn) {
        if (RELEASED == s_buttons[btn])
            s_buttons[btn] = PRESSED;
    }

    void HandleUp(MOUSEBUTTON btn) {
        s_buttons[btn] = RELEASED;
    }

    void Update() {
        // update position
        GetCursorPos(&s_pos);
        ScreenToClient(Window::GetHwnd(), &s_pos);

        // update states
        for (int i = 0; i < 2; i++)
            if (PRESSED == s_buttons[i])
                s_buttons[i] = HELD;
    }

    int GetX() {
        return s_pos.x;
    }

    int GetY() {
        return s_pos.y;
    }

    bool IsHeld(MOUSEBUTTON btn) {
        return (RELEASED != s_buttons[btn]);
    }

    bool IsPressed(MOUSEBUTTON btn) {
        return (PRESSED == s_buttons[btn]);
    }

}
