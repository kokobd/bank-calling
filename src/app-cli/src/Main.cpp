#include <iostream>
#include <locale>

#include "Utils.h"
#include "BankRunner.h"
#include <bank-calling/service/Bank.h>

int main() {
    using namespace Zelinf::BankCalling::App;

    std::locale::global(std::locale(""));
    setlocale(LC_CTYPE, "");
    std::wcout.imbue(std::locale(""));

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
