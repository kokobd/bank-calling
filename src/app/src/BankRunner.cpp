#include "BankRunner.h"

namespace Zelinf {
namespace BankCalling {
namespace App {

BankRunner::BankRunner() = default;

void BankRunner::start() {
    if (state.load() != RunnerState::STOPPED) {
        return;
    }

    bank = std::make_shared<Bank>({L"A", L"B", L"C", L"D", L"E"});

    workerTh = std::make_shared([&cycleTime, &state, bank]() {
        while (state.load() != RunnerState::STOPPED) {
            if (state.load() == RunnerState::RUNNING) {
                std::lock_guard<std::recursive_mutex> guard(bank->getLock());
                bank->tick();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(cycleTime.load()));
        }
        bank = nullptr;
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

}
}
}