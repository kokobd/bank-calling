#pragma once

#include <atomic>
#include <memory>
#include <bank-calling/service/Bank.h>
#include <thread>
#include <mutex>

namespace Zelinf {
namespace BankCalling {
namespace App {

class BankRunner {
public:
    BankRunner();

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
    
private:
    enum class RunnerState {
        RUNNING, PAUSED, STOPPED
    };

private:
    std::shared_ptr<Zelinf::BankCalling::Service::Bank> bank;

    // cycle time in milliseconds
    std::atomic<int32_t> cycleTime;

    std::atomic<RunnerState> state;

    std::shared_ptr<std::thread> workerTh;

};

}
}
}
