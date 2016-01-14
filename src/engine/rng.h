#ifndef RNG_H_
#define RNG_H_

#include <random>

namespace sunshine {

class RNG {
public:
    RNG(unsigned int seed);
    ~RNG();

    void seed(unsigned int seed);

    /* Generate a random number between [0-1) */
    float GetRandom01();
private:
    std::minstd_rand0 generator;
};


} // namespace sunshine
#endif // !RNG_H_

