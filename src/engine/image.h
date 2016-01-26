#ifndef SUNSHINE_ENGINE_IMAGE_H_
#define SUNSHINE_ENGINE_IMAGE_H_

#include <vector>

#include "glm/glm.hpp"

namespace sunshine {
namespace engine {

struct RGBA {
    RGBA() : r(0.0f), g(0.0f), b(0.0f), a(0.0f)
    {}

    RGBA(const glm::vec4& v) : r(v.r), g(v.g), b(v.b), a(v.a)
    {}

    RGBA(const glm::vec3& v) : r(v.r), g(v.g), b(v.b), a(0.0f)
    {}

    RGBA(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
    {}

    void clamp(float min, float max)
    {
        //r
        if (r < min) a = min;
        if (r > max) a = max;

        //g
        if (g < min) a = min;
        if (g > max) a = max;

        //b
        if (b < min) a = min;
        if (b > max) a = max;

        //a
        if (a < min) a = min;
        if (a > max) a = max;
    }

    float r, g, b, a;
};


class Image {
public:
    Image(unsigned width, unsigned height, bool alpha);
    ~Image();

    unsigned getWidth() const;
    unsigned getHeight() const;
    bool hasAlpha() const;
    bool setPixel(unsigned x, unsigned y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    bool setPixel(unsigned x, unsigned y, float r, float g, float b, float a);
    bool setPixel(unsigned x, unsigned y, const RGBA &rgba);
    bool setPixel(unsigned i, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    bool setPixel(unsigned i, unsigned char r, unsigned char g, unsigned char b);

    RGBA getPixel(unsigned x, unsigned y) const;

    std::vector<RGBA>::const_iterator begin() const { return data.begin(); }
    std::vector<RGBA>::const_iterator end() const { return data.end(); }

private:
    unsigned mWidth;
    unsigned mHeight;
    bool mAlpha;
    std::vector<RGBA> data;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_IMAGE_H_
