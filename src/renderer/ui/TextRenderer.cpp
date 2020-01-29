#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "math/Types.h"
#include "platform/String.h"
#include "platform/Path.h"
#include "renderer/VBO.h"
#include "renderer/ShaderProgram.h"
#include "Log.h"

#define TEXT_HEIGHT 12

static FT_Face s_face;
static ShaderProgram* s_shader;

static const char* s_sourceVert = \
    "void main(void) {"\
    "    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"\
    "    gl_TexCoord[0] = gl_MultiTexCoord0;"\
    "    gl_FrontColor = gl_Color;"\
    "}";
static const char* s_sourceFrag = \
    "uniform sampler2D tex;"\
    "void main(void) {"\
    "    gl_FragColor.rgba = vec4(gl_Color.rgb, texture2D(tex, gl_TexCoord[0].st).r * gl_Color.a);"\
    "}";

static void renderQuad(Vec4i coords) {
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2i  (coords.x0, coords.y0);
    glTexCoord2f(1, 0);
    glVertex2i  (coords.x1, coords.y0);
    glTexCoord2f(1, 1);
    glVertex2i  (coords.x1, coords.y1);
    glTexCoord2f(0, 1);
    glVertex2i  (coords.x0, coords.y1);
    glEnd();
}

namespace TextRenderer {

    void Init() {
        // Initialize freetype
        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            Log::Log(Log::FATAL, "Could not init freetype library.");
        }

        if (FT_New_Face(ft, std::string(Platform::Path::GetFontPath() + "courbd.ttf").c_str(), 0, &s_face)) {
            Log::Log(Log::FATAL, "Could not open font.");
        }

        FT_Set_Pixel_Sizes(s_face, 0, TEXT_HEIGHT);

        // Initialize shader
        s_shader = new ShaderProgram();
        s_shader->addStage(s_sourceVert, VERTEX);
        s_shader->addStage(s_sourceFrag, FRAGMENT);
        s_shader->link();
    }

    Vec2i Render(Vec2i pos, const String text, Vec4f color) {
        float x = pos.x;
        float y = pos.y;

        GLuint tex;
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glUniform1i(glGetUniformLocation(s_shader->getProgram(), "tex"), 0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        VBO vbo;
        glEnableVertexAttribArray(0);
        vbo.bind();
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

        s_shader->use();
        glColor4f(color.r, color.g, color.b, color.a);

        FT_GlyphSlot g = s_face->glyph;
        const char* p;
        for (p = text.c_str(); *p; p++) {
            if (FT_Load_Char(s_face, *p, FT_LOAD_RENDER)) {
                Log::Log(Log::WARNING, "Unable to load char.");
                break;
            }

            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                g->bitmap.width,
                g->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                g->bitmap.buffer
            );

            int x1 = x + g->bitmap.width;
            int y1 = y + g->bitmap.rows;

            renderQuad({
                (int)g->bitmap_left + x,
                TEXT_HEIGHT + y - g->bitmap_top,
                g->bitmap_left + x1,
                TEXT_HEIGHT + y1 - g->bitmap_top
            });

            x += (g->advance.x/64);
            y += (g->advance.y/64);


        }

        return {x, y};
    }

}
