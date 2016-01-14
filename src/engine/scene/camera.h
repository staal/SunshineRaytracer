#ifndef CAMERA_H_
#define CAMERA_H_

#include "../rayutil.h"

namespace staal {

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


} // namespace staal
#endif // !CAMERA_H_