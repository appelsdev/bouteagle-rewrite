#include "socket.h"

/**
 * @param Protocol
 * @return 0 on success, otherwise WSAGetLastError
 */
int Socket::create(Protocol type) {
    SOCKET result = socket(AF_INET, (type == PROTOCOL_TCP) ? SOCK_STREAM : SOCK_DGRAM, 0);
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

bool Socket::isConnected() {
    return (-1 != sock);
}
