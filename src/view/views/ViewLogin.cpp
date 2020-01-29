#include "network/Packet.h"
#include "network/Client.h"
#include "view/ViewManager.h"
#include "view/views/Views.h"
#include "view/ui/UIElement.h"
#include "view/View.h"
#include "acegames/acegames.h"
#include "Main.h"
#include "Log.h"

static bool s_isLoggingIn = false;

void ViewLogin::tryLogin() {
    if (s_isLoggingIn) return;
    s_isLoggingIn = true;
    UI::LoginBox* box = new UI::LoginBox();
    box->setName("LoginBox");
    addUIElement(box);

    Ace_Login(getEditBoxValue("ID").c_str(), getEditBoxValue("Password").c_str());
}



void ViewLogin::prepare() {
    // setBackground("assets/data/ads/adban_main.tga");
    //
    // UI::Image* overlay = new UI::Image();
    // overlay->setName("Overlay");
    // overlay->assignTexture("assets/data/ui/ui_100.tga");
    // overlay->setPos({0, 0});
    // addUIElement(overlay);
    //
    // UI::Image* logo = new UI::Image();
    // logo->setName("Logo");
    // logo->assignTexture("assets/data/ads/adban_login.tga");
    // logo->setPos({16, 488});
    // addUIElement(logo);
    //
    // UI::Button* login = new UI::Button();
    // login->setName("Connection");
    // login->assignTexture("assets/data/ui/ui_101.tga");
    // login->setPos({466, 544});
    // login->setBounds({466, 544, 596, 575});
    // addUIElement(login);
    //
    // UI::Button* exit = new UI::Button();
    // exit->setName("Exit");
    // exit->assignTexture("assets/data/ui/ui_207.tga");
    // exit->setPos({647, 543});
    // exit->setBounds({647, 543, 779, 581});
    // addUIElement(exit);
    //
    // UI::EditBox* username = new UI::EditBox();
    // username->setName("ID");
    // username->setBounds({468, 497, 596, 511});
    // username->setMaxChars(18);
    // addUIElement(username);
    //
    // UI::EditBox* password = new UI::EditBox();
    // password->setName("Password");
    // password->setBounds({468, 520, 596, 534});
    // password->setMaxChars(18);
    // password->setProtected(true);
    // addUIElement(password);
    //
    // selectEditBox("ID");
}

void ViewLogin::cleanup() {
    // removeUIElement("Overlay");
    // removeUIElement("Logo");
    // removeUIElement("ID");
    // removeUIElement("Password");
    // removeUIElement("Exit");
}

void ViewLogin::doAction(const std::string& name) {
    if ("Connection" == name || "ID" == name || "Password" == name) {
        tryLogin();
    } else if ("Exit" == name) {
        Main::Abort();
    } else if ("Cancel Login" == name) {
        Ace_Disconnect();
        removeUIElement("LoginBox");
        s_isLoggingIn = false;
    } else if ("MessageBox OK" == name) {
        UI::RemoveMessageBoxes();
    }
}

void ViewLogin::handlePacket(AcePacket p) {
    // Log::Log(Log::INFO, "PACKET %i", p.type);
    // AceStatus status;
    // removeUIElement("LoginBox");
    //
    // switch (p.type) {
    // case DISCONNECT:
    //     Log::Log(Log::INFO, "DISCONNECT MSG");
    //     break;
    // case LOGIN_SUCCESS:
    //     Log::Log(Log::INFO, "Login success");
    //     status = Ace_Channel_Connect();
    //     switch (status) {
    //     case AceStatus::CHANNEL_CONNECTED:
    //         ViewManager::SwitchView(Lobby);
    //         break;
    //     case AceStatus::CHANNEL_CREATE_BOT:
    //         Log::Log(Log::INFO, "create bot");
    //         addUIElement(new UI::CreateBotDialog());
    //         break;
    //     case AceStatus::CHANNEL_DISCONNECTED:
    //         Log::Log(Log::INFO, "FUCK CHANNEL DISCONNECT");
    //         UI::ShowMessageBox("Oh noes! We were unable to login.\nTry again later!");
    //         break;
    //     }
    //     return;
    // case LOGIN_INVALID_USER:
    //     Log::Log(Log::WARNING, "Invalid user");
    //     UI::ShowMessageBox("You entered an invalid username brah!");
    //     break;
    // case LOGIN_INVALID_PASS:
    //     Log::Log(Log::WARNING, "Invalid pass");
    //     UI::ShowMessageBox("Yo that password is invalid!");
    //     break;
    // case LOGIN_BANNED:
    //     Log::Log(Log::WARNING, "User is banned");
    //     UI::ShowMessageBox("Your account has been banned, we're sorry <3.");
    //     break;
    // default:
    //     Log::Log(Log::INFO, "PACKET %i", p.type);return;
    // }
    // Ace_Disconnect();
    // s_isLoggingIn = false;
}
