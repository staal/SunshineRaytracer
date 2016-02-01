#ifndef SUNSHINE_ENGINE_LIGHT_SOURCE_H_
#define SUNSHINE_ENGINE_LIGHT_SOURCE_H_

#include <memory>
#include "../rayutil.h"
#include "../rng.h"
#include "../geometry/surface.h"
#include "../geometry/triangle.h"

namespace sunshine {
namespace engine{

class LightSource {
public:
    LightSource(Triangle* t1, Triangle* t2);
    ~LightSource();
    void generatePoint(HitRecord& rec, float* pdf, RNG* rng);

private:
    Triangle* mTriangle[2];
    float mPdf[2];
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_LIGHT_SOURCE_H_

