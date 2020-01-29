#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <Winsock2.h>
#define WIN32WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <queue>
#include "acegames/acegames.h"
#include "wsa.h"
#include "connection/Connection.h"
#include "connection/LoginConnection.h"
#include "connection/MasterConnection.h"


static LoginConnection* s_connLogin = NULL;
std::queue<AcePacket> g_packetQueue;



/**
 * Connects with the login server and authenticates.
 * @param const char* username
 * @param const char* password
 */
ACEGAMES void Ace_Login(const char* username, const char* password) {

    // Connect if needed
    if (!s_connLogin) {
        s_connLogin = new LoginConnection();
        s_connLogin->connect("158.69.217.182", 53699, PROTOCOL_TCP);
    }

    // Make login packet
    s_connLogin->login(username, password);
}


/**
 * Connects to the lobby.
 * @returns AceStatus
 */
ACEGAMES AceStatus Ace_Channel_Connect() {
    // Retrieve channel IP from master server
    MasterConnection* master = new MasterConnection();
    master->connect("158.69.217.182", 11010, PROTOCOL_UDP);
    master->requestChannels();





    // UDPConnection*
    // 11010 UDP
    // Receive:
    // 	FA2A: CHANNEL_SELECTION_PACKET
    // 		in:	FA2A, 2 bytes length, 2 bytes Server ID
    // 		Out: 	- EE2C, 2 bytes lenght, loop*12: (if channel: (2 bytes playercount, 1 byte min_level, 1 byte max_level, 22 bytes channel name) Else if no channel: (FF FF, 24 Bytes 00))
    // 				  loop*4: (if channel: (00 00, split ip on "." then int to byte for all 4 numbers) else if no channel: (FF FF 00 00 00 00)).
    return CHANNEL_CONNECTED;
}

/**
 * Closes all connections.
 */
ACEGAMES void Ace_Disconnect() {
    if (s_connLogin)
        s_connLogin->close();
}



BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    switch(reason) {
    case DLL_PROCESS_ATTACH:
        WSA::Init();
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        WSA::Cleanup();
        break;
    }
    return TRUE;
}
