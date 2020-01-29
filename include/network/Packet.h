#pragma once
namespace Network {
typedef enum {
    UNKNOWN,
    LOGIN_SUCCESS, LOGIN_INVALID_USER, LOGIN_INVALID_PASS, LOGIN_BANNED, LOGIN_ALREADY,
    SELECTSERVER_CYBERSPACE
} PacketType;

class Packet {
    public:
        Packet(char* buffer, int size);
        unsigned char* data;
        int size;
        PacketType type = UNKNOWN;
};
}
