#include <catch/catch.hpp>
#include <bank-calling/service/Window.h>

namespace BCS = Zelinf::BankCalling::Service;

TEST_CASE("Window") {
    BCS::Window window;
    REQUIRE(0 == window.getLeftTime());
    REQUIRE(window.isEnabled());
    REQUIRE(nullptr == window.getCurrentCustomer());

    auto c1 = std::make_shared<BCS::Customer>(20);
    window.serve(c1);
    window.serve(c1);
    REQUIRE(18 == window.getLeftTime());
    for (int i = 0; i < 17; i++) {
        window.serve(c1);
    }
    window.serve(nullptr);
    REQUIRE(0 == window.getLeftTime());
    auto c2 = std::make_shared<BCS::Customer>(5);
    window.serve(c2);
    REQUIRE(4 == window.getLeftTime());
}
