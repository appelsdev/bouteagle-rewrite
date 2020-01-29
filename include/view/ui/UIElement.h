#pragma once
#include <vector>
#include <string>
#include "math/Types.h"
#include "resource/TextureResource.h"
namespace UI {

typedef enum {
    BUTTON, IMAGE, EDITBOX, IMAGE_ANIMATED, CONTAINER, TEXT
} ElementType;


class Element {
    protected:
        ElementType type;
        std::string name = "";
        Vec2i pos = {0, 0};
        bool persistant = false;
    public:
        // virtual functions
        virtual void update() {};
        virtual void destroy() {};

        // getters
        ElementType getType();
        Vec2i getPos();
        const std::string& getName();
        bool isPersistant();

        // setters
        void setPos(Vec2i pos);
        void setName(const std::string& name);
        void setPersistant(bool x);
};


class Container : public Element {
    private:
        std::vector<Element*> children;
    public:
        Container();
        std::vector<Element*> getChildren();
        void addElement(UI::Element* e);
        void update();
        void destroy();
};


class Hoverable {
    protected:
        Vec4i bounds;
    public:
        bool isHovered();
        void setBounds(Vec4i bounds);
        Vec4i getBounds();
};



class Clickable : public Hoverable {
    protected:
        int index;
        bool clicked;
    public:
        int getIndex();
        bool updateStateAndCheckClicked();
};


/*******************************************************************************
 * Image
 ******************************************************************************/
class Image : public Element {
    protected:
        std::string texName;
    public:
        Image();
        void assignTexture(const std::string& filename);
        const std::string& getTexName();
};

/*******************************************************************************
 * Animated Image
 ******************************************************************************/
class Animation : public Image {
    private:
        int frames;
        double index = 0.0;
    public:
        Animation();
        int getFrames();
        int getIndex();
        void setFrames(int frames);
        void update();
};

/*******************************************************************************
 * Text
 ******************************************************************************/
class Text : public Element {
    private:
        std::string text;
        Vec4f color;
    public:
        Text();
        void setColor(Vec4f color);
        void setText(const std::string& text);
        const std::string& getText();
        Vec4f getColor();
};


/*******************************************************************************
 * Button
 ******************************************************************************/
class Button : public Image, public Clickable {
private:
    int parts = 4;
public:
    Button();
    int getParts();
    void setParts(int parts);
    void update();
    void setPos(Vec2i pos);
};

/*******************************************************************************
 * EditBox
 ******************************************************************************/
class EditBox : public Element, public Clickable {
private:
    bool protect;
    std::string text;
    int maxChars;
public:
    EditBox();
    const std::string& getText();
    void clearText();
    void update();
    int getMaxChars();
    void setMaxChars(int num);
    bool isProtected();
    void setProtected(bool protect);
    void handleChar(int scancode);

};




/*******************************************************************************
 * LoginBox
 ******************************************************************************/
class LoginBox : public Container {
private:

public:
    LoginBox();

};

/*******************************************************************************
 * Create bot dialog in lobby screen
 ******************************************************************************/
class CreateBotDialog : public Container {
public:
    CreateBotDialog() {};
};


/*******************************************************************************
 * Generic messagebox
 ******************************************************************************/
void ShowMessageBox(const std::string& text);

void RemoveMessageBoxes();

}
