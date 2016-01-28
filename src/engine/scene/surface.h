#ifndef SUNSHINE_ENGINE_SURFACE_H_
#define SUNSHINE_ENGINE_SURFACE_H_

#include <memory>
#include <vector>
#include "glm/glm.hpp"
#include "../rayutil.h"

namespace sunshine {
namespace engine{


struct Material {
    Material()
    {
        Ns = 0.0f;
        Ke = glm::vec3(0.0f);
        Kd = glm::vec3(0.0f);
        Ks = glm::vec3(0.0f);
        Ka = glm::vec3(0.0f);
    }
    ~Material() {}
    glm::vec3 Ka;
    glm::vec3 Kd;
    glm::vec3 Ks;
    glm::vec3 Ke;
    float Ns;
};

class Surface;

struct HitRecord {
    float t;
    Surface* surface;
    glm::vec3 normal;
    glm::vec3 point;
};

class Box {
public:
    Box() { bounds[0] = glm::vec3(); bounds[1] = glm::vec3(); }
    Box(const glm::vec3 min, const glm::vec3 max);
    ~Box();
    bool hit(const Ray& r, const float t0, const float t1);

    glm::vec3 bounds[2];
};

class Surface {
public:
    Surface();
    ~Surface();
    virtual bool hit(const Ray& r, const float t0, const float t1, HitRecord& rec) = 0;
    virtual Box boundingBox() = 0;

    Material* material;
};


using Surfaces = std::vector<std::unique_ptr<Surface>>;
using Materials = std::vector<std::unique_ptr<Material>>;

} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_SURFACE_H_
