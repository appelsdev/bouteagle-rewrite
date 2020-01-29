#include <libxml/parser.h>
#include <libxml/tree.h>
#include "platform/String.h"
#include "platform/Path.h"
#include "view/View.h"
#include "view/ViewManager.h"
#include "Log.h"

static void parseViewContents(xmlNode* node, View* view, Vec2i parentPos) {
    for (xmlNode* n = node; n; n = n->next) {
        if (XML_ELEMENT_NODE != n->type) continue;

        UI::Element* el = NULL;
        std::vector<int> pos(0, 0);

        // Images
        if (!xmlStrcmp((const xmlChar*)"image", n->name)) {
            UI::Image* img = new UI::Image();

            for (xmlAttr* property = n->properties; property; property = property->next) {

                // name
                if (!xmlStrcmp((const xmlChar*)"name", property->name)) {
                    img->setName((char*)property->children->content);
                }

                // src
                else if (!xmlStrcmp((const xmlChar*)"src", property->name)) {
                    img->assignTexture((char*)property->children->content);
                }

                // pos
                else if (!xmlStrcmp((const xmlChar*)"pos", property->name)) {
                    pos = Platform::StringToIntegers(std::string((char*)property->children->content));
                    if (parentPos.x || parentPos.y) {
                        pos[0] += parentPos.x;
                        pos[1] += parentPos.y;
                    }
                    img->setPos({pos[0], pos[1]});
                }
                std::string name = img->getName();

                Log::Log(Log::INFO, "Image %s", name.c_str());

            }
            el = img;

        }

        // Buttons
        else if (!xmlStrcmp((const xmlChar*)"button", n->name)) {
            UI::Button* btn = new UI::Button();

            for (xmlAttr* property = n->properties; property; property = property->next) {

                // name
                if (!xmlStrcmp((const xmlChar*)"name", property->name)) {
                    btn->setName((char*)property->children->content);
                }

                // src
                else if (!xmlStrcmp((const xmlChar*)"src", property->name)) {
                    btn->assignTexture((char*)property->children->content);
                }

                // pos
                else if (!xmlStrcmp((const xmlChar*)"pos", property->name)) {
                    pos = Platform::StringToIntegers(std::string((char*)property->children->content));
                    if (parentPos.x || parentPos.y) {
                        pos[0] += parentPos.x;
                        pos[1] += parentPos.y;
                    }
                    btn->setPos({pos[0], pos[1]});
                }

            }
            el = btn;

        }

        Vec2i parentPosNew;
        if (el) {
            view->addUIElement(el);
            parentPosNew = el->getPos();
        } else {
            parentPosNew = {0, 0};
        }
        parseViewContents(n->children, view, parentPosNew);

    }

}

static std::vector<View*> parseTemplate(xmlNode* node) {
    std::vector<View*> views;
    for (xmlNode* n = node; n; n = n->next) {
        if (XML_ELEMENT_NODE != n->type) continue;

        if (!xmlStrcmp((const xmlChar*)"view", n->name)) {
            for (xmlAttr* property = n->properties; property; property = property->next) {
                if (xmlStrcmp((const xmlChar*)"name", property->name)) continue;

                std::string viewName = std::string((char*)property->children->content);
                View* v = ViewManager::CreateViewByName(viewName);
                parseViewContents(n->children, v, {0,0});
                views.push_back(v);

            }

        }
    }
    return views;
}



namespace TemplateParser {

std::vector<View*> LoadViews() {
    std::vector<View*> views;
    std::vector<String> filenames = Platform::Path::ListFiles("assets/templates/");
    for (auto& filename : filenames) {
        xmlDocPtr doc;
        doc = xmlReadFile(filename.c_str(), NULL, 0);
        if (doc == NULL) {
            Log::Log(Log::FATAL, "Failed to parse %s\n", filename.c_str());
        }

        std::vector<View*> foundViews = parseTemplate(xmlDocGetRootElement(doc));
        views.insert(views.end(), foundViews.begin(), foundViews.end());


        xmlFreeDoc(doc);
        // Log::Log(Log::INFO, filename.c_str());
    }
    xmlCleanupParser();
    return views;
}

}
