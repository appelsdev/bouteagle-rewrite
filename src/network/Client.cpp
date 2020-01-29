#include "view/ViewManager.h"
#include "network/Network.h"
#include "network/Client.h"
#include "Log.h"

// swapped = (num>>8) | (num<<8);
// Unsigned 32-bit conversion:
//
// swapped = ((num>>24)&0xff) | // move byte 3 to byte 0
//                     ((num<<8)&0xff0000) | // move byte 1 to byte 2
//                     ((num>>8)&0xff00) | // move byte 2 to byte 1
//                     ((num<<24)&0xff000000); // byte 0 to byte 3

#define SWAP_ENDIAN_16(x)/**/\
    (((x)>>8)|((x)<<8))

#define SWAP_ENDIAN_32(x)/**/\
    /*FUCK*/;



static void sendPacket(char* buffer, int size) {
    // *(uint16_t*)(buffer+offset) = value
    char packet[2048] = {0};
    *(int*)packet = SWAP_ENDIAN_16(0xF82A);
    *(int*)(packet+2) = 64;
    memcpy(packet+4, buffer, size);
    Network::Send(packet, size+4);
}

namespace Client {

/**
 * Send a login packet to the server.
 *
 * @param const std::string& username
 * @param const std::string& password
 */
void Login(const std::string& username, const std::string& password) {
    if (!Network::IsConnected())
        Network::Init();
    Network::DoConnectionCheck();

    char packet[64] = {0};
    memcpy(packet, username.c_str(), strlen(username.c_str())); //23
    memcpy(packet+23, password.c_str(), strlen(password.c_str())); //32
    sendPacket(packet, 64);
}

void HandlePacket(char* buffer, int size) {
    // ViewManager::GetActiveView()->handlePacket(Network::Packet(buffer, size));
}

void Disconnect() {
    Network::Cleanup();
}

};
