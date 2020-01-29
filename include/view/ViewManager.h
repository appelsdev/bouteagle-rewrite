#pragma once
#include "view/View.h"
#include "view/views/Views.h"

namespace ViewManager {
    void Init();
    void Destroy();
    void UpdateActiveView();
    void SwitchView(std::string name);
    void RegisterView(View* view);
    View* GetActiveView();
    View* CreateViewByName(const std::string name);
}
