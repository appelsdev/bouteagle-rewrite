#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <Winsock2.h>
#include "wsa.h"
#include "error.h"

namespace WSA {

void Init() {
    WSADATA wsaData;
    if (0 != WSAStartup(0x202, &wsaData)) {
        Error::SetError("WSA failed to initialize.");
    }
    if (0x0202 != wsaData.wVersion) {
        WSACleanup();
        Error::SetError("Wrong WSA version.");
    }
}

void Cleanup() {
    WSACleanup();
}

}
