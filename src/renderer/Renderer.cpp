#include "Main.h"
#include "Log.h"
#include "platform/Thread.h"
#include "renderer/ui/UIRenderer.h"
#include "renderer/SceneRenderer.h"
#include "renderer/TextureCache.h"
#include "renderer/Renderer.h"
static Thread* s_thread;
static ThreadLock* s_lockMainThread;
static ThreadLock* s_lockRenderThread;

static void renderProc(void* unused) {
    DisplayDevice::InitGL();
    // SceneRenderer::Init();
    UIRenderer::Init();
    TextureCache::Init();

    // wait for the main thread to be done and tell main thread we're done too
    s_lockMainThread->waitForRelease();
    s_lockRenderThread->release();

    do {
        // SceneRenderer::Render();
        TextureCache::RebuildWhereNecessary();
        UIRenderer::Render();
        DisplayDevice::Swap();
        Sleep(1);
    } while (Main::GetEngine()->isRunning());

    // SceneRenderer::Destroy();
}

namespace Renderer {
    void Init() {
        // create and launch render thread
        s_thread = new Thread((void*)renderProc, (void*)NULL, false);
        s_lockMainThread   = new ThreadLock();
        s_lockRenderThread = new ThreadLock();
        s_thread->start();

        // NOTE: here we can add operations to do while the render thread is loading
        Main::GetEngine()->doActionsWhileRendererStarts();

        // tell the render thread that the main thread is done
        // and wait for render thread to be initialized
        s_lockMainThread->release();
        s_lockRenderThread->waitForRelease();

        // destroy the thread locks
        delete s_lockMainThread;
        delete s_lockRenderThread;
    }

    void Destroy() {
        s_thread->waitUntilDone();
        delete s_thread;
    }
}
