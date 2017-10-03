#pragma once

#include <map>
#include <deque>
#include <cstdint>
#include <initializer_list>
#include "Window.h"
#include "RandomGen.h"
#include <string>
#include <mutex>

namespace Zelinf {
namespace BankCalling {
namespace Service {

/**
 * Bank simulates a bank-calling system.<br>
 * See 'tick' method to learn what will happen in each logical second.
 */
class Bank {
private:
    // (label, window)
    std::map<std::wstring, Window> windows_;

    // back-in, front-out
    std::deque<std::shared_ptr<Customer>> waitingQueue_;

    int32_t totalWaitTime;
    int32_t totalCustomers;

public:
    /**
     * Constructs a Bank object with initial labels of service windows.
     * Corresponding number of service windows will be created.
     * @param initialWindowLabels Initial labels of service windows.
     */
    Bank(std::initializer_list<std::wstring> initialWindowLabels);

    /**
     * Get a view of the current service windows.
     * @return A map from label to window object.
     */
    const std::map<std::wstring, Window> &windows() const { return windows_; }

    /**
     * Get a view of the current waiting queue.
     * @return A queue of customers.
     */
    const std::deque<std::shared_ptr<Customer>> &waitingQueue() const;

    /**
     * Run another logical second.
     * During every logic second, following things will happen:
     * <ul>
     *   <li>
     *     Random number of new customers are generated and pushed to the
     *     back of the waiting queue. For each newly generated customer,
     *     his/her expected waiting time is also generated randomly. You
     *     may change the random parameters by modifying 'customerCountGen'
     *     and 'expectedServiceTimeGen' properties.
     *   </li>
     *   <li>
     *     All service window will serve their customers for a second. If
     *     no customer is there for a window, another customer will leave
     *     the waiting queue and get served, for a logical second.
     *   </li>
     * </ul>
     */
    void tick();

    /**
     * Get the average waiting time, up to now.
     * @return the average waiting time.
     */
    double averageWaitingTime() const {
        return static_cast<double>(totalWaitTime) / static_cast<double>(totalCustomers);
    }

//    /**
//     * Start a 'transaction'. Before calling 'commitTrans',
//     * no other thread could return from startTrans.
//     */
//    void startTrans();
//
//    /**
//     * Commit a 'transaction'. Other threads could then
//     * return from 'startTrans'.
//     */
//    void commitTrans();

private:
    RandomGen customerCountGen;
    RandomGen expectedServiceTimeGen;

public:
    void updateCustomerCountGen(double mean, double stddev);

    void updateExpectedServiceTimeGen(double mean, double stddev);

private:
    std::recursive_mutex lock;

public:
    std::recursive_mutex &getLock() { return lock; }
};

}
}
}