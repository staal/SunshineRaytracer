#include "material.h"


namespace sunshine {
namespace engine {

// *****************************************************************************
Material::Material()
    : Ns(0.0f), Ke(glm::vec3(0.0f)), Kd(glm::vec3(0.0f)),
    Ks(glm::vec3(0.0f)), Ka(glm::vec3(0.0f))
{}

} // namespace engine
} // namespace sunshine