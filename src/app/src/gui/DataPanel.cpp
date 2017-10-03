#include "DataPanel.h"
#include <bank-calling/service/Bank.h>
#include <wx/sizer.h>
#include "../BankRunner.h"
#include "InfoUpdateEvent.h"

namespace Zelinf {
namespace BankCalling {
namespace App {

DataPanel::DataPanel(wxWindow *parent, BankRunner &bankRunner)
        : wxPanel(parent), bankRunner(bankRunner) {
    initWindowInfo();
    initQueueInfo();

    auto *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(windowInfo, wxSizerFlags().Border(wxTOP, 10));
    sizer->Add(queueInfo, wxSizerFlags().Border(wxTOP, 20));
    SetSizer(sizer);

//    Bind(InfoUpdateEvent, &DataPanel::onUpdateInfo, this, GetId());
}

void DataPanel::initWindowInfo() {
    windowInfo = new wxGrid(this, wxID_ANY);
    windowInfo->CreateGrid(1, 4);
    windowInfo->HideRowLabels();

    windowInfo->SetColLabelValue(0, wxT("窗口名"));
    windowInfo->SetColLabelValue(1, wxT("当前顾客ID"));
    windowInfo->SetColLabelValue(2, wxT("剩余时间"));
    windowInfo->SetColLabelValue(3, wxT("已服务顾客数"));

    updateWindowInfo();
}

void DataPanel::initQueueInfo() {
    queueInfo = new wxGrid(this, wxID_ANY);
    queueInfo->CreateGrid(1, 3);
    queueInfo->HideRowLabels();

    queueInfo->SetColLabelValue(0, wxT("队列位置"));
    queueInfo->SetColLabelValue(1, wxT("顾客ID"));
    queueInfo->SetColLabelValue(2, wxT("等待时间"));

    updateQueueInfo();
}

void clearTableContents(wxGrid *table) {
    int rows = table->GetNumberRows();
    if (rows > 0) {
        table->DeleteRows(0, rows);
    }
}

void DataPanel::updateWindowInfo() {
    using Zelinf::BankCalling::Service::Window;

    clearTableContents(windowInfo);

    if (bankRunner.getBank() == nullptr) {
        return;
    }

    windowInfo->AppendRows(static_cast<int>(bankRunner.getBank()->windows().size()));

    int j = 0;
    for (const auto &p : bankRunner.getBank()->windows()) {
        windowInfo->SetCellValue(j, 0, p.first);

        const Window &window = p.second;
        if (window.getCurrentCustomer() != nullptr) {
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
}

void DataPanel::updateQueueInfo() {
    using Zelinf::BankCalling::Service::Customer;

    clearTableContents(queueInfo);

    if (bankRunner.getBank() == nullptr) {
        return;
    }

    const std::deque<std::shared_ptr<Customer>> &waitingQueue = bankRunner.getBank()->waitingQueue();
    queueInfo->AppendRows(static_cast<int>(waitingQueue.size()));

    for (size_t i = 0; i != waitingQueue.size(); ++i) {
        auto row = static_cast<int>(i);
        queueInfo->SetCellValue(row, 0, std::to_string(row + 1));
        queueInfo->SetCellValue(row, 1, std::to_string(waitingQueue[i]->getId()));
        queueInfo->SetCellValue(row, 2, std::to_string(waitingQueue[i]->getWaitedTime()));

        queueInfo->SetReadOnly(row, 0);
        queueInfo->SetReadOnly(row, 1);
        queueInfo->SetReadOnly(row, 2);
    }
}

void DataPanel::updateInfo() {
    std::lock_guard<std::recursive_mutex> guard(bankRunner.getBank()->getLock());

    updateWindowInfo();
    updateQueueInfo();
}

void DataPanel::onUpdateInfo(wxCommandEvent &event) {
    updateInfo();
}

}
}
}
