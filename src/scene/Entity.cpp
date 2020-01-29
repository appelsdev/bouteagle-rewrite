#include <cal3d.h>
#include "Log.h"
#include "platform/Time.h"
#include "resource/ResourceManager.h"
#include "scene/Entity.h"

Entity::Entity() {

}

Entity::~Entity() {

}

void Entity::update() {
    this->calModel->update(Clock::GetElapsedSeconds());
}

void Entity::attachModel(const std::string& modelName) {
    // assign model resource
    CalCoreModel* coreModel = ResourceManager::FindModel(modelName)->coreModel;
    this->modelName = modelName;
    this->calModel = new CalModel(coreModel);
    if (!this->calModel)
        Log::LogCal3d(Log::FATAL);

    // attach meshes to model
    for (int i = 0; i < coreModel->getCoreMeshCount(); i++)
        this->calModel->attachMesh(i);

    // set the material set of the whole model
    this->calModel->setMaterialSet(0);
    // this->calModel->disableInternalData();
    this->calModel->getMorphTargetMixer()->blend(0, 1.0f, 0, 1.00, true);

    // set initial animation state
    /*
    if (coreModel->getCoreAnimationCount() > 0) {
        this->currentAnimationId = 0;
        this->leftAnimationTime = coreModel->getCoreAnimation(this->currentAnimationId)->getDuration() - this->blendTime;
        if (coreModel->getCoreAnimationCount() > 1) {
            this->calModel->getMixer()->executeAction(this->currentAnimationId, 0.0f, this->blendTime);
        } else {
            this->calModel->getMixer()->blendCycle(this->currentAnimationId, 1.0f, 0.0f);
        }
    } else {
        this->currentAnimationId = -1;
        this->leftAnimationTime = -1.0f;
    }
    */
    // update model
    this->calModel->update(1.0f);
}
