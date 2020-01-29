#pragma once
#include "platform/MessageBus.h"
#include "scene/Scene.h"

namespace SceneManager {
    void HandleMessage(Msg msg);
    void Init();
    void Destroy();
    void UpdateActiveScene();
    Scene* GetActiveScene();
}
