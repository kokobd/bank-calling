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
    if (!enabled) {
        return false;
    }

    if (currentCustomer == nullptr) {
        if (newCustomer != nullptr) {
            currentCustomer = newCustomer;
            leftTime = currentCustomer->getExpectedServiceTime();
            --leftTime;
            return true;
        }
        return false;
    }

    --leftTime;
    if (leftTime == 0) {
        currentCustomer = nullptr;
        ++numOfServed;
        if (newCustomer != nullptr) {
            currentCustomer = newCustomer;
            leftTime = currentCustomer->getExpectedServiceTime();
            return true;
        }
        return false;
    }

    return false;

//    if (leftTime == 0) {
//        if (enabled && newCustomer != nullptr) {
//            ++numOfServed;
//            currentCustomer = std::move(newCustomer);
//            leftTime = currentCustomer->getExpectedServiceTime();
//            --leftTime;
//            return true;
//        }
//    } else {
//        --leftTime;
//        if (leftTime == 0) {
//            ++numOfServed;
//            currentCustomer = nullptr;
//            if (enabled && newCustomer != nullptr) {
//                currentCustomer = std::move(newCustomer);
//                leftTime = currentCustomer->getExpectedServiceTime();
//                return true;
//            }
//        }
//    }
}

}
}
}
