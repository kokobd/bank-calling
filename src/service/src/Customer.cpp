#include <bank-calling/service/Customer.h>

namespace Zelinf {
namespace BankCalling {
namespace Service {

std::atomic<Customer::ID> Customer::nextId = ATOMIC_VAR_INIT(0);

}
}
}

