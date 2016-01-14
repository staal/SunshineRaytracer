#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "surface.h"

namespace staal {

struct Vertex {
    glm::vec3 v;
    glm::vec3 normal;
};

class Triangle : public Surface {
public:
    Triangle(Vertex v1, Vertex v2, Vertex v3, Material* mat);
    ~Triangle();
    bool hit(const Ray &r, const float t0, const float t1, HitRecord& rec);
    Box boundingBox();

    Vertex v1, v2, v3;
};


} // namespace staal
#endif // !TRIANGLE_H_