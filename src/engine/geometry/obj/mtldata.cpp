#include "mtldata.h"


namespace sunshine {
namespace engine {


// *****************************************************************************
MtlData::MtlData()
    : Kd(glm::vec3(0.0f)), Ks(glm::vec3(0.0f)), Ka(glm::vec3(0.0f)),
    d(0.0f), Tr(0.0f), Ns(0.0f), illum(0)
{}


// *****************************************************************************
Material MtlData::toMaterial()
{
    Material m;

    m.Ka = Ka;
    m.Kd = Kd;
    m.Ks = Ks;
    m.Ns = Ns;

    return m;
}


} // namespace engine
} // namespace sunshine