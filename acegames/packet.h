#pragma once
#define SWAP_ENDIAN_16(x)/**/\
    ((((unsigned short)(x))>>8)|(((unsigned short)(x))<<8))

class Packet {
public:
    static Packet FromBuffer(char* data, int len);
    static Packet Allocate(short id, short size);
    ~Packet();

    void print();
    void setId(short id);
    char* ptr();
    int getTotalSize();

    char* data;
    int totalSize;
};
