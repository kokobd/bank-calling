#include "BankRunner.h"

#include "gui/InfoUpdateEvent.h"
#include "gui/DataPanel.h"

namespace Zelinf {
namespace BankCalling {
namespace App {

BankRunner::BankRunner(wxEvtHandler *receiver)
        : state(ATOMIC_VAR_INIT(RunnerState::STOPPED)),
          bank(nullptr),
          cycleTime(ATOMIC_VAR_INIT(0)),
          workerTh(nullptr),
          receiver(receiver) {
}

using Zelinf::BankCalling::Service::Bank;

void BankRunner::start() {
    if (state.load() != RunnerState::STOPPED) {
        return;
    }

    {
        std::lock_guard<std::recursive_mutex> guard(bankLock);
        bank = std::make_shared<Bank>(
                std::initializer_list<std::wstring>({L"A", L"B", L"C", L"D", L"E"})
        );
    }

    state = RunnerState::RUNNING;

    workerTh = std::make_shared<std::thread>([this]() {
        while (state.load() != RunnerState::STOPPED) {
            if (state.load() == RunnerState::RUNNING) {
                std::lock_guard<std::recursive_mutex> guard(bank->getLock());
                bank->tick();
//                receiver->QueueEvent(new wxCommandEvent(InfoUpdateEvent));
                receiver->CallAfter(&DataPanel::updateInfo);
                // TODO break if waitingQueue and windows are empty.
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(cycleTime.load()));
        }

        {
            std::lock_guard<std::recursive_mutex> guard(bankLock);
            bank = nullptr;
        }
    });
}

void BankRunner::pause() {
    state = RunnerState::PAUSED;
}

void BankRunner::stop() {
    state = RunnerState::STOPPED;
    workerTh->join();
}

void BankRunner::resume() {
    state = RunnerState::RUNNING;
}

void BankRunner::withBank(std::function<void(std::shared_ptr<Bank>)> callback) {
    std::lock_guard<std::recursive_mutex> guard(bankLock);
    if (bank)
        callback(bank);
}

}
}
}