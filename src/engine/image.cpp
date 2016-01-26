#include "image.h"

namespace sunshine {
namespace engine{


// *****************************************************************************
Image::Image(unsigned width, unsigned height, bool alpha) :
    data(std::vector<RGBA>(width*height)), mWidth(width), mHeight(height),
    mAlpha(alpha)
{}


// *****************************************************************************
Image::~Image()
{}


// *****************************************************************************
bool Image::setPixel(unsigned x, unsigned y, 
    unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    if (x > mWidth || y > mHeight)
        return false;

    data[y * mWidth + x] = RGBA(
        static_cast<float>(r) / 255.0f,
        static_cast<float>(g) / 255.0f,
        static_cast<float>(b) / 255.0f,
        static_cast<float>(a) / 255.0f);
    return true;
}


// *****************************************************************************
bool Image::setPixel(unsigned x, unsigned y, 
    float r, float g, float b, float a)
{
    if (x >= mWidth || y >= mHeight)
        return false;

    data[y * mWidth + x] = RGBA(r, g, b, a);
    return true;
}


// *****************************************************************************
bool Image::setPixel(unsigned x, unsigned y, const RGBA & rgba)
{
    if (x >= mWidth || y >= mHeight)
        return false;

    data[y * mWidth + x] = rgba;
    return true;
}


// *****************************************************************************
bool Image::setPixel(unsigned i, 
    unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    if (i >= mWidth * mHeight)
        return false;

    data[i] = RGBA(
        static_cast<float>(r) / 255.0f,
        static_cast<float>(g) / 255.0f,
        static_cast<float>(b) / 255.0f,
        static_cast<float>(a) / 255.0f);
    return true;
}


// *****************************************************************************
bool Image::setPixel(unsigned i, unsigned char r, unsigned char g, unsigned char b)
{
    if (i >= mWidth * mHeight)
        return false;

    data[i] = RGBA(
        static_cast<float>(r) / 255.0f,
        static_cast<float>(g) / 255.0f,
        static_cast<float>(b) / 255.0f,
        0.0f);
    return true;
}


// *****************************************************************************
RGBA Image::getPixel(unsigned x, unsigned y) const
{
    if (x < mWidth && y < mHeight)
        return data[y * mWidth + x];
    return RGBA();
}


// *****************************************************************************
unsigned Image::getWidth() const
{
    return mWidth;
}


// *****************************************************************************
unsigned Image::getHeight() const
{
    return mHeight;
}


// *****************************************************************************
bool Image::hasAlpha() const
{
    return mAlpha;
}


} // namespace engine
} // namespace sunshine