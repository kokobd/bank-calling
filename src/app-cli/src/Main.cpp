#include <iostream>

#ifndef _WIN32

#include <locale>

#else
#include <io.h>
#include <fcntl.h>
#endif

#include "Utils.h"
#include "BankRunner.h"
#include <bank-calling/service/Bank.h>

int main() {
    using namespace Zelinf::BankCalling::App;

#ifndef _WIN32
    std::wcout.sync_with_stdio(false);
    std::wcout.imbue(std::locale("en_US.utf8"));
#else
    _setmode(_fileno(stdout), _O_U16TEXT)
#endif

    int period;
    readVar(L"逻辑时间单位实际长度(ms)：", 1000, period);

    BankRunner runner({L"A", L"B", L"C", L"D", L"E"}, period);

    double numOfCusMean, numOfCusStdDev;
    readVar<double>(L"每时间单位新顾客数量mean：", 1.5, numOfCusMean);
    readVar<double>(L"每时间单位新顾客数量stddev：", 3, numOfCusStdDev);
    runner.bank()->updateCustomerCountGen(numOfCusMean, numOfCusStdDev);

    double expTimeMean, expTimeStdDev;
    readVar<double>(L"每个新顾客需要的业务时间mean：", 4, expTimeMean);
    readVar<double>(L"每个新顾客需要的业务时间stddev：", 1.2, expTimeStdDev);
    runner.bank()->updateExpectedServiceTimeGen(expTimeMean, expTimeStdDev);

    runner.run();

    return 0;
}
