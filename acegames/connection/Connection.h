#pragma once
#include "packet.h"
#include "socket.h"
#include "thread.h"

class Connection {
public:
    ~Connection();
    void close();
    void connect(const char* ip, int port, Protocol type);
    int receivePacket(char* dest);
    void sendPacket(Packet p);
    virtual void handlePacket(Packet p) = 0;

    bool connected;

private:
    Socket socket;
    SOCKADDR_IN connection;
    Protocol type;
    Thread* thread = NULL;

    char* stream = NULL;
    int heldBytes = 0;

};
