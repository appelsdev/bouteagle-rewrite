#pragma once
#include "view/View.h"
#include "acegames/acegames.h"

typedef enum {
    Login, Play, SelectServer, Lobby
} VIEWID;

class ViewLogin : public View {
private:
    void tryLogin();
public:
    void prepare();
    void cleanup();
    void doAction(const std::string& name);
    void handlePacket(AcePacket p);
};

class ViewPlay : public View {

};

class ViewSelectServer : public View {
public:
    void prepare();
    void cleanup();
    void doAction(const std::string& name);
    void handlePacket(AcePacket p);
};

class ViewLobby : public View {
public:
    void prepare();
    void cleanup();
    void doAction(const std::string& name);
    void handlePacket(AcePacket p);
};
