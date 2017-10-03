#include <bank-calling/service/RandomGen.h>

#include <cmath>

namespace Zelinf {
namespace BankCalling {
namespace Service {


RandomGen::RandomGen(double mean, double stddev) : normal_dist(mean, stddev) {
}

int32_t RandomGen::next() {
    return static_cast<int32_t>(
            std::floor(std::fabs(normal_dist(engine)))
    );
}

void RandomGen::set(double mean, double stddev) {
    normal_dist.param(std::normal_distribution<>::param_type(mean, stddev));
}

}
}
}
