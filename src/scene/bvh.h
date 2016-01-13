#ifndef BVH_NODE_H_
#define BVH_NODE_H_

#include <memory>
#include "surface.h"

namespace staal {

enum class Axis {
    X, Y, Z
};

class Bvh : public Surface {
public:
    Bvh(Surfaces::iterator start, Surfaces::iterator end, Axis axis = Axis::X);
    ~Bvh() {}
    bool hit(const Ray& r, const float t0, const float t1, HitRecord& rec);
    Box boundingBox();

private:
    Box mBoundingBox;
    Box combine(const Box b1, const Box b2);

    std::unique_ptr<Surface> mLeft;
    std::unique_ptr<Surface> mRight;
};


} // namespace staal
#endif // !BVH_NODE_H_
