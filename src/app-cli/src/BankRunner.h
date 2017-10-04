#pragma once

#include <memory>

namespace Zelinf {
namespace BankCalling {

namespace Service {
class Bank;
}

namespace App {

class BankRunner {
public:
    BankRunner(std::initializer_list<std::wstring> initLabels, int period = 500);

    std::shared_ptr<Service::Bank> bank();

    void run();

private:
    std::shared_ptr<Service::Bank> bank_;

    // period in ms
    int period;

    void printCurrentInfo() const;

    void printCurrentWindowsInfo() const;

    void printCurrentQueueInfo() const;

    void printSummary() const;
};
}
}
}
