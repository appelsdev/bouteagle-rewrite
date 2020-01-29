#pragma once
#include "scene/Scene.h"

namespace SceneRenderer {
    void Init();
    void Destroy();
    void Render();
    void ChangeScene(Scene* scene);
}
