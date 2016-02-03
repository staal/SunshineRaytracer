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
    Surface* surface;

    /*! Normal at the point hit */
    glm::vec3 normal;

};

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
        Tests if ray r intersects with this Surface object. Populates 
        HitRecord with details of hit point.
    */
    virtual bool hit(
        const Ray& r, 
        const float t0, 
        const float t1, 
        HitRecord& rec
        ) = 0;

    /*!
        The bounding box of the surface.
    */
    virtual BoundingBox boundingBox() = 0;

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
