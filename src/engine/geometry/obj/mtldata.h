#ifndef SUNSHINE_ENGINE_MTL_DATA_H_
#define SUNSHINE_ENGINE_MTL_DATA_H_

#include <memory>
#include <map>
#include <boost/fusion/include/adapt_struct.hpp>
#include <glm/glm.hpp>

#include "../material.h"

namespace sunshine {
namespace engine {

/*!
    \brief The mtl class for data extracted from mtl lib files, associated with
    the OBJ format.
*/
struct MtlData {
    /*!
        Constructor, initialize values.
    */
    MtlData();

    /*!
        Converts the MtlData to a Material object.
    */
    Material toMaterial();

    /*! Ambient color */
    glm::vec3 Ka;

    /*! Diffuse color */
    glm::vec3 Kd;

    /*! Specular color */
    glm::vec3 Ks;

    /*! Transparency*/
    float d;

    /*! Transparency (inverse d)*/
    float Tr;

    /*! Specular exponent */
    float Ns;

    /*! Illumination model*/
    int illum;

};

using MtlMaterials = std::map<std::string, MtlData>;

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
    sunshine::engine::MtlData,
    (glm::vec3, Ka)
    (glm::vec3, Kd)
    (glm::vec3, Ks)
    (float, d)
    (float, Tr)
    (float, Ns)
    (int, illum)
    );


#endif // !SUNSHINE_ENGINE_MTL_DATA_H_