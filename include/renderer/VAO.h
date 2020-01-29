#include <GL/gl.h>
class VAO {
private:
    GLuint vao;
public:
    VAO();
    ~VAO();
    void bind();
};
