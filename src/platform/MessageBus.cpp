#include "platform/MessageBus.h"
#include "scene/SceneManager.h"

namespace MessageBus {
    void Post(Msg msg) {
        SceneManager::HandleMessage(msg);
    }
}
