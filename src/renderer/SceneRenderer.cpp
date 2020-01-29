#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <GL/gl.h>
#include "resource/ResourceManager.h"
#include "scene/Scene.h"
#include "scene/SceneManager.h"
#include "renderer/ViewMatrix.h"
// #include "renderer/TextureCache.h"
#include "renderer/EntityRenderer.h"
#include "renderer/SceneRenderer.h"
#include "renderer/ui/hud/HUDRenderer.h"

static Scene* s_activeScene;
static ViewMatrix* s_viewMatrix;
static EntityRenderer* s_entityRenderer;

namespace SceneRenderer {
    void Init() {
        s_activeScene = SceneManager::GetActiveScene();
        // TextureCache::Init();
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        s_viewMatrix = new ViewMatrix();
        s_entityRenderer = new EntityRenderer(s_activeScene);

        HUDRenderer::Init();
    }

    void Destroy() {
        delete s_entityRenderer;
        delete s_viewMatrix;
    }

    void Render() {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // set camera matrix
        s_viewMatrix->calcAndApply();


        // render grid
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_LINES);
        for (int i = -100; i <= 100; i += 10) {
            glVertex2f(-100, i);
            glVertex2f(100, i);
            glVertex2f(i, -100);
            glVertex2f(i, 100);
        }
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(100, 0, 0);
        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 100, 0);
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 100);
        glEnd();

        // render entities
        s_entityRenderer->render(s_activeScene);
                        glMatrixMode(GL_PROJECTION);
                        glLoadIdentity();
                        glOrtho(0, (GLdouble)800, 0, (GLdouble)600, -1.0f, 1.0f);

                        HUDRenderer::Render();
                        glMatrixMode(GL_MODELVIEW);
                        glLoadIdentity();
    }

    void ChangeScene(Scene* scene) {

    }
}
