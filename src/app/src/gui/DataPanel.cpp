#include "DataPanel.h"
#include <bank-calling/service/Bank.h>
#include <mutex>

namespace Zelinf {
namespace BankCalling {
namespace App {

DataPanel::DataPanel(wxWindow *parent, std::shared_ptr<Bank> bank)
        : wxPanel(parent), bank(bank) {
    initWindowInfo();
    initQueueInfo();
}

void DataPanel::initWindowInfo() {
    windowInfo = new wxGrid(this, wxID_ANY);
    windowInfo->CreateGrid(static_cast<int>(bank->windows().size() + 1),
                           4);

    windowInfo->SetCellValue(0, 0, "窗口名");
    windowInfo->SetCellValue(0, 1, "当前顾客ID");
    windowInfo->SetCellValue(0, 2, "剩余时间");
    windowInfo->SetCellValue(0, 3, "已服务顾客数");

    windowInfo->SetReadOnly(0, 0);
    windowInfo->SetReadOnly(0, 1);
    windowInfo->SetReadOnly(0, 2);
    windowInfo->SetReadOnly(0, 3);

    updateWindowInfo();
}

void DataPanel::initQueueInfo() {
    queueInfo = new wxGrid(this, wxID_ANY);
    queueInfo->CreateGrid(1, 3);

    queueInfo->SetCellValue(0, 0, "队列位置");
    queueInfo->SetCellValue(0, 1, "顾客ID");
    queueInfo->SetCellValue(0, 2, "等待时间");

    updateQueueInfo();
}

void DataPanel::updateWindowInfo() {
    using Zelinf::BankCalling::Service::Window;

    int j = 1;
    for (const auto &p : bank->windows()) {
        windowInfo->SetCellValue(j, 0, p.first);

        Window &window = p.second;
        windowInfo->SetCellValue(j, 1, std::to_string(window.getCurrentCustomer()->getId()));
        windowInfo->SetCellValue(j, 2, std::to_string(window.getLeftTime()));
        windowInfo->SetCellValue(j, 3, std::to_string(window.getNumOfServed()));

        windowInfo->SetReadOnly(j, 0);
        windowInfo->SetReadOnly(j, 1);
        windowInfo->SetReadOnly(j, 2);
        windowInfo->SetReadOnly(j, 3);

        ++j;
    }
}

void DataPanel::updateQueueInfo() {
    using Zelinf::BankCalling::Service::Customer;

    // Delete old rows
    queueInfo->DeleteRows(1, queueInfo->GetNumberRows() - 1);

    const std::deque<std::shared_ptr<Customer>> &waitingQueue = bank->waitingQueue();
    queueInfo->AppendRows(static_cast<int>(waitingQueue.size()));

    for (size_t i = 0; i != waitingQueue.size(); ++i) {
        auto row = static_cast<int>(i + 1);
        queueInfo->SetCellValue(row, 0, std::to_string(row));
        queueInfo->SetCellValue(row, 1, std::to_string(waitingQueue[i]->getId()));
        queueInfo->SetCellValue(row, 2, std::to_string(waitingQueue[i]->getWaitedTime()));
    }
}

void DataPanel::updateInfos() {
    std::lock_guard<std::recursive_mutex> guard(bank->getLock());

    updateWindowInfo();
    updateQueueInfo();
}

}
}
}
