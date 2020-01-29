#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <Winsock2.h>
#include "Main.h"
#include "network/Network.h"
#include "network/Client.h"
#include "platform/Thread.h"
#include "acegames/acegames.h"
#include "Log.h"
#define PACKET_SIZE 2048
static bool s_connected = false;
static Socket s_socket;
static Thread* s_thread;
static char s_packetBuffer[PACKET_SIZE];

/**
 * Packet receival thread.
 */
static void networkProc(void* unused) {
    Log::Log(Log::INFO, "Network thread started.");
    do {
        int result = recv(
            s_socket.sock,
            s_packetBuffer,
            PACKET_SIZE,
            0
        );
        if (result > 0) {
            // Log::Log(Log::INFO, "WE GOT A PACKET HOE (%i):");
            Log::PrintBuffer(s_packetBuffer, result);
            Client::HandlePacket(s_packetBuffer, result);
        } else if (0 == result) { // connection closed
            Log::Log(Log::WARNING, "Tried to receive packet but connection was closed.");
            break;
        } else {
            Log::Log(Log::FATAL, "Failed to receive packet; last WSA error = %i.", WSAGetLastError());
            break;
        }
        Sleep(1);
    } while (Main::GetEngine()->isRunning());
}



namespace Network {

void DoConnectionCheck() {
    if (!s_connected)
        Log::Log(Log::FATAL, "We aint connected mate!");
    struct timeval timeout = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(s_socket.sock, &fds);
    if ((SOCKET_ERROR == select(64, NULL, &fds, NULL, &timeout))
    || (0 == __WSAFDIsSet(s_socket.sock, &fds))) {
        Log::Log(Log::FATAL, "Oh shit network fucked!");
    }
}

void Init() {
    // Init WSA
    WSADATA wsaData;
    if (0 != WSAStartup(0x202, &wsaData)) {
        Log::Log(Log::FATAL, "WSA failed to initialize.");
    }
    if (0x0202 != wsaData.wVersion) {
        WSACleanup();
        Log::Log(Log::FATAL, "Wrong WSA version.");
    }

    // Create socket
    if (s_socket.create())
        Log::Log(Log::FATAL, "Unable to create socket.");

    // @TODO: Encrypt IP string
    Network::ConnectToServer("158.69.217.182", 53699);

    // Start packet recv thread
    s_thread = new Thread((void*)networkProc, (void*)NULL, true);
}

void Cleanup() {
    Log::Log(Log::INFO, "Network disconnecting.");
    s_connected = false;
    s_socket.close();
    WSACleanup();
}

void ConnectToServer(const char* ipAddress, int port) {
    if (s_connected) {
        Log::Log(Log::WARNING, "Already connected.");
        return;
    }
    // create the connection struct
    SOCKADDR_IN connection;
    connection.sin_family      = AF_INET;
    connection.sin_port        = ntohs(port);
    connection.sin_addr.s_addr = inet_addr(ipAddress);
    /* Connect to server, the return value will automatically be -1 if connect()
       returns SOCKET_ERROR. */
    if (-1 == connect(s_socket.sock, (SOCKADDR*)&connection, sizeof(connection))) {
        Log::Log(Log::FATAL, "Unable to connect to server.");
    }
    s_connected = true;
}

void Send(char* buffer, int length) {
    // Log::PrintBuffer(buffer, length);
    DoConnectionCheck();
    int result = send(s_socket.sock, buffer, length, 0);
    if (SOCKET_ERROR == result) {
        Log::Log(Log::FATAL, "Socket error, last WSA error = %i.", WSAGetLastError());
    }
    Log::Log(Log::INFO, "Bytes sent: %i", result);
}

bool IsConnected() {
    return s_connected;
}

}
