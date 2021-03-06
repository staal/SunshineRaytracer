#ifndef SUNSHINE_ENGINE_CAMERA_H_
#define SUNSHINE_ENGINE_CAMERA_H_

#include "../ray.h"

namespace sunshine {
namespace engine{

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 viewDirection, glm::vec3 up, float fov, 
        unsigned int width, unsigned int height);

    glm::vec3 getPosition() const;
    Ray getRay(float x, float y) const;
    void getOrtographicRay(const int x, const int y, Ray* ray) const;

private:
    float mWidth, mHeight;
    float mAspect;
    float mDistance;
    glm::vec3 mBasisV, mBasisW, mBasisU, mOrigin;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_CAMERA_H_
