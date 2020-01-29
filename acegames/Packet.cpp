#include <stdio.h>
#include <stdlib.h>
#include "packet.h"

/**
 * Make packet object from a buffer.
 *
 * @param char* data
 * @param int   len
 */
Packet Packet::FromBuffer(char* data, int len) {
    Packet p;
    // p.totalSize = (*(short*)(data+2)) + 4;
    p.totalSize = len;
    p.data = (char*)data;
    return p;
}

/**
 * Allocate a new packet.
 *
 * @param short id    The packet header's id field.
 * @param short size  Packet data size, this does not include the 4 bytes of the
 *                    packet's header.
 */
Packet Packet::Allocate(short id, short size) {
    Packet p;
    p.totalSize = size + 4;
    p.data = (char*)malloc(p.totalSize);
    *(short*)p.data     = id;
    *(short*)(p.data+2) = size;
    return p;
}

/**
 * Cleanup.
 */
Packet::~Packet() {
    free(data);
}

/**
 * Print packet in a formatted manner.
 */
void Packet::print() {
    unsigned short id = SWAP_ENDIAN_16(*(unsigned short*)data);
    printf("<%04X | Data Length: %hi>\n", id, (*(unsigned short*)(data+2)));
    for (int i = 4, j = 0; i < totalSize; i++, j = (j + 1) % 8) {
        printf("%02X ", (unsigned char)data[i]);
        if (7 == j)
            printf("\n");
    }
    printf("-----------------------\n");
}

/**
 * Set packet type.
 *
 * @param short id
 */
void Packet::setId(short id) {
    *(short*)data = id;
}

/**
 * Return packet inner data pointer.
 *
 * @return char*
 */
char* Packet::ptr() {
    return data+4;
}

/**
 * Total buffer size of the packet.
 *
 * @return int
 */
int Packet::getTotalSize() {
    return totalSize;
}
