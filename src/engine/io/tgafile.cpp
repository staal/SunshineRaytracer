
#include <cstdint>
#include <fstream>
#include "tgafile.h"

namespace sunshine {


// *****************************************************************************
/*
Official Targa File header, should be 18 bytes long
*/
struct TgaHeader {
    TgaHeader() : idLength(0), colormapType(0), imageType(0), colormapStart(0),
        colormapLength(0), colormapBits(0), xOrigin(0), yOrigin(0), width(0),
        height(0), bitDepth(0), imageDescriptor(0)
    {}
    uint8_t idLength;
    uint8_t colormapType;
    uint8_t imageType;

    uint16_t colormapStart;
    uint16_t colormapLength;
    uint8_t  colormapBits;

    uint16_t xOrigin;
    uint16_t yOrigin;
    uint16_t width;
    uint16_t height;
    uint8_t  bitDepth;
    uint8_t  imageDescriptor;
};


// *****************************************************************************
TgaFile::TgaFile()
    : mImage(nullptr)
{}


// *****************************************************************************
TgaFile::~TgaFile()
{}


// *****************************************************************************
bool TgaFile::load(std::string filename)
{
    TgaHeader header;

    std::ifstream input(filename, std::ifstream::binary);

    if (!input.good()) {
        return false;
    }
    
    //Read header
    input.read(reinterpret_cast<char*>(&header.idLength), 1);
    input.read(reinterpret_cast<char*>(&header.colormapType), 1);
    input.read(reinterpret_cast<char*>(&header.imageType), 1);
    input.read(reinterpret_cast<char*>(&header.colormapStart), 2);
    input.read(reinterpret_cast<char*>(&header.colormapLength), 2);
    input.read(reinterpret_cast<char*>(&header.colormapBits), 1);
    input.read(reinterpret_cast<char*>(&header.xOrigin), 2);
    input.read(reinterpret_cast<char*>(&header.yOrigin), 2);
    input.read(reinterpret_cast<char*>(&header.width), 2);
    input.read(reinterpret_cast<char*>(&header.height), 2);
    input.read(reinterpret_cast<char*>(&header.bitDepth), 1);
    input.read(reinterpret_cast<char*>(&header.imageDescriptor), 1);

    //Error reading header
    if (!input.good()) {
        return false;
    }

    bool hasAlpha = false;
    switch (header.bitDepth) {
        case 24:
            hasAlpha = false;
            break;
        case 32:
            hasAlpha = true;
            break;
        default:
            //Only 24 and 32 bit depth
            return false;
    }


    mImage = std::make_unique<Image>(header.width, header.height, hasAlpha);

    //Read image data
    switch (header.bitDepth) {
        case 24:
        {
            unsigned char data[3] = { 0 };
            for (int i = 0; i < header.width * header.height; i++) {
                input.read(reinterpret_cast<char*>(data), 3);
                if (!mImage->setPixel(i, data[2], data[1], data[1]) || !input.good()) {
                    mImage = nullptr;
                    return false;
                }
            }
            break;
        }
        case 32:
        {
            unsigned char data[4] = { 0 };
            for (int i = 0; i < header.width * header.height; i++) {
                input.read(reinterpret_cast<char*>(data), 4);
                if (!mImage->setPixel(i, data[2], data[1], data[1], data[3]) || !input.good()) {
                    mImage = nullptr;
                    return false;
                }
            }
            break;
        }

    }
    
    input.close();
    if (!input.good()) {
        mImage = nullptr;
        return false;
    }
    return true;
}


// *****************************************************************************
std::unique_ptr<Image> TgaFile::getImage()
{
    return std::move(mImage);
}


// *****************************************************************************
bool TgaFile::save(std::string filename, const Image & image)
{
    TgaHeader header;

    header.width = image.getWidth();
    header.height = image.getHeight();

    if (image.hasAlpha()) {
        header.bitDepth = 32;
    } else {
        header.bitDepth = 24;
    }
    header.idLength = 0;
    header.colormapType = 0;
    header.imageType = 2;

    header.colormapStart = 0;
    header.colormapLength = 0;
    header.colormapBits = 0;

    header.xOrigin = 0;
    header.yOrigin = 0;

    header.imageDescriptor = 0;


    std::ofstream output(filename, 
        std::ofstream::binary | std::ofstream::trunc);

    if (!output.good()) {
        return false;
    }

    //Write header
    output.write(reinterpret_cast<const char*>(&header.idLength), 1);
    output.write(reinterpret_cast<const char*>(&header.colormapType), 1);
    output.write(reinterpret_cast<const char*>(&header.imageType), 1);
    output.write(reinterpret_cast<const char*>(&header.colormapStart), 2);
    output.write(reinterpret_cast<const char*>(&header.colormapLength), 2);
    output.write(reinterpret_cast<const char*>(&header.colormapBits), 1);
    output.write(reinterpret_cast<const char*>(&header.xOrigin), 2);
    output.write(reinterpret_cast<const char*>(&header.yOrigin), 2);
    output.write(reinterpret_cast<const char*>(&header.width), 2);
    output.write(reinterpret_cast<const char*>(&header.height), 2);
    output.write(reinterpret_cast<const char*>(&header.bitDepth), 1);
    output.write(reinterpret_cast<const char*>(&header.imageDescriptor), 1);
    output.flush();

    //Error writing header
    if (!output.good()) {
        return false;
    }

    //Write image data
    switch (header.bitDepth) {
        case 24:
        {
            for (const auto& pixel : image) {
                unsigned char r = static_cast<unsigned char>(pixel.r * 255);
                unsigned char g = static_cast<unsigned char>(pixel.g * 255);
                unsigned char b = static_cast<unsigned char>(pixel.b * 255);

                output.write(reinterpret_cast<const char*>(&b), 1);
                output.write(reinterpret_cast<const char*>(&g), 1);
                output.write(reinterpret_cast<const char*>(&r), 1);

                if (output.fail()) {
                    mImage = nullptr;
                    return false;
                }
            }
            break;
        }
        case 32:
        {
            for (const auto& pixel : image) {
                unsigned char r = static_cast<unsigned char>(pixel.r * 255);
                unsigned char g = static_cast<unsigned char>(pixel.g * 255);
                unsigned char b = static_cast<unsigned char>(pixel.b * 255);
                unsigned char a = static_cast<unsigned char>(pixel.a * 255);

                output.write(reinterpret_cast<const char*>(&b), 1);
                output.write(reinterpret_cast<const char*>(&g), 1);
                output.write(reinterpret_cast<const char*>(&r), 1);
                output.write(reinterpret_cast<const char*>(&a), 1);

                if (output.fail()) {
                    return false;
                }
            }
            break;
        }

    }

    output.close();
    if (!output.good()) {
        return false;
    }

    return true;
}

} // namespace sunshine