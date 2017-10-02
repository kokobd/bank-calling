#include <catch/catch.hpp>
#include <bank-calling/service/Customer.h>
#include <set>

namespace BCS = Zelinf::BankCalling::Service;

TEST_CASE("Customer") {
    SECTION("No same IDs") {
        std::set<BCS::Customer::ID> existingIds;
        bool noClash = true;
        for (int i = 0; i < 300 && noClash; i++) {
            auto customer = std::make_shared<BCS::Customer>(10);
            noClash &= existingIds.find(customer->getId()) == existingIds.end();
            existingIds.insert(customer->getId());
        }
        REQUIRE(noClash);
    }

    SECTION("Getting and Setting waitedTime") {
        auto customer = std::make_shared<BCS::Customer>(10);
        REQUIRE(0 == customer->getWaitedTime());
        customer->wait();
        REQUIRE(1 == customer->getWaitedTime());
    }
}