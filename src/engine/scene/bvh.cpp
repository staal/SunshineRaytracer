#include <algorithm>
#include "bvh.h"

namespace sunshine {
namespace engine {


// *****************************************************************************
BoundingBox Bvh::boundingBox()
{
    return mBoundingBox;
}


// *****************************************************************************
BoundingBox Bvh::combine(const BoundingBox& b1, const BoundingBox& b2)
{
    float minx = (b1.bounds[0].x < b2.bounds[0].x) ? b1.bounds[0].x : b2.bounds[0].x;
    float miny = (b1.bounds[0].y < b2.bounds[0].y) ? b1.bounds[0].y : b2.bounds[0].y;
    float minz = (b1.bounds[0].z < b2.bounds[0].z) ? b1.bounds[0].z : b2.bounds[0].z;

    float maxx = (b1.bounds[1].x > b2.bounds[1].x) ? b1.bounds[1].x : b2.bounds[1].x;
    float maxy = (b1.bounds[1].y > b2.bounds[1].y) ? b1.bounds[1].y : b2.bounds[1].y;
    float maxz = (b1.bounds[1].z > b2.bounds[1].z) ? b1.bounds[1].z : b2.bounds[1].z;

    return BoundingBox(glm::vec3(minx, miny, minz), glm::vec3(maxx, maxy, maxz));
}


// *****************************************************************************
class CenterSortFunctor {
private:
    Axis axis;
    float center;
public:
    CenterSortFunctor(Axis axis, float center)
    {
        this->axis = axis; this->center = center;
    }

    bool operator() (const std::unique_ptr<Surface>& surface)
    {
        float triCenter = 0.0f;
        switch (axis) {
            case Axis::X:
                triCenter = (
                    surface->boundingBox().bounds[0].x +
                    surface->boundingBox().bounds[1].x) / 2;
                break;
            case Axis::Y:
                triCenter = (
                    surface->boundingBox().bounds[0].y +
                    surface->boundingBox().bounds[1].y) / 2;
                break;
            case Axis::Z:
            default:
                triCenter = (
                    surface->boundingBox().bounds[0].z +
                    surface->boundingBox().bounds[1].z) / 2;
                break;
        }

        return triCenter < center;
    }
};


// *****************************************************************************
Bvh::Bvh(Surfaces::iterator start, Surfaces::iterator end, Axis axis)
    : mLeft(nullptr), mRight(nullptr)
{
    auto range = end - start;
    if (range == 1) {
        mLeft = std::move(*start);
        mBoundingBox = mLeft->boundingBox();
    } else if (range == 2) {
        mLeft = std::move(*start);
        mRight = std::move(*(start + 1));

        mBoundingBox = combine(mLeft->boundingBox(), mRight->boundingBox());
    } else {
        BoundingBox bigbox = (*start)->boundingBox();
        for (auto it = start; it != end; ++it) {
            bigbox = combine(bigbox, (*it)->boundingBox());
        }

        //find midpoint M (center)
        Axis nextAxis = Axis::X;
        float center = 0.0f;
        switch (axis) {
            case Axis::X:
                center = (bigbox.bounds[1].x + bigbox.bounds[0].x) / 2;
                nextAxis = Axis::Y;
                break;
            case Axis::Y:
                center = (bigbox.bounds[1].y + bigbox.bounds[0].y) / 2;
                nextAxis = Axis::Z;
                break;
            case Axis::Z:
            default:
                center = (bigbox.bounds[1].z + bigbox.bounds[0].z) / 2;
                break;
        }

        //partition around center point on the current axis
        auto mid = std::partition(start, end, CenterSortFunctor(axis, center));

        auto low = mid - start;
        if (low == 0) {
            mid++;
        }
        if (end - mid == 0) {
            mid--;
        }

        mLeft = std::make_unique<Bvh>(start, mid, nextAxis);
        mRight = std::make_unique<Bvh>(mid, end, nextAxis);
        mBoundingBox = combine(mLeft->boundingBox(), mRight->boundingBox());
    }
}


// *****************************************************************************
bool Bvh::hit(const Ray& r, float t0, float t1, HitRecord& rec)
{
    if (mBoundingBox.hit(r, t0, t1)) {

        HitRecord lrec, rrec;
        //Left is never null by construction
        bool leftHit = mLeft->hit(r, t0, t1, lrec);
        bool rightHit = (mRight != nullptr) && mRight->hit(r, t0, t1, rrec);

        if (leftHit && rightHit) {
            if (lrec.t < rrec.t) {
                rec.normal = lrec.normal;
                rec.point = lrec.point;
                rec.surface = lrec.surface;
                rec.t = lrec.t;
                return true;
            } else {
                rec.normal = rrec.normal;
                rec.point = rrec.point;
                rec.surface = rrec.surface;
                rec.t = rrec.t;
                return true;
            }
        } else if (leftHit) {
            rec.normal = lrec.normal;
            rec.point = lrec.point;
            rec.surface = lrec.surface;
            rec.t = lrec.t;
            return true;
        } else if (rightHit) {
            rec.normal = rrec.normal;
            rec.point = rrec.point;
            rec.surface = rrec.surface;
            rec.t = rrec.t;
            return true;
        }
    }

    return false;
}

} // namespace engine
} // namespace sunshine