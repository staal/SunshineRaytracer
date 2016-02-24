#include "engine/image.h"

namespace sunshine {
namespace engine{


// *****************************************************************************
Image::Image(unsigned width, unsigned height, bool alpha) :
    data(std::vector<Pixel>(width*height)), mWidth(width), mHeight(height),
    mAlpha(alpha)
{}


// *****************************************************************************
bool Image::setPixel(unsigned x, unsigned y, 
    unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    if (x > mWidth || y > mHeight)
        return false;

    data[y * mWidth + x] = Pixel(
        static_cast<float>(r) / 255.0f,
        static_cast<float>(g) / 255.0f,
        static_cast<float>(b) / 255.0f,
        static_cast<float>(a) / 255.0f);
    return true;
}


// *****************************************************************************
bool Image::setPixel(unsigned x, unsigned y, float r, float g, float b, float a)
{
    if (x >= mWidth || y >= mHeight)
        return false;

    data[y * mWidth + x] = Pixel(r, g, b, a);
    return true;
}


// *****************************************************************************
bool Image::setPixel(unsigned x, unsigned y, float r, float g, float b)
{
    if (x >= mWidth || y >= mHeight)
        return false;

    data[y * mWidth + x] = Pixel(r, g, b, 1.0f);
    return true;
}


// *****************************************************************************
bool Image::setPixel(unsigned x, unsigned y, const Pixel &pixel)
{
    if (x >= mWidth || y >= mHeight)
        return false;

    data[y * mWidth + x] = pixel;
    return true;
}


// *****************************************************************************
bool Image::setPixel(unsigned i, 
    unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    if (i >= mWidth * mHeight)
        return false;

    data[i] = Pixel(
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

    data[i] = Pixel(
        static_cast<float>(r) / 255.0f,
        static_cast<float>(g) / 255.0f,
        static_cast<float>(b) / 255.0f,
        1.0f);
    return true;
}


// *****************************************************************************
Pixel Image::getPixel(unsigned x, unsigned y) const
{
    if (x < mWidth && y < mHeight)
        return data[y * mWidth + x];
    return Pixel();
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