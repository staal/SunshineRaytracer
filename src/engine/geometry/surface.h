#ifndef SUNSHINE_ENGINE_SURFACE_H_
#define SUNSHINE_ENGINE_SURFACE_H_

#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "../ray.h"
#include "boundingbox.h"
#include "material.h"

namespace sunshine {
namespace engine{

//! Forward declaration, see \sa Surface.
class Surface;

/*!
    \brief Hit record, used for returning data found in the scene.
*/
struct HitRecord {
    /*! The distance of the ray traveled */
    float t;

    /*! World space point of the hit */
    glm::vec3 point;

    /*! Non owning pointer to the surface hit. */
    const Surface* surface;

    /*! Normal at the point hit */
    glm::vec3 normal;

};

/*!
    \brief The base surface class for geometry
*/
class Surface {
public:
    /*!
        Default constructor.
    */
    Surface(Material* material = nullptr);

    /*!
        Virtual destructor.
    */
    virtual ~Surface();
    
    /*!
        Finds the closest surface going out from Ray r. Populates 
        HitRecord with details of hit point if hit.

        \returns True if it hit anything, false otherwise.
    */
    virtual bool hit(
        const Ray& r, 
        const float start, 
        const float end, 
        HitRecord& rec
        ) const = 0;

    /*!
        Tests if ANYTHING is between point A and point B, early return possible
        compared to hit which returns the closest hit. Returns true if intersect
        otherwise false.
    */
    virtual bool intersects(
        const Ray& r,
        const float start,
        const float end
        ) const = 0;

    /*!
        The bounding box of the surface.
    */
    virtual BoundingBox boundingBox() const = 0;


    /*!
        The material associated with this surface. Non owning pointer.
    */
    Material* material;
};

//! Default Surfaces type.
using Surfaces = std::vector<std::unique_ptr<Surface>>;

} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_SURFACE_H_
