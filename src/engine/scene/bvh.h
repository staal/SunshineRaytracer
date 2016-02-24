#ifndef SUNSHINE_ENGINE_BVH_NODE_H_
#define SUNSHINE_ENGINE_BVH_NODE_H_

#include <memory>
#include "../geometry/surface.h"

namespace sunshine {
namespace engine{

/*!
    \brief Bounding volume hierarchy implementation 
*/
class Bvh : public Surface {
public:
    /*! Pivot axis for building the Bvh */
    enum class Axis {
        X, Y, Z
    };


    Bvh(Surfaces::iterator start, Surfaces::iterator end, Axis axis = Axis::X);

    bool hit(
        const Ray& r, 
        const float t0, 
        const float t1, 
        HitRecord& rec
        ) const override;

    BoundingBox boundingBox() const override;

private:
    BoundingBox mBoundingBox;
    BoundingBox combine(const BoundingBox& b1, const BoundingBox& b2);

    std::unique_ptr<Surface> mLeft;
    std::unique_ptr<Surface> mRight;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_BVH_NODE_H_
