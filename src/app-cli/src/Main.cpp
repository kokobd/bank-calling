#include <iostream>

#include "Utils.h"
#include "BankRunner.h"
#include <bank-calling/service/Bank.h>

int main() {
    using namespace Zelinf::BankCalling::App;

    int period;
    readVar("Actual length of a logical time unit (ms): ", 1000, period);

    BankRunner runner({"A", "B", "C", "D", "E", "F", "G", "H"}, period);

    double numOfCusMean, numOfCusStdDev;
    readVar<double>("mean of number of new customers per time unit: ", 1.5, numOfCusMean);
    readVar<double>("stddev of number of new customers per time unit: ", 3, numOfCusStdDev);
    runner.bank()->updateCustomerCountGen(numOfCusMean, numOfCusStdDev);

    double expTimeMean, expTimeStdDev;
    readVar<double>("mean of the expected service time of a new customer: ", 3.8, expTimeMean);
    readVar<double>("stddev of the expected service time of a new customer: ", 1.2, expTimeStdDev);
    runner.bank()->updateExpectedServiceTimeGen(expTimeMean, expTimeStdDev);

    runner.run();

    return 0;
}
