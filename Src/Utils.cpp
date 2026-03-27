#include "../include/Utils.h"
#include "../include/Order.h"
#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

namespace Utils {

std::string getStatusText(int status) {
    switch (status) {
        case 0: return "New";
        case 1: return "Rejected";
        case 2: return "Fill";
        case 3: return "Pfill";
        default: return "Unknown";
    }
}
    
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

bool validateOrder(const Order& o, string& reason) {

    if (o.instrument != "Rose" &&
        o.instrument != "Lavender" &&
        o.instrument != "Lotus" &&
        o.instrument != "Tulip" &&
        o.instrument != "Orchid") {

        reason = "Invalid Instrument";
        return false;
        }

    if (o.side != 1 && o.side != 2) {
        reason = "Invalid Side";
        return false;
    }

    if (o.price <= 0) {
        reason = "Invalid Price";
        return false;
    }

    if (o.quantity < 10 || o.quantity > 1000 || o.quantity % 10 != 0) {
        reason = "Invalid Quantity";
        return false;
    }

    return true;
}

} // namespace Utils
