#pragma once
#include <string>
#include "math/Types.h"
namespace TextRenderer {
    void Init();
    Vec2i Render(Vec2i pos, std::string text, Vec4f color);
}
