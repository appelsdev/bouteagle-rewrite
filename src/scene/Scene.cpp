#include <vector>
#include "resource/ResourceManager.h"
#include "scene/Player.h"
#include "scene/Scene.h"

Scene::Scene() {
    // ResourceManager::LoadModel("ram/main.cal");
    // activePlayer = new Player();
    // activePlayer->attachModel("ram/main.cal");
    // entities.insert(entities.begin(), activePlayer);
}

Scene::~Scene() {

}

void Scene::update() {
    for (Entity* e : entities) {
        e->update();
    }
}

std::vector<Entity*>* Scene::getEntities() {
    return &entities;
}

Player* Scene::getPlayer() {
    return activePlayer;
}
