#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <Winsock2.h>
#include <stdlib.h>
#include <stdio.h> // @FIXME
#include "connection/Connection.h"
#include "socket.h"
#include "thread.h"
#include "error.h"
#include "packet.h"
#include "PacketQueue.h"
#include "acegames/acegames.h"
#define PACKET_SIZE 2048

// if (sendto(socketC, buffer, sizeof(buffer), 0, (sockaddr*)&serverInfo, len) != SOCKET_ERROR)
//        {
//            if (recvfrom(socketC, buffer, sizeof(buffer), 0, (sockaddr*)&serverInfo, &len) != SOCKET_ERROR)
//            {
//                printf("Receive response from server: %s\n", buffer);
//            }
//        }

/**
 * The packet receiver thread.
 */
void receiverProc(Connection* conn) {
    char* buffer = (char*)malloc(PACKET_SIZE);

    while (conn->connected) {
        // Wait for packet
        int r = conn->receivePacket(buffer);
        if (-1 == r) {
            Error::SetError("Failed to receive packet; last WSA error = %i.", WSAGetLastError());
            break;
        } else if (-2 == r) {
            Error::SetError("Connection closed.");
            break;
        } else if (0 != r) { // Handle packet
            conn->handlePacket(Packet::FromBuffer(buffer, r));
        }

        // @TODO: If UDP then test ping

        Sleep(1);
    }

    puts("Closing connection!");
    free(buffer);

    // Send disconnection message as fake packet
    AcePacket p;
    p.type = DISCONNECT;
    PacketQueue::Push(p);
}

/**
 * Destructor closes connection.
 */
Connection::~Connection() {
    puts("Destructing connection.");
    this->close();
}

/**
 * Closes receiver thread, closes socket and frees stream buffer.
 */
void Connection::close() {
    connected = false;
    thread->waitUntilDone();
    delete thread;

    socket.close();
    free(stream);
}

/**
 * Initiate connection to a server.
 *
 * @param const char* ip
 * @param int         port
 * @param Protocol    type  PROTOCOL_TCP or PROTOCOL_UDP.
 */
void Connection::connect(const char* ip, int port, Protocol type) {
    this->type = type;
    if (0 != socket.create(type))
        Error::SetError("Unable to create socket.");

    // Create the connection struct
    connection.sin_family      = AF_INET;
    connection.sin_port        = ntohs(port);
    connection.sin_addr.s_addr = inet_addr(ip);

    // When protocol is TCP attempt to connect
    if (PROTOCOL_TCP == type) {
        if (SOCKET_ERROR == ::connect(socket.sock, (SOCKADDR*)&connection, sizeof(connection))) {
            Error::SetError("Unable to connect to TCP server.");
        }
        // Set as non-blocking
        u_long mode = 1;
        int err = ioctlsocket(socket.sock, FIONBIO, &mode);
        if (NO_ERROR != err) {
            Error::SetError("Unable to set TCP socket as non-blocking (%i).", err);
        }
    }
    this->connected = true;

    // Allocate buffer that'll initially receive the stream of incoming data
    if (!stream)
        stream = (char*)malloc(PACKET_SIZE);

    // Start receiver thread
    thread = new Thread((void*)receiverProc, (void*)this, true);
}

/**
 * Copy data of the last received packet and remove it from the list.
 * Server packets are structured as follows:
 * <short Type> <short Length> <char Data[Length]>
 *
 * @param char* dest  Output buffer.
 *
 * @returns int   0 if no packet was found.
 *               -1 if a socket error occurred.
 *               -2 if the connection was closed.
 *               Otherwise the total size of the packet.
 */
int Connection::receivePacket(char* dest) {
    int bytesRead = heldBytes;
    short packetLength;
    bool buildingHeader = true;

    // Copy leftover data from previous call into output buffer
    if (heldBytes > 0) {
        memcpy(dest, stream, heldBytes);
        heldBytes = 0;
    }

    // Read packet
    while (true) {
        // Try to copy incoming packet data into stream buffer
        int r;
        if (PROTOCOL_TCP == type) {
            r = recv(socket.sock, dest + bytesRead, PACKET_SIZE - bytesRead, 0);
        } else {
            int len = sizeof(SOCKADDR_IN);
            r = recvfrom(socket.sock, dest, PACKET_SIZE, 0, (sockaddr*)&connection, &len);
        }

        // Handle errors and non-blocking passthrough
        if (SOCKET_ERROR == r) {
            int err = WSAGetLastError();
            if (WSAEWOULDBLOCK == err)
                return 0;
            printf("Wsa returned %i.\n", err);
            return -1;
        } else if (0 == r) { // connection close
            return -2;
        }

        bytesRead += r;

        // Build packet header
        if (buildingHeader) {
            if (bytesRead > 4) { // packet header size
                packetLength = (dest[2] | dest[3] << 8);
            }
            buildingHeader = false;
            // @TODO: Make sure dest buffer is big enough
        }

        // Check whether we finished building the packet
        if (!buildingHeader && (bytesRead >= packetLength))
            break;
    }

    // Save leftover bytes in stream buffer for the next call
    heldBytes = bytesRead - packetLength;
    memcpy(stream, dest + packetLength, heldBytes);

    return packetLength;
}

/**
 * Send a packet to the server.
 */
void Connection::sendPacket(Packet p) {
    if (!this->connected) {
        Error::SetError("Tried to send packet after closing connection.");
        return;
    }

    int bytesLeft = p.getTotalSize();
    char* buffer = p.data;

    while (bytesLeft > 0) {
        int bytesSent = send(socket.sock, buffer, bytesLeft, 0);
        if (SOCKET_ERROR == bytesSent) {
            Error::SetError("Socket error while sending packet. WSA returned %i.", WSAGetLastError());
            return;
        }
        bytesLeft -= bytesSent;
        buffer += bytesSent;
    }
}
