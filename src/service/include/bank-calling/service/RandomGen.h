#pragma once

#include <cstdint>
#include <random>

namespace Zelinf {
namespace BankCalling {
namespace Service {

/**
 * A Random generator that generates int32_t
 * random values, conforming the normal distribution.
 * 'mean' and 'stddev' can be modified on the fly.
 */
class RandomGen {
public:
    /**
     * Construct a random generator.
     * @param mean The mean value, defaults to 0
     * @param stddev The standard deviation, defaults to 1.0
     */
    explicit RandomGen(double mean = 0.0, double stddev = 1.0);

    /**
     * Calculate random int32_t
     * @return the next random int32_t
     */
    int32_t next();

    /**
     * Set the mean value and the standard deviation.
     * This immediately affects the next generated random number.
     * @param mean The mean value
     * @param stddev The standard deviation
     */
    void set(double mean, double stddev);

private:
    std::default_random_engine engine;
    std::normal_distribution<> normal_dist;
};

}
}
}
