#include "platform/Window.h"
#include "platform/DisplayDevice.h"
#include "scene/SceneManager.h"
#include "renderer/Renderer.h"

class Engine {
private:
    bool running;
public:
    void init();
    void cleanup();
    void update();
    bool isRunning();
    void doActionsWhileRendererStarts();
};
