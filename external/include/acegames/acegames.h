#pragma once
#ifdef ACEGAMES_DLL
#define ACEGAMES __declspec(dllexport)
#else
#define ACEGAMES __declspec(dllimport)
#endif

typedef enum {
    LOGIN_SUCCESS, LOGIN_INVALID_USER, LOGIN_INVALID_PASS, LOGIN_BANNED, LOGIN_ALREADY,
    SELECTSERVER_CYBERSPACE,
    DISCONNECT
} AcePacketType;

typedef struct {
    AcePacketType type;
    int size;
    void* data;
} AcePacket;

typedef enum {
    CHANNEL_CONNECTED, CHANNEL_DISCONNECTED, CHANNEL_CREATE_BOT
} AceStatus;


ACEGAMES void Ace_Login(const char* username, const char* password);
ACEGAMES void Ace_Disconnect();
ACEGAMES AceStatus Ace_Channel_Connect();

ACEGAMES int Ace_Poll(AcePacket* packet);

ACEGAMES const char* Ace_GetErrorString();
ACEGAMES int Ace_GetErrorNum();
