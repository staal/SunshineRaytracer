#ifndef SUNSHINE_ENGINE_IMAGE_H_
#define SUNSHINE_ENGINE_IMAGE_H_

#include <vector>
#include "glm/glm.hpp"

namespace sunshine {
namespace engine{

using RGBA = glm::vec4;
using RGB = glm::vec3;

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
    bool setPixel(unsigned x, unsigned y, const RGB &rgb);
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
