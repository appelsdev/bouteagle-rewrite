#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <GL/gl.h>
#include <vector>
#include <cmath>
#include "platform/Time.h"
#include "resource/ResourceManager.h"
#include "renderer/ShaderProgram.h"
#include "renderer/ui/UIRenderer.h"
#include "renderer/ui/TextRenderer.h"
#include "view/ViewManager.h"
#include "view/ui/UIElement.h"
#include "Log.h"

extern std::string g_keyboardString;


static ShaderProgram* s_shader;
static const char* s_shaderSourceVert = \
    "void main(void) {"\
    "    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"\
    "    gl_TexCoord[0] = gl_MultiTexCoord0;"\
    "}";
static const char* s_shaderSourceFrag = \
    "uniform sampler2D tex;"\
    "void main(void) {"\
    "    gl_FragColor.rgba = texture2D(tex, gl_TexCoord[0].st);"\
    "}";


static void renderSpriteIndexed(TextureResource* tex, Vec2i pos, int index, int parts) {
    s_shader->use();
    tex->bind();

    float tHeight = 1.0 / parts;
    float v0 = index * tHeight;
    float v1 = v0 + tHeight;

    int x1 = pos.x + tex->getWidth();
    int y1 = pos.y + (tex->getHeight() / parts);

    glBegin(GL_QUADS);
    glTexCoord2f(0     , v0);
    glVertex2i  (pos.x , pos.y);
    glTexCoord2f(1     , v0);
    glVertex2i  (x1    , pos.y);
    glTexCoord2f(1     , v1);
    glVertex2i  (x1    , y1);
    glTexCoord2f(0     , v1);
    glVertex2i  (pos.x , y1);
    glEnd();
}

static void renderSprite(TextureResource* tex, Vec2i pos) {
    renderSpriteIndexed(tex, pos, 0, 1);
}



/**
 * Renders an image.
 * @param UI::Image
 */
static void renderImage(UI::Image* img) {
    TextureResource* tex = ResourceManager::FindTexture(img->getTexName());
    renderSprite(tex, img->getPos());
}

/**
 * Renders a button.
 * @param UI::Button
 */
static void renderButton(UI::Button* btn) {
    renderSpriteIndexed(
        ResourceManager::FindTexture(btn->getTexName()),
        btn->getPos(),
        btn->getIndex(),
        btn->getParts()
    );
}

/**
 * Renders an animated image.
 * @param UI::Animation
 */
static void renderAnimation(UI::Animation* a) {
    renderSpriteIndexed(
        ResourceManager::FindTexture(a->getTexName()),
        a->getPos(),
        a->getIndex(),
        a->getFrames()
    );
}

/**
 * Renders an edit box with the carat if it's selected.
 * @param UI::EditBox
 */
static void renderEditBox(UI::EditBox* box) {
    std::string text = box->isProtected() ? std::string(box->getText().size(), '*') : box->getText();
    Vec2i caratPos = TextRenderer::Render(
        { box->getBounds().left, box->getBounds().top },
        text,
        {1.0, 1.0, 1.0, 1.0}
    );

    // draw carat
    if ((ViewManager::GetActiveView()->getSelectedEditBox() == box)
    &&  (std::fmod(Clock::GetTime(), 0.4) < 0.2)) {
        renderSprite(
            ResourceManager::FindTexture("data/ui/ui_carat.tga"),
            caratPos
        );
    }
}

/**
 * Renders text.
 * @param UI::Text
 */
static void renderText(UI::Text* t) {
    TextRenderer::Render(
        t->getPos(),
        t->getText(),
        t->getColor()
    );
}

/**
 * Renders an UI element.
 * @param UI::Element
 */
static void renderElement(UI::Element* e) {
    if (UI::IMAGE == e->getType()) {
        renderImage((UI::Image*)e);
    } else if (UI::BUTTON == e->getType()) {
        renderButton((UI::Button*)e);
    } else if (UI::EDITBOX == e->getType()) {
        renderEditBox((UI::EditBox*)e);
    } else if (UI::IMAGE_ANIMATED == e->getType()) {
        renderAnimation((UI::Animation*)e);
    } else if (UI::TEXT == e->getType()) {
        renderText((UI::Text*)e);
    } else if (UI::CONTAINER == e->getType()) {
        UI::Container* c = (UI::Container*)e;
        for (UI::Element* child : c->getChildren()) {
            renderElement(child);
        }
    }
}


namespace UIRenderer {

    void Init() {
        s_shader = new ShaderProgram();
        s_shader->addStage(s_shaderSourceVert, VERTEX);
        s_shader->addStage(s_shaderSourceFrag, FRAGMENT);
        s_shader->link();
        TextRenderer::Init();
        ResourceManager::LoadTexture("data/ui/ui_carat.tga");
    }

    void Render() {

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, (GLdouble)800, (GLdouble)600, 0, -1.0f, 1.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glViewport(0,0, 800, 600);

        for (UI::Element* e : ViewManager::GetActiveView()->getUIElements()) {
            renderElement(e);
        }
    }
}
