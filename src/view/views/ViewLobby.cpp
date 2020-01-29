#include "view/ui/UIElement.h"
#include "view/views/Views.h"
#include "view/ViewManager.h"
#include "view/View.h"
#include "network/Client.h"
#include "Log.h"

static bool s_isLoggingIn = false;


void ViewLobby::prepare() {
    // Log::Log(Log::INFO, "Preparing lobby view...");
    //
    // UI::Image* background = new UI::Image();
    // background->setName("Overlay");
    // background->assignTexture("assets/data/ui/ui_200.tga");
    // background->setPos({0, 0});
    // addUIElement(background);
    //
    // UI::Button* exit = new UI::Button();
    // exit->setName("Exit");
    // exit->assignTexture("assets/data/ui/ui_207.tga");
    // exit->setPos({640, 550});
    // exit->setBounds({640 + 132, 550 + 38, 640, 550});
    // addUIElement(exit);

}



void ViewLobby::cleanup() {

}

void ViewLobby::doAction(const std::string& name) {
    // if ("Exit" == name) {
    //     ViewManager::SwitchView(Login);
    // }
}

void ViewLobby::handlePacket(AcePacket p) {
    // switch (p.type) {
    // case Network::SELECTSERVER_CYBERSPACE:
    //     ViewManager::SwitchView(SelectServer);
    //     return;
    // default:return;
    // }
    // Client::Disconnect();
    // s_isLoggingIn = false;
}
