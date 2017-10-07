#include <bank-calling/service/Bank.h>
#include <random>
#include <cmath>

namespace Zelinf {
namespace BankCalling {
namespace Service {

Bank::Bank(std::initializer_list<std::string> initialWindowLabels)
        : totalWaitTime(0), totalCustomers(0) {
    for (const std::string &label : initialWindowLabels) {
        windows_.insert({label, Window()});
    }

}

void Bank::tick() {
    int32_t customerCount = customerCountGen.next();
    totalCustomers += customerCount;

    for (int32_t i = 0; i < customerCount; i++) {
        // generate a new customer
        Time expTime = expectedServiceTimeGen.next();
        if (expTime < 2)
            expTime = 2;
        auto newCustomer = std::make_shared<Customer>(expTime);
        waitingQueue_.push_back(newCustomer);
    }

    for (auto &p : windows_) {
        if (waitingQueue_.empty()) {
            p.second.serve(nullptr);
        } else {
            if (p.second.serve(waitingQueue_.front())) {
                waitingQueue_.pop_front();
            }
        }
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ClangTidyInspection"
    for (std::shared_ptr<Customer> customer : waitingQueue_) {
#pragma clang diagnostic pop
        customer->wait();
    }
    totalWaitTime += static_cast<int32_t>(waitingQueue_.size());
}

const std::deque<std::shared_ptr<Customer>> &Bank::waitingQueue() const {
    return waitingQueue_;
}

void Bank::updateCustomerCountGen(double mean, double stddev) {
    customerCountGen.set(mean, stddev);
}

void Bank::updateExpectedServiceTimeGen(double mean, double stddev) {
    expectedServiceTimeGen.set(mean, stddev);
}

bool Bank::empty() const {
    bool isEmpty = waitingQueue_.empty();
    for (const auto &win : windows_) {
        isEmpty = isEmpty && (win.second.getCurrentCustomer() == nullptr);
    }
    return isEmpty;
}

}
}
}
