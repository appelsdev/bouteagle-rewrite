#include "connection/Connection.h"
class LoginConnection : public Connection {
public:
    void handlePacket(Packet p);
    void login(const char* username, const char* password);
};
