#pragma once
#include <string>
#include "../include/Order.h"

namespace Utils {
    std::string getStatusText(int status);
    std::string getTimestamp();
    std::string generateOrderId();
    bool validateOrder(const Order& order, string& reason);
}
