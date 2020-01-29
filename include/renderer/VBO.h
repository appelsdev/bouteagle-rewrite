#include <GL/gl.h>
class VBO {
private:
    GLuint vbo;
public:
    VBO();
    ~VBO();
    void bind();
};
