#ifndef SUNSHINE_ENGINE_MATERIAL_H_
#define SUNSHINE_ENGINE_MATERIAL_H_

#include <memory>
#include <map>

#include <boost/fusion/include/adapt_struct.hpp>
#include <glm/glm.hpp>

namespace sunshine {
namespace engine{


struct Material {
    Material()
    {
        Ns = 0.0f;
        Ke = glm::vec3(0.0f);
        Kd = glm::vec3(0.0f);
        Ks = glm::vec3(0.0f);
        Ka = glm::vec3(0.0f);
    }
    ~Material() {}
    glm::vec3 Ka;
    glm::vec3 Kd;
    glm::vec3 Ks;
    glm::vec3 Ke;
    float Ns;
};

using Materials = std::map<std::string,std::unique_ptr<Material>>;

} // namespace engine
} // namespace sunshine


  /*Adapt structure macros must be called on the global namespace*/
BOOST_FUSION_ADAPT_STRUCT(
    glm::vec3,
    (float, x)
    (float, y)
    (float, z)
    );

/*Only map the part of Material that is naturally occuring in mtl files*/
BOOST_FUSION_ADAPT_STRUCT(
    sunshine::engine::Material,
    (glm::vec3, Ka)
    (glm::vec3, Kd)
    (glm::vec3, Ks)
    (float, Ns)
    );

#endif // !SUNSHINE_ENGINE_MATERIAL_H_
