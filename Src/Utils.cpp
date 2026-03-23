#include "../Include/Utils.h"
#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

namespace Utils {

std::string getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    tm* tm_ptr = std::localtime(&time);
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%Y%m%d-%H%M%S", tm_ptr);
    return std::string(buffer);
}

std::string generateOrderId() {
    static int counter = 1;
    return "ord" + std::to_string(counter++);
}

} // namespace Utils
