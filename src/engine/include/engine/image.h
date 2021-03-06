#ifndef SUNSHINE_ENGINE_IMAGE_H_
#define SUNSHINE_ENGINE_IMAGE_H_

#include <vector>

namespace sunshine {
namespace engine {

/*!
    \brief A single pixel
*/
struct Pixel {
    Pixel() : r(0.0f), g(0.0f), b(0.0f), a(0.0f)
    {}

    Pixel(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
    {}

    /*! Clamps all fields between min and max. */
    inline void clamp(float min, float max)
    {
        //r
        if (r < min) r = min;
        if (r > max) r = max;

        //g
        if (g < min) g = min;
        if (g > max) g = max;

        //b
        if (b < min) b = min;
        if (b > max) b = max;

        //a
        if (a < min) a = min;
        if (a > max) a = max;
    }

    float r, g, b, a;
};


class Image {
public:
    Image(unsigned width, unsigned height, bool alpha);

    unsigned getWidth() const;
    unsigned getHeight() const;
    bool hasAlpha() const;
    bool setPixel(unsigned x, unsigned y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    bool setPixel(unsigned x, unsigned y, float r, float g, float b, float a);
    bool setPixel(unsigned x, unsigned y, float r, float g, float b);
    bool setPixel(unsigned x, unsigned y, const Pixel &pixel);
    bool setPixel(unsigned i, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    bool setPixel(unsigned i, unsigned char r, unsigned char g, unsigned char b);

    Pixel getPixel(unsigned x, unsigned y) const;

    std::vector<Pixel>::const_iterator begin() const { return data.begin(); }
    std::vector<Pixel>::const_iterator end() const { return data.end(); }

private:
    unsigned mWidth;
    unsigned mHeight;
    bool mAlpha;
    std::vector<Pixel> data;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_IMAGE_H_
