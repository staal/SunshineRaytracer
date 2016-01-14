#include "surface.h"


namespace sunshine {

Surface::Surface()
{}

Surface::~Surface()
{}

//Box implementation

Box::Box(glm::vec3 min, glm::vec3 max)
{
    this->bounds[0] = min;
    this->bounds[1] = max;
}

Box::~Box()
{}

bool Box::hit(const Ray& r, float t0, float t1)
{
    float tmin = (bounds[r.sign[0]].x - r.origin.x) * r.invDirection.x;
    float tmax = (bounds[1 - r.sign[0]].x - r.origin.x) * r.invDirection.x;

    float tymin = (bounds[r.sign[1]].y - r.origin.y) * r.invDirection.y;
    float tymax = (bounds[1 - r.sign[1]].y - r.origin.y) * r.invDirection.y;

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (bounds[r.sign[2]].z - r.origin.z) * r.invDirection.z;
    float tzmax = (bounds[1 - r.sign[2]].z - r.origin.z) * r.invDirection.z;

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    return ((tmin < t1) && (tmax > t0));
}

} // namespace sunshine