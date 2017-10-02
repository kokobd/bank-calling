#include <catch/catch.hpp>
#include <bank-calling/service/Bank.h>

TEST_CASE("Bank") {
    using namespace Zelinf::BankCalling::Service;

    Bank bank({L"A", L"B", L"C"});
    bank.tick();
    bank.tick();
    bank.tick();
    // TODO
}
