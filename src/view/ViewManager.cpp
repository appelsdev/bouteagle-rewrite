#include <vector>
#include <string>
#include "view/views/Views.h"
#include "view/ViewManager.h"
#include "view/View.h"
#include "view/TemplateParser.h"
#include "system/ExceptionHandler.h"

static std::vector<View*> s_views;
static View* s_activeView = NULL;

namespace ViewManager {

    void Init() {
        s_views = TemplateParser::LoadViews();
        SwitchView("Login");
    }

    void Destroy() {
        // @TODO: destroy all view objects
    }

    void UpdateActiveView() {
        if (NULL == s_activeView)
            return;
        s_activeView->processPackets();
        s_activeView->updateUIElements();
    }

    View* GetActiveView() {
        return s_activeView;
    }

    void SwitchView(std::string name) {
        if (NULL != s_activeView) {
            // carry over persistant UI elements
            std::vector<UI::Element*> elements = s_activeView->getPersistantUIElements();

            // cleanup resources of current view
            s_activeView->cleanup();
        }

        // set active view pointer
        View* view = NULL;
        for (auto v : s_views) {
            if (name == v->name) {
                view = v;
                break;
            }
        }
        if (!view) {
            THROW_EXCEPTION(ViewException,
                std::string("Failed to switch to view '") +
                name +
                std::string("'.")
            );
        }
        s_activeView = view;

        // initialize new view
        s_activeView->prepare();
        // @TODO: add persistant elements
    }

    /**
     * @TODO: Remove
     */
    void RegisterView(View* view) {
        s_views.insert(s_views.begin(), view);
    }


    View* CreateViewByName(const std::string name) {
        View* v = NULL;
        if      ("Login"        == name) v = new ViewLogin();
        else if ("SelectServer" == name) v = new ViewSelectServer();
        else if ("Lobby"        == name) v = new ViewLobby();
        else if ("Play"         == name) v = new ViewPlay();
        v->name = name;
        return v;
    }
}
