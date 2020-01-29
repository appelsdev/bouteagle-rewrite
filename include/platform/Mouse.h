

namespace Mouse {
    typedef enum {
        LEFT = 0, RIGHT = 1
    } MOUSEBUTTON;

    void HandleDown(MOUSEBUTTON btn);
    void HandleUp(MOUSEBUTTON btn);
    void Update();
    int GetX();
    int GetY();
    bool IsHeld(MOUSEBUTTON btn);
    bool IsPressed(MOUSEBUTTON btn);
}
