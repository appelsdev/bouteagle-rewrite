#pragma once
#include <Winsock2.h>

class Socket {
public:
    int create();
    void close();
    SOCKET sock;
};


namespace Network {
    void DoConnectionCheck();
    void Init();

    void Cleanup();
    void ConnectToServer(const char* ipAddress, int port);
    void Send(char* buffer, int length);
    bool IsConnected();
}
