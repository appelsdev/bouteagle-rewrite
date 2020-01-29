#include "network/Network.h"
#include <Winsock2.h>

int Socket::create() {
    SOCKET result = socket(AF_INET, SOCK_STREAM, 0);
    if (SOCKET_ERROR == result)
        return WSAGetLastError();
    sock = result;
    return 0;
}

void Socket::close() {
    if (-1 != sock)
        closesocket(sock);
    sock = -1;
}
