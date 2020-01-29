#include "view/ui/UIElement.h"
#include "view/views/Views.h"
#include "view/ViewManager.h"
#include "view/View.h"
#include "network/Client.h"
#include "Log.h"

static bool s_isLoggingIn = false;

void ViewSelectServer::prepare() {
    setBackground("data/ads/adban_main.tga");

    // Server select panel
    UI::Image* panel = new UI::Image();
    panel->setName("Panel");
    panel->assignTexture("data/ui/ui_150.tga");
    addUIElement(panel);

    Log::Log(Log::INFO, "Preparing server select view...");

}

void ViewSelectServer::cleanup() {

}

void ViewSelectServer::doAction(const std::string& name) {
    if ("Cyberspace" == name) {

    }
}

void ViewSelectServer::handlePacket(AcePacket p) {
    // switch (p.type) {
    // case Network::SELECTSERVER_CYBERSPACE:
    //     ViewManager::SwitchView(SelectServer);
    //     return;
    // default:return;
    // }
    // Client::Disconnect();
    // s_isLoggingIn = false;
}
