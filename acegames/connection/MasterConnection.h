#include "connection/Connection.h"
class MasterConnection : public Connection {
public:
    void handlePacket(Packet p);
    void requestChannels();
};
