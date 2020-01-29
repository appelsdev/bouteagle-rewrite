#include <stdio.h>
#include "packet.h"
#include "PacketQueue.h"
#include "connection/LoginConnection.h"

void LoginConnection::handlePacket(Packet in) {
    in.print();
    AcePacket p;
    switch (in.ptr()[2]) {
    case 0x00:
        p.type = LOGIN_SUCCESS;
        break;
    case 0x02:
        p.type = LOGIN_INVALID_USER;
        break;
    case 0x01:
        p.type = LOGIN_INVALID_PASS;
        break;
    case 0x03:
        p.type = LOGIN_BANNED;
        break;
    case 0x06:
        p.type = LOGIN_ALREADY;
        break;
    }
    PacketQueue::Push(p);
}

void LoginConnection::login(const char* username, const char* password) {
    Packet p = Packet::Allocate(11000, 64);
    memcpy(p.ptr()   , username, strlen(username)); //23
    memcpy(p.ptr()+23, password, strlen(password)); //32
    sendPacket(p);
}
