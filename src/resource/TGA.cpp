#include <string>
#include <vector>
#include <stdlib.h>
#include <stdint.h>
#include "system/ExceptionHandler.h"
#include "resource/File.h"
#include "resource/TGA.h"

#define IMAGETYPE_NONE    0
#define IMAGETYPE_INDEXED 1
#define IMAGETYPE_RGB     2
#define IMAGETYPE_GREY    3
#define IMAGETYPE_RLE     8 // and above

#pragma pack(1)
typedef struct {
    uint8_t  idLength;       // 00h - Size of image ID field
    uint8_t  colorMapType;   // 01h - Color map type (0=none, 1=has palette)
    uint8_t  imageType;      // 02h - Image type code (0=none, 1=indexed, 2=rgb,
                             //                        3=grey, 8+=RLE)
    uint16_t colorMapStart;  // 03h - Color map origin
    uint16_t colorMapLength; // 05h - Color map length
    uint8_t  colorMapDepth;  // 07h - Bits per palette entry (15, 16, 24, 32)

    uint16_t xOffset;        // 08h - Image X origin
    uint16_t yOffset;        // 0Ah - Image Y origin
    uint16_t width;          // 0Ch - Image width in pixels
    uint16_t height;         // 0Eh - Image height in pixels
    uint8_t  pixelBits;      // 10h - Image bits per pixel
    uint8_t  descriptor;     // 11h - Image descriptor (vh flip bits)
} TGAHEADER;
#pragma pack()



TGA::TGA() {

}

TGA::~TGA() {
    delete this->dest;
}


/**
 * Flips the image vertically.
 */
void TGA::flipImageVertically() {
    // int* flippedPixels = (int*)malloc(width * height * 4);
    //
    // for (int row = 0; row < height; row++) {
    //     // Log::Log(Log::INFO, "%i", row * width * 4);
    //     // void* grab = dest + (row * width);
    //     // memcpy(flippedPixels, grab, width * 4);
    //     for (int col = 0; col < width; col++) {
    //         flippedPixels[width * row + col] = (int)127;
    //     }
    // }
    //
    // // memcpy(flippedPixels, dest, width * height * 4);
    //
    // free(dest);
    // dest = (char*)flippedPixels;

    // std::vector<int> flippedPixels(pixels, pixels + size);
    // auto count = flippedPixels.size();
    // std::reverse(flippedPixels.begin(), flippedPixels.end());
    //
    // int* buff = (reinterpret_cast<int*>(&flippedPixels[0]));
    // const void * pnewdata = (const void *)buff;
    // memcpy(pixels, pnewdata, count);
}


void TGA::loadDataRGB(FILEHANDLE* file, int pixels, int dataSize) {
    // read image data
    File_Read(file, this->dest, dataSize);
    // color byte swapping
    for (int swp = 0; swp < dataSize; swp += this->depth)
        this->dest[swp] ^= this->dest[swp+2] ^= this->dest[swp] ^= this->dest[swp+2];

    // flip texture vertically NOTE: this is currently needed because of the renderer itself
    int stride = this->width * this->depth;
    char* tmpRow = new char[stride];
    for (int y = 0; y < this->height / 2;  y++) {
        char* source = this->dest + y * stride;
        char* target = this->dest + (this->height - y - 1) * stride;
        memcpy(tmpRow, source, stride);
        memcpy(source, target, stride);
        memcpy(target, tmpRow, stride);
    }
    delete[] tmpRow;
}

void TGA::loadDataRGBCompressed(FILEHANDLE* file, int pixels, int dataSize) {
    int curPixel   = 0;
    int curByte    = 0;
    char colorBuf[4]; // max 4 bytes per pixel

    do {
        // read chunk header byte
        int chunkHeader = 0;
        File_Read(file, &chunkHeader, 1);

        if (chunkHeader < 128) {
            chunkHeader++;
            for (int counter = 0; counter < chunkHeader; counter++) {
                // try to read 1 pixel
                File_Read(file, colorBuf, depth);

                // write to image data (R and B values are swapped)
                dest[curByte  ] = colorBuf[2];
                dest[curByte+1] = colorBuf[1];
                dest[curByte+2] = colorBuf[0];

                // copy transparency byte if bpp is 32
                if (4 == depth)
                    dest[curByte+3] = colorBuf[3];

                // increase current byte by number of bytes per pixel
                curByte += depth;
                // increment current pixel
                curPixel++;

                // out of bounds check
                if (curPixel > pixels)
                    Log::Log(Log::WARNING, "Too many pixels read in TGA.");
            }
        } else { // chunkheader >= 128
            chunkHeader -= 127;

            File_Read(file, colorBuf, depth);

            for (int counter = 0; counter < chunkHeader; counter++) {
                // write to image data (R and B values are swapped)
                dest[curByte  ] = colorBuf[2];
                dest[curByte+1] = colorBuf[1];
                dest[curByte+2] = colorBuf[0];

                // copy transparency byte if bpp is 32
                if (4 == depth)
                    dest[curByte+3] = colorBuf[3];

                // increase current byte by number of bytes per pixel
                curByte += depth;
                // increment current pixel
                curPixel++;

                // out of bounds check
                if (curPixel > pixels)
                    Log::Log(Log::WARNING, "Too many pixels read in TGA.");
            }
        }
    } while (curPixel < pixels);
}


