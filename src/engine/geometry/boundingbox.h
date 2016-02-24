#ifndef SUNSHINE_ENGINE_BOUNDINGBOX_H_
#define SUNSHINE_ENGINE_BOUNDINGBOX_H_

#include <glm/glm.hpp>

#include "../ray.h"

namespace sunshine {
namespace engine {

/*!
    \brief Bounding Box between min point and max point.
*/
class BoundingBox {
public:
    /*!
        Initialize zero size bounding box.
    */
    BoundingBox() { bounds[0] = glm::vec3(); bounds[1] = glm::vec3(); }

    /*!
        Create a bounding box from the given parameters.
        \param min lower corner of bounding box
        \param max upper corner of bounding box
    */
    BoundingBox(const glm::vec3 min, const glm::vec3 max);

    /*!
        A simple intersection method. Tests if ray r intersects the box.

        \param r the ray to test.
        \param t0 min length of ray
        \param t1 max length of ray
    */
    bool hit(const Ray& r, const float t0, const float t1) const;

    /*!
        The bounds of the bounding box. Index 0 is the lower point. Index 1
        is the upper point.
    */
    glm::vec3 bounds[2];
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_BOUNDINGBOX_H_
