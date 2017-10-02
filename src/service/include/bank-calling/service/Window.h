#pragma once

#include <memory>
#include "Customer.h"

namespace Zelinf {
namespace BankCalling {
namespace Service {

/**
 * A Service window.<br>
 * Every service window contain the following properties:
 * <ul>
 *   <li>Enabled</li>
 *   <li>The current customer</li>
 *   <li>Left service time for that customer</li>
 * </ul>
 *
 * Call 'serve' method to simulate another logical second.
 */
class Window {
public:
    /**
     * Construct a default-initialized window, with
     * nullptr current customer, 0 left service time, and enabled.
     */
    Window();

    std::shared_ptr<Customer> getCurrentCustomer() const { return currentCustomer; }

    Time getLeftTime() const { return leftTime; }

    bool isEnabled() const { return enabled; }

    void enable() { enabled = true; }

    int32_t getNumOfServed() const { return numOfServed; }

    /**
     * Work for a logical second. Serve the current customer if there is one.
     * Otherwise, serve the new customer.
     * @param newCustomer Another customer. Might be nullptr if you have none.
     * @return Whether the new customer is consumed.
     */
    bool serve(std::shared_ptr<Customer> newCustomer);

private:
    std::shared_ptr<Customer> currentCustomer;
    Time leftTime;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ClangTidyInspection"
    bool enabled;
#pragma clang diagnostic pop
    int32_t numOfServed;
};

}
}
}
