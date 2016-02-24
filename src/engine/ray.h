#ifndef SUNSHINE_ENGINE_RAY_H_
#define SUNSHINE_ENGINE_RAY_H_

#include <math.h>
#include <glm/glm.hpp>

namespace sunshine {
namespace engine{


class Ray {
public:
    Ray(const glm::vec3 &o, const glm::vec3 &d)
        : sign{}
    {
        origin = o;
        direction = d;
        invDirection = glm::vec3(1 / d.x, 1 / d.y, 1 / d.z);
        sign[0] = (invDirection.x < 0);
        sign[1] = (invDirection.y < 0);
        sign[2] = (invDirection.z < 0);
    }
    void setRay(const glm::vec3 &o, const glm::vec3 &d)
    {
        origin = o;
        direction = d;
        invDirection = glm::vec3(1 / d.x, 1 / d.y, 1 / d.z);
        sign[0] = (invDirection.x < 0);
        sign[1] = (invDirection.y < 0);
        sign[2] = (invDirection.z < 0);
    }
    glm::vec3 invDirection;
    glm::vec3 origin;
    glm::vec3 direction;
    int sign[3];
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_RAY_H_