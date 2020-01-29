#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <GL/gl.h>
#include "Log.h"
#include "resource/ResourceManager.h"
#include "renderer/EntityRenderer.h"

EntityRenderer::EntityRenderer(Scene* scene) {
    std::vector<Entity*>* entities = scene->getEntities();
    for (Entity* e : *entities) {

    }
}

EntityRenderer::~EntityRenderer() {

}

void EntityRenderer::render(Scene* scene) {
    std::vector<Entity*>* entities = scene->getEntities();
    for (Entity* e : *entities) {
        if (!ResourceManager::FindModel(e->modelName))
            Log::Log(Log::WARNING, "Failed to find model '%s'.", e->modelName.c_str());

        // apply model position
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(e->x, e->y, e->z);

        // light attributes
        const GLfloat light_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
        const GLfloat light_diffuse[] = { 0.52f, 0.5f, 0.5f, 1.0f };
        const GLfloat light_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };

        // setup the light attributes
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

        // set the light position
        GLfloat lightPosition[] = { 0.0f, -1.0f, 1.0f, 1.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        // get the renderer of the model
        e->calModel->setLodLevel(1.0f);
        CalRenderer *pCalRenderer = e->calModel->getRenderer();

        // begin the rendering loop
        if (pCalRenderer->beginRendering()) {
            // set global OpenGL states
            glEnable(GL_DEPTH_TEST);
            glShadeModel(GL_SMOOTH);
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);

            // we will use vertex arrays, so enable them
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_NORMAL_ARRAY);

            // get the number of meshes
            int meshCount = pCalRenderer->getMeshCount();

            // render all meshes of the model
            for (int meshId = 0; meshId < meshCount; meshId++) {
                // get the number of submeshes
                int submeshCount = pCalRenderer->getSubmeshCount(meshId);

                // render all submeshes of the mesh
                for (int submeshId = 0; submeshId < submeshCount; submeshId++) {
                    // select mesh and submesh for further data access
                    if (pCalRenderer->selectMeshSubmesh(meshId, submeshId)) {
                        unsigned char meshColor[4];
                        GLfloat materialColor[4];

                        // set the material ambient color
                        pCalRenderer->getAmbientColor(&meshColor[0]);
                        materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
                        glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);

                        // set the material diffuse color
                        pCalRenderer->getDiffuseColor(&meshColor[0]);
                        materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
                        glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);

                        // set the material specular color
                        pCalRenderer->getSpecularColor(&meshColor[0]);
                        materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
                        glMaterialfv(GL_FRONT, GL_SPECULAR, materialColor);

                        // set the material shininess factor
                        float shininess;
                        shininess = 50.0f; //pCalRenderer->getShininess();
                        glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

                        // get the transformed vertices of the submesh
                        static float meshVertices[30000][3];
                        int vertexCount = pCalRenderer->getVertices(&meshVertices[0][0]);

                        // get the transformed normals of the submesh
                        static float meshNormals[30000][3];
                        pCalRenderer->getNormals(&meshNormals[0][0]);

                        // get the texture coordinates of the submesh
                        static float meshTextureCoordinates[30000][2];
                        int textureCoordinateCount = pCalRenderer->getTextureCoordinates(0, &meshTextureCoordinates[0][0]);

                        // get the faces of the submesh
                        static CalIndex meshFaces[50000][3];
                        int faceCount = pCalRenderer->getFaces(&meshFaces[0][0]);

                        // set the vertex and normal buffers
                        glVertexPointer(3, GL_FLOAT, 0, &meshVertices[0][0]);
                        glNormalPointer(GL_FLOAT, 0, &meshNormals[0][0]);

                        // set the texture coordinate buffer and state if necessary
                        if ((pCalRenderer->getMapCount() > 0) && (textureCoordinateCount > 0)) {
                            glEnable(GL_TEXTURE_2D);
                            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                            glEnable(GL_COLOR_MATERIAL);

                            // set the texture id we stored in the map user data
                            TextureResource* tex = (TextureResource*)pCalRenderer->getMapUserData(0);
                            glBindTexture(GL_TEXTURE_2D, (GLuint)tex->texId);

                            // set the texture coordinate buffer
                            glTexCoordPointer(2, GL_FLOAT, 0, &meshTextureCoordinates[0][0]);
                            glColor3f(1.0f, 1.0f, 1.0f);
                        }

                        // draw the submesh
                        if (sizeof(CalIndex) == 2)
                            glDrawElements(GL_TRIANGLES, faceCount * 3, GL_UNSIGNED_SHORT, &meshFaces[0][0]);
                        else
                            glDrawElements(GL_TRIANGLES, faceCount * 3, GL_UNSIGNED_INT, &meshFaces[0][0]);

                        // disable the texture coordinate state if necessary
                        if ((pCalRenderer->getMapCount() > 0) && (textureCoordinateCount > 0)) {
                            glDisable(GL_COLOR_MATERIAL);
                            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                            glDisable(GL_TEXTURE_2D);
                        }
                    }
                }
            }
            // Log::Log(Log::INFO, "%i", m_vertexCount);

            // clear vertex array state
            glDisableClientState(GL_NORMAL_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);

            // clear light
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);
            glDisable(GL_DEPTH_TEST);

            // end the rendering
            pCalRenderer->endRendering();
        }
    }
}
