#include <queue>
#include <cstring>
#include "PacketQueue.h"
#include "acegames/acegames.h"

static std::queue<AcePacket> s_queue;

namespace PacketQueue {
void Push(AcePacket p) {
    s_queue.push(p);
}
}

/**
 * Abstract layer to receive packets from different server connections.
 *
 * @param AcePacket* packet Pointer to a packet struct to write to.
 *
 * @return 0 If no packets have been found.
 *         1 If a packet has been found.
 */
ACEGAMES int Ace_Poll(AcePacket* packet) {
    if (s_queue.empty())
        return 0;

    AcePacket p = s_queue.front();
    s_queue.pop();
    memcpy(packet, &p, sizeof(p));
    return 1;
}
