#include <bank-calling/service/Window.h>

namespace Zelinf {
namespace BankCalling {
namespace Service {

Window::Window()
        : currentCustomer(nullptr),
          leftTime(0),
          enabled(true),
          numOfServed(0) {
}

bool Window::serve(std::shared_ptr<Customer> newCustomer) {
    if (leftTime == 0) {
        if (enabled && newCustomer != nullptr) {
            currentCustomer = std::move(newCustomer);
            ++numOfServed;
            leftTime = currentCustomer->getExpectedServiceTime();
            --leftTime;
            return true;
        }
    } else {
        --leftTime;
        if (leftTime == 0) {
            currentCustomer = nullptr;
            ++numOfServed;
        }
    }

    return false;
}

}
}
}
