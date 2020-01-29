#include <string>
namespace Client {
    void Login(const std::string& username, const std::string& password);
    void HandlePacket(char* buffer, int size);
    void Disconnect();
};
