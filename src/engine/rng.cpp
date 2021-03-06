
#include <random>
#include "rng.h"

namespace sunshine {
namespace engine{


// *****************************************************************************
RNG::RNG(unsigned int seed) : generator(seed)
{}


// *****************************************************************************
void RNG::seed(unsigned int seed)
{
    generator.seed(seed);
}


// *****************************************************************************
float RNG::GetRandom01()
{
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    return distribution(generator);
}

} // namespace engine
} // namespace sunshine