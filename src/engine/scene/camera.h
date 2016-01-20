#ifndef SUNSHINE_ENGINE_CAMERA_H_
#define SUNSHINE_ENGINE_CAMERA_H_

#include "../rayutil.h"

namespace sunshine {
namespace engine{

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 viewDirection, glm::vec3 up, float fov, unsigned int width, unsigned int height);
    ~Camera();
    glm::vec3 getPosition();
    Ray getRay(float x, float y);
    void getOrtographicRay(const int x, const int y, Ray* ray);

private:
    float mWidth, mHeight;
    float mAspect;
    float mDistance;
    glm::vec3 mBasisV, mBasisW, mBasisU, mOrigin;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_CAMERA_H_
