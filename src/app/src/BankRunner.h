#pragma once

#include <atomic>
#include <memory>
#include <bank-calling/service/Bank.h>
#include <thread>
#include <mutex>
#include <functional>
#include <wx/event.h>

namespace Zelinf {
namespace BankCalling {
namespace App {

class BankRunner {
private:
    wxEvtHandler *receiver;
public:
    explicit BankRunner(wxEvtHandler *receiver = nullptr);

    /**
     * Get a smart pointer to the underlying bank model.
     * Note that when using 'bank', you have to call 'getLock()'
     * on it and acquire the lock. Otherwise, race condition will
     * happen.
     * @return A shared_ptr to the bank model.
     */
    std::shared_ptr<Zelinf::BankCalling::Service::Bank> getBank() { return bank; }

    /**
     * Create another thread to simulate a bank-calling system.
     * 'tick' method will be called repeatedly.
     */
    void start();

    /**
     * Pause the running thread.
     */
    void pause();

    /**
     * Release the current 'bank' object and stop the thread.
     */
    void stop();

    /**
     * Resume the paused thread.
     */
    void resume();

    void withBank(std::function<void(std::shared_ptr<Zelinf::BankCalling::Service::Bank>)> callback);

    enum class RunnerState {
        RUNNING, PAUSED, STOPPED
    };

    RunnerState getState() const {
        return state;
    }

    void setCycleTime(int32_t cycleTime) {
        this->cycleTime = cycleTime;
    }

    void setReceiver(wxEvtHandler *receiver) {
        this->receiver = receiver;
    }

private:
    std::shared_ptr<Zelinf::BankCalling::Service::Bank> bank;

    std::recursive_mutex bankLock;

    // cycle time in milliseconds
    std::atomic<int32_t> cycleTime;

    std::atomic<RunnerState> state;

    std::shared_ptr<std::thread> workerTh;

};

}
}
}
