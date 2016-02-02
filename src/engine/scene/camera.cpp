#include "camera.h"

namespace sunshine {
namespace engine{

using namespace glm;


// *****************************************************************************
Camera::Camera(vec3 position, vec3 viewDirection, vec3 up, float fov, 
    unsigned int width, unsigned int height)
{
    const float pi = 3.14159265f;

    float radAngle = (fov / 2.0f)* pi / 180.0f; //degree to radian
    this->mDistance = 1.0f / tan(radAngle);
    this->mOrigin = position;
    this->mBasisW = -normalize(viewDirection);
    this->mBasisV = normalize(up);
    this->mBasisU = cross(normalize(viewDirection), normalize(up));

    this->mWidth = static_cast<float>(width);
    this->mHeight = static_cast<float>(height);
    mAspect = mHeight / mWidth;
}


// *****************************************************************************
Camera::~Camera()
{}


// *****************************************************************************
void Camera::getOrtographicRay(int x, int y, Ray* ray)
{
    float r = 10.0f;
    float t = 10.0f;
    float l = -r;
    float b = -t;

    float u = l + (r - l) * (x + 0.5f) / this->mWidth;
    float v = b + (t - b) * (y + 0.5f) / this->mHeight;

    vec3 org = mOrigin + u * mBasisU + v * mBasisV;
    vec3 dir = -mBasisW;

    ray->setRay(org, dir);
}


// *****************************************************************************
vec3 Camera::getPosition()
{
    return vec3(mOrigin);
}


// *****************************************************************************
Ray Camera::getRay(float x, float y)
{
    float r = 1.0f;
    float t = mAspect;
    float l = -r;
    float b = -t;
    float d = mDistance; //Fov

    float u = l + (r - l) * (x + 0.5f) / this->mWidth;
    float v = b + (t - b) * (y + 0.5f) / this->mHeight;

    vec3 org = mOrigin;
    vec3 dir = -d * mBasisW + u * mBasisU + v * mBasisV;

    return Ray(org, dir);
}

} // namespace engine
} // namespace sunshine
