#pragma once
#include <Winsock2.h>

typedef enum {
    PROTOCOL_TCP, PROTOCOL_UDP
} Protocol;

class Socket {
public:
    int create(Protocol type);
    void close();
    bool isConnected();
    SOCKET sock = -1;
};
