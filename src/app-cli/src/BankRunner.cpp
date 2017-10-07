#include "BankRunner.h"
#include <string>
#include <bank-calling/service/Bank.h>
#include <thread>
#include <iostream>

namespace Zelinf {
namespace BankCalling {
namespace App {

BankRunner::BankRunner(std::initializer_list<std::string> initLabels, int period)
        : period(period) {
    bank_ = std::make_shared<Service::Bank>(initLabels);
}

std::shared_ptr<Service::Bank> BankRunner::bank() {
    return bank_;
}

void BankRunner::run() {
    bool notEmpty = true;
    while (notEmpty) {
        std::this_thread::sleep_for(std::chrono::milliseconds(period));
        printCurrentInfo();
        bank_->tick();
        notEmpty = !bank_->empty();
    }
    printSummary();
}

void BankRunner::printCurrentInfo() const {
    std::cout << "\n";
    std::cout << "----------\n";
    printCurrentWindowsInfo();
    printCurrentQueueInfo();
    std::flush(std::cout);
}

void BankRunner::printCurrentWindowsInfo() const {
    std::cout << "Windows Status：\n";
    for (const auto &p : bank_->windows()) {
        if (p.second.getCurrentCustomer() != nullptr) {
            std::cout << "Window " << p.first;
            std::cout << " <---> ";
            std::cout << "Customer " << p.second.getCurrentCustomer()->getId()
                      << " (" << p.second.getLeftTime() << " time units left)\n";
        }
    }

}

void BankRunner::printCurrentQueueInfo() const {
    std::cout << "Waiting Queue Status：" << bank_->waitingQueue().size() << " customers\n";
    for (const auto &cus : bank_->waitingQueue()) {
        std::cout << "Customer " << cus->getId()
                  << " has waited for " << cus->getWaitedTime()
                  << " time units\n";
    }
}

void BankRunner::printSummary() const {
    std::cout << "----------\n";
    std::cout << "Average Waiting Time：" << bank_->averageWaitingTime() << "\n";
    for (const auto &p : bank_->windows()) {
        std::cout << "Window " << p.first
                  << " has served " << p.second.getNumOfServed() << " customers in total.\n";
    }
    std::flush(std::cout);
}

}
}
}
