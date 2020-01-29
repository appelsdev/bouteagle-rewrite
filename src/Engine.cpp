#include "platform/Time.h"
#include "platform/Window.h"
#include "platform/DisplayDevice.h"
#include "platform/InputRouter.h"
#include "resource/ResourceManager.h"
#include "scene/SceneManager.h"
#include "renderer/Renderer.h"
#include "view/ViewManager.h"
#include "acegames/acegames.h"
#include "Engine.h"

void Engine::init() {
    this->running = true;
    Clock::Init();
    Window::Init("BoutEagle");
    DisplayDevice::Init();
    SceneManager::Init();
    ViewManager::Init();
    Renderer::Init();
    Window::Show();
}

void Engine::cleanup() {
    Renderer::Destroy();
    ViewManager::Destroy();
    SceneManager::Destroy();
    DisplayDevice::Destroy();
    Window::Destroy();
}

void Engine::update() {
    InputRouter::Finish();
    Window::PumpMessages();
    ViewManager::UpdateActiveView();
    SceneManager::UpdateActiveScene();
    Clock::Update();
}

bool Engine::isRunning() {
    return this->running;
}

void Engine::doActionsWhileRendererStarts() {
}