void TGA::readFile(const char* filename) {
    try {
        // open file
        FILEHANDLE* file = File_OpenRead(filename);
        // read the TGA header (18 bytes)
        TGAHEADER header;
        File_Read(file, &header, sizeof(TGAHEADER));

        // prepare image data
        this->width    = header.width;
        this->height   = header.height;
        this->depth    = header.pixelBits / 8;
        int pixels     = header.width * header.height;
        int dataSize   = pixels * this->depth;
        this->dest     = new char[dataSize];

        // image type check
        if (IMAGETYPE_RGB == header.imageType)
            loadDataRGB(file, pixels, dataSize);
        else if (IMAGETYPE_RLE <= header.imageType) {
            Log::Log(Log::INFO, "Loading RLE TGA image \"%s\"...", filename);
            loadDataRGBCompressed(file, pixels, dataSize);
            // flipImageVertically();
        } else
            throw UnsupportedTGAException(
                std::string("Trying to load unsupported TGA file '") +
                std::string(filename) +
                std::string("' of type ") +
                std::to_string(header.imageType) +
                std::string("."));

        // close file handle
        File_Close(file);
    } catch (BoutEagleException& e) {
        ExceptionHandler::Handle(e);
    }
}
//
//
// /*******************************************************************************
// DESCRIPTION:
//     Load a compressed TGA file from the given file handle object and provided
//     image information struct.
// ARGUMENTS:
//     file - File handle object to read the image data from, please note that the
//            file cursor must be placed at the end of the TGA header (18 bytes).
//     img - Previously created image struct.
// RETURNS:
//     An IMAGE struct filled with the read image data.
// *******************************************************************************/
// static IMAGE loadDataRGBCompressed(FILEHANDLE* file, IMAGE img) {
//     // TODO: restructure this function to look and be more clean
//     GLuint curPixel   = 0;
//     GLuint curByte    = 0;
//     GLubyte colorBuf[4]; // max 4 bytes per pixel
//
//     do {
//         // read chunk header byte
//         GLubyte chunkHeader = 0;
//         File_Read(file, &chunkHeader, 1);
//
//         if (chunkHeader < 128) {
//             chunkHeader++;
//             for (int counter = 0; counter < chunkHeader; counter++) {
//                 // try to read 1 pixel
//                 File_Read(file, colorBuf, img.pixelBytes);
//                 // fread(colorBuf, 1, img.pixelBytes, file);
//
//                 // write to image data (R and B values are swapped)
//                 img.data[curByte  ] = colorBuf[2];
//                 img.data[curByte+1] = colorBuf[1];
//                 img.data[curByte+2] = colorBuf[0];
//
//                 // copy transparency byte if bpp is 32
//                 if (4 == img.pixelBytes)
//                     img.data[curByte+3] = colorBuf[3];
//
//                 // increase current byte by number of bytes per pixel
//                 curByte += img.pixelBytes;
//                 // increment current pixel
//                 curPixel++;
//
//                 // out of bounds check
//                 if (curPixel > img.pixels)
//                     ERROR_("Too many pixels read in TGA.");
//             }
//         } else { // chunkheader >= 128
//             chunkHeader -= 127;
//
//             File_Read(file, colorBuf, img.pixelBytes);
//
//             for (int counter = 0; counter < chunkHeader; counter++) {
//                 // write to image data (R and B values are swapped)
//                 img.data[curByte  ] = colorBuf[2];
//                 img.data[curByte+1] = colorBuf[1];
//                 img.data[curByte+2] = colorBuf[0];
//
//                 // copy transparency byte if bpp is 32
//                 if (4 == img.pixelBytes)
//                     img.data[curByte+3] = colorBuf[3];
//
//                 // increase current byte by number of bytes per pixel
//                 curByte += img.pixelBytes;
//                 // increment current pixel
//                 curPixel++;
//
//                 // out of bounds check
//                 if (curPixel > img.pixels)
//                     ERROR_("Too many pixels read in TGA.");
//             }
//         }
//     } while (curPixel < img.pixels);
//
//     return img;
// }
