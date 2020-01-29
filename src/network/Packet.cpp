#include "network/Packet.h"
namespace Network {


Packet::Packet(char* buffer, int size) {
    this->data = (unsigned char*)buffer;
    this->size = size;

    // Login packet
    switch (data[2]) {
    case 0x00:
        type = LOGIN_SUCCESS;
        break;
    case 0x02:
        type = LOGIN_INVALID_USER;
        break;
    case 0x01:
        type = LOGIN_INVALID_PASS;
        break;
    case 0x03:
        type = LOGIN_BANNED;
        break;
    case 0x06:
        type = LOGIN_ALREADY;
        break;
    }
}


}
