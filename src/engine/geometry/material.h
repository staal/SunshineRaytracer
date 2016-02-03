#ifndef SUNSHINE_ENGINE_MATERIAL_H_
#define SUNSHINE_ENGINE_MATERIAL_H_

#include <memory>
#include <map>
#include <glm/glm.hpp>

namespace sunshine {
namespace engine{

/*!
    \brief The main material class for the sunshine engine.
*/
struct Material {
    /*!
        Constructor, initialize values.
    */
    Material();

    /*! Ambient color */
    glm::vec3 Ka;

    /*! Diffuse color */
    glm::vec3 Kd;

    /*! Specular color */
    glm::vec3 Ks;

    /*! Emissive color*/
    glm::vec3 Ke;

    /*! Specular exponent */
    float Ns;
};

//! Default Materials type.
using Materials = std::map<std::string,std::unique_ptr<Material>>;

} // namespace engine
} // namespace sunshine



#endif // !SUNSHINE_ENGINE_MATERIAL_H_
