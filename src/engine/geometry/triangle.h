#ifndef SUNSHINE_ENGINE_TRIANGLE_H_
#define SUNSHINE_ENGINE_TRIANGLE_H_

#include "surface.h"

namespace sunshine {
namespace engine{

struct Vertex {
    glm::vec3 v;
    glm::vec3 normal;
};

class Triangle : public Surface {
public:
    Triangle(Vertex v1, Vertex v2, Vertex v3, Material* mat);

    bool hit(
        const Ray &r, 
        const float t0, 
        const float t1, 
        HitRecord& rec
        )  override;

    BoundingBox boundingBox() override;

    Vertex v1, v2, v3;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_TRIANGLE_H_
