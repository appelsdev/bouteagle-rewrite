#include <stdlib.h>
#include <stdio.h>
#include "packet.h"
#include "connection/MasterConnection.h"

void MasterConnection::handlePacket(Packet in) {
    printf("Incoming packet...\n");
    in.print();



    //PacketQueue::Push(p);

    // AcePacket p;
    // p.size = size;
    // switch (buffer[2]) {
    // case 0x00:
    //     p.type = LOGIN_SUCCESS;
    //     break;
    // case 0x02:
    //     p.type = LOGIN_INVALID_USER;
    //     break;
    // case 0x01:
    //     p.type = LOGIN_INVALID_PASS;
    //     break;
    // case 0x03:
    //     p.type = LOGIN_BANNED;
    //     break;
    // case 0x06:
    //     p.type = LOGIN_ALREADY;
    //     break;
    // }
    // PacketQueue::Push(p);
}

void MasterConnection::requestChannels() {
    const long serverId = 1;
    Packet p = Packet::Allocate(0xFA2A, sizeof(serverId));
    *(p.ptr()) = serverId;
    p.print();
    sendPacket(p);
}
