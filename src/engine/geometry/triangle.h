#ifndef SUNSHINE_ENGINE_TRIANGLE_H_
#define SUNSHINE_ENGINE_TRIANGLE_H_

#include "surface.h"

namespace sunshine {
namespace engine{

/*!
    \brief A single vertex entry in a polygon
*/
struct Vertex {
    glm::vec3 v;
    glm::vec3 normal;
};

/*!
    \brief A Triangle implemenentation, a specialization of a surface.
*/
class Triangle : public Surface {
public:
    /*!
        Create the triangle from 3 vertices and an associated material.
    */
    Triangle(Vertex v1, Vertex v2, Vertex v3, Material* mat);

    /*!
        Override of hit function. See \sa sunshine::engine::Surface::hit
    */
    bool hit(
        const Ray &r, 
        const float t0, 
        const float t1, 
        HitRecord& rec
        ) const override;


    /*!
    Override of visible function. See \sa sunshine::engine::Surface::visible
    */
    bool intersects(
        const Ray& r,
        const float start,
        const float end
        ) const override;

    /*!
        Override of boundingBox function. 
        See \sa sunshine::engine::Surface::boundingBox        
    */
    BoundingBox boundingBox() const override;

    /*!
        Compute the area of the triangle
    */
    float area();

    /*!
       The vertices of the triangle. TODO: Privatize! 
    */
    Vertex v1, v2, v3;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_TRIANGLE_H_
