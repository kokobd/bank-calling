#pragma once

#include <cstdint>
#include <atomic>
#include <memory>

namespace Zelinf {
namespace BankCalling {
namespace Service {

using Time = int32_t;

class Customer {
public:
    using ID = int32_t;

    explicit Customer(Time expectedServiceTime)
            : id(id),
              waitedTime(0),
              expectedServiceTime(expectedServiceTime) {
        id = nextId++;
    }

    ID getId() const { return id; }

    Time getWaitedTime() const { return waitedTime; }

    Time getExpectedServiceTime() const { return expectedServiceTime; }

    void wait() { ++waitedTime; }

private:
    ID id;
    Time waitedTime;
    Time expectedServiceTime;

    static std::atomic<ID> nextId;
};

}
}
}
