#ifndef SUNSHINE_ENGINE_RNG_H_
#define SUNSHINE_ENGINE_RNG_H_

#include <random>

namespace sunshine {
namespace engine{

class RNG {
public:
    RNG(unsigned int seed);

    void seed(unsigned int seed);

    /* Generate a random number between [0-1) */
    float GetRandom01();
private:
    std::minstd_rand0 generator;
};


} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_RNG_H_

