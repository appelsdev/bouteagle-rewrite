#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <GL/gl.h>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "platform/Window.h"
#include "renderer/ViewMatrix.h"

ViewMatrix::ViewMatrix() {
    this->scale = 1.0f;
    this->tiltAngle = 180.0f;
    this->twistAngle = 180.0f;
    this->distance = -380.0f;
    this->camheight = 0.0f;
}

void ViewMatrix::calcAndApply() {
    // set projection matrix
    glMatrixMode(GL_PROJECTION);
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT,
        0.01f,
        1000.0f);
    glLoadMatrixf(glm::value_ptr(projection));

    // set the model transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // set camera position
    glTranslatef(0.0f, 0.0f, -this->distance * this->scale);
    glRotatef(this->tiltAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(this->twistAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 0.0f, -90.0f * this->scale);
    glTranslatef(0.0f, 0.0f, this->camheight);

}
