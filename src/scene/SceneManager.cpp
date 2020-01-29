#include "platform/MessageBus.h"
#include "scene/Scene.h"
#include "scene/SceneManager.h"

static Scene* s_activeScene;

namespace SceneManager {
    void HandleMessage(Msg msg) {
        switch (msg) {
        case WALK_LEFT:
            s_activeScene->getPlayer()->walkLeft();
            break;
        case WALK_RIGHT:
            s_activeScene->getPlayer()->walkRight();
            break;
        case WALK_UP:
            s_activeScene->getPlayer()->walkUp();
            break;
        case WALK_DOWN:
            s_activeScene->getPlayer()->walkDown();
            break;
        }
    }

    void Init() {
        s_activeScene = new Scene();
    }

    void Destroy() {
        delete s_activeScene;
    }

    void UpdateActiveScene() {
        s_activeScene->update();
    }

    Scene* GetActiveScene() {
        return s_activeScene;
    }
}
