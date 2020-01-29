#pragma once

typedef enum {
    WALK_LEFT, WALK_RIGHT, WALK_UP, WALK_DOWN
} Msg;

namespace MessageBus {

    void Post(Msg msg);
}
