#include <string>
#include <cal3d.h>
#include "Log.h"
#include "resource/ResourceManager.h"
#include "resource/TextureResource.h"
#include "resource/ModelResource.h"

ModelResource::ModelResource(const std::string& filename) {
    this->coreModel = new CalCoreModel(filename);
    if (!this->coreModel)
        Log::LogCal3d(Log::FATAL);

    this->parseModelConfig(filename);

    // make one material thread for each material
    // NOTE: this is not the right way to do it, but this viewer can't do the right
    // mapping without further information on the model etc., so this is the only
    // thing we can do here.
    int materialId;
    for (materialId = 0; materialId < this->coreModel->getCoreMaterialCount(); materialId++) {
        // create the a material thread
        this->coreModel->createCoreMaterialThread(materialId);
        // initialize the material thread
        this->coreModel->setCoreMaterialId(materialId, 0, materialId);
    }

    // load all textures and store the opengl texture id in the corresponding map in the material
    for (int materialId = 0; materialId < coreModel->getCoreMaterialCount(); materialId++) {
        // get the core material
        CalCoreMaterial *pCoreMaterial = coreModel->getCoreMaterial(materialId);

        // loop through all maps of the core material
        for (int mapId = 0; mapId < pCoreMaterial->getMapCount(); mapId++) {
            // get the filename of the texture
            std::string texFilename = pCoreMaterial->getMapFilename(mapId);
            // load the texture from the file
            TextureResource* texture = ResourceManager::LoadTexture(texFilename);
            // store texture reference
            pCoreMaterial->setMapUserData(mapId, (Cal::UserData)texture);
        }
    }
}

ModelResource::~ModelResource() {
    // TODO: unload textures if unused by other models
}

// TODO: create new parser from scratch
void ModelResource::parseModelConfig(const std::string& filename) {
    // open the model configuration file
    std::ifstream file;
    file.open(filename.c_str(), std::ios::in | std::ios::binary);
    if (!file)
        Log::Log(Log::FATAL, "Failed to open model configuration file '%s'.", filename.c_str());

    // parse all lines from the model configuration file
    int line;
    for (line = 1;; line++) {
        // read the next model configuration line
        std::string strBuffer;
        std::getline(file, strBuffer);

        // stop if we reached the end of file
        if (file.eof()) break;

        // check if an error happened while reading from the file
        if (!file)
            Log::Log(Log::FATAL, "Error while reading from the model configuration file '%s'.", filename.c_str());

        // find the first non-whitespace character
        std::string::size_type pos;
        pos = strBuffer.find_first_not_of(" \t");

        // check for empty lines
        if ((pos == std::string::npos) || (strBuffer[pos] == '\n') || (strBuffer[pos] == '\r') || (strBuffer[pos] == 0)) continue;

        // check for comment lines
        if (strBuffer[pos] == '#') continue;

        // get the key
        std::string strKey;
        strKey = strBuffer.substr(pos, strBuffer.find_first_of(" _=\t\n\r", pos) - pos);
        pos += strKey.size();

        // get the '=' character
        pos = strBuffer.find_first_of("=", pos);
        if ((pos == std::string::npos) || (strBuffer[pos] != '='))
            Log::Log(Log::FATAL, "'%s' (%i): Invalid syntax.", filename.c_str(), line);

        // find the first non-whitespace character after the '=' character
        pos = strBuffer.find_first_not_of(" \t", pos + 1);

        // get the data
        std::string strData;
        strData = strBuffer.substr(pos, strBuffer.find_first_of("\n\r", pos) - pos);

        // handle the model creation
        if (strKey == "scale") {
            // set rendering scale factor
            // Log::Log(Log::INFO, "Setting scale '%s'...", strData.c_str());
            this->scale = atof(strData.c_str());
        } else if (strKey == "skeleton") {
            // load core skeleton
            // Log::Log(Log::INFO, "Loading skeleton '%s'...", strData.c_str());
            if (!this->coreModel->loadCoreSkeleton(strData))
                Log::LogCal3d(Log::FATAL);
        } else if (strKey == "animation") {
            // load core animation
            // Log::Log(Log::INFO, "Loading animation '%s'...", strData.c_str());
            if (this->coreModel->loadCoreAnimation(strData) == -1)
                Log::LogCal3d(Log::FATAL);
        } else if (strKey == "mesh") {
            // load core mesh
            // Log::Log(Log::INFO, "Loading mesh '%s'...", strData.c_str());
            if (this->coreModel->loadCoreMesh(strData) == -1)
                Log::LogCal3d(Log::FATAL);
            this->coreModel->getCoreMesh(this->coreModel->getCoreMeshCount() - 1)->setName
                (strData.substr(0, strData.length() - 4));
        } else if (strKey == "blendmesh") {
            for (int i = 0; i<this->coreModel->getCoreMeshCount(); i++){
                ///search over all meshes basemesh of this morphmesh
                /// morphname=basemeshname+something
                std::string name = this->coreModel->getCoreMesh(i)->getName();
                unsigned int subs = strData.find(name);
                if (subs<strData.length()){
                    // Log::Log(Log::INFO, "Loading mesh '%s' as morphtarget...", strData.c_str());
                    CalCoreMeshPtr pCoreMesh = CalLoader::loadCoreMesh(strData);
                    if (!pCoreMesh) {
                        Log::Log(Log::WARNING, "Unable to load mesh '%s'.", strData.c_str());
                        Log::LogCal3d(Log::FATAL);
                    }

                    this->coreModel->getCoreMesh(i)->addAsMorphTarget(pCoreMesh.get());
                    break;
                }
            }
        } else if (strKey == "morphanim") {
            // load core mesh
            Log::Log(Log::INFO, "Loading Blend shape anim '%s'...", strData.c_str());
            if (this->coreModel->loadCoreAnimatedMorph(strData) == -1)
                Log::LogCal3d(Log::FATAL);

        } else if (strKey == "material") {
            // load core material
            // Log::Log(Log::INFO, "Loading material '%s'...", strData.c_str());
            if (this->coreModel->loadCoreMaterial(strData) == -1)
                Log::LogCal3d(Log::FATAL);
        } else {
            // everything else triggers an error message, but is ignored
            Log::Log(Log::FATAL, "'%s' (%i): Invalid syntax.", filename.c_str(), line);
        }
    }

    // explicitely close the file
    file.close();
}
