#ifndef LIGHT_SOURCE_H_
#define LIGHT_SOURCE_H_

#include <memory>
#include "../rayutil.h"
#include "../rng.h"
#include "surface.h"
#include "triangle.h"

namespace staal {

class LightSource {
public:
    LightSource(Triangle* t1, Triangle* t2);
    ~LightSource();
    void generatePoint(HitRecord& rec, float* pdf, RNG* rng);

private:
    Triangle* mTriangle[2];
    float mPdf[2];
};


} // namespace staal
#endif // !LIGHT_SOURCE_H_

