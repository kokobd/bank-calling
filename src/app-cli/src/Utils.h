#include <iostream>
#include <sstream>
#include <string>

namespace Zelinf {
namespace BankCalling {
namespace App {

/**
 * Read a variable from standard input.
 * @tparam T the type of the variable. Must be copyable and overloads operator>>
 * @param prompt The text to be displayed to end user.
 * @param defaultValue Default value to supply, if no input is provided.
 * @param var A reference to save the input.
 */
template<typename T>
void readVar(const std::string &prompt, const T &defaultValue, T &var) {
    std::cout << prompt << "(" << defaultValue << ") ";
    std::string line;
    std::getline(std::cin, line);
    if (line.empty()) {
        var = defaultValue;
        return;
    }
    std::istringstream is(line);
    is >> var;
}

}
}
}

