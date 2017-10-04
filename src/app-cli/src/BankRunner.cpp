#include "BankRunner.h"
#include <string>
#include <bank-calling/service/Bank.h>
#include <thread>
#include <iostream>

namespace Zelinf {
namespace BankCalling {
namespace App {

BankRunner::BankRunner(std::initializer_list<std::wstring> initLabels, int period)
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
    std::wcout << L"\n";
    std::wcout << L"----------\n";
    printCurrentWindowsInfo();
    printCurrentQueueInfo();
    std::flush(std::wcout);
}

void BankRunner::printCurrentWindowsInfo() const {
    std::wcout << L"窗口状态：\n";
    for (const auto &p : bank_->windows()) {
        if (p.second.getCurrentCustomer() != nullptr) {
            std::wcout << L"窗口" << p.first;
            std::wcout << L" <---> ";
            std::wcout << L"顾客" << p.second.getCurrentCustomer()->getId()
                       << L" (" << p.second.getLeftTime() << L"时间单位)\n";
        }
    }

}

void BankRunner::printCurrentQueueInfo() const {
    std::wcout << L"等待队列状态：" << bank_->waitingQueue().size() << L"人\n";
    for (const auto &cus : bank_->waitingQueue()) {
        std::wcout << L"顾客" << cus->getId()
                   << L"已等待" << cus->getWaitedTime()
                   << L"时间单位\n";
    }
}

void BankRunner::printSummary() const {
    std::wcout << L"----------\n";
    std::wcout << L"等待平均时间：" << bank_->averageWaitingTime() << L"\n";
    for (const auto &p : bank_->windows()) {
        std::wcout << L"窗口" << p.first
                   << L"共服务" << p.second.getNumOfServed() << L"位顾客\n";
    }
    std::flush(std::wcout);
}

}
}
}
