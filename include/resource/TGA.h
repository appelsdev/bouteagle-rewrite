#pragma once
#include <string>
#include "resource/File.h"
class TGA {
private:
    int width, height, depth;
    char* dest;
    void flipImageVertically();
    void loadDataRGB(FILEHANDLE* file, int pixels, int dataSize);
    void loadDataRGBCompressed(FILEHANDLE* file, int pixels, int dataSize);
public:
    TGA();
    ~TGA();
    void readFile(const char* filename);

    int getWidth() { return this->width; }
    int getHeight() { return this->height; }
    int getDepth() { return this->depth; }
    char* getPointer() { return this->dest; }
};
