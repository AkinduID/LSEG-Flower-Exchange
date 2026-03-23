#pragma once
#include <string>
#include "../Include/Order.h"

namespace Utils {
    std::string getStatusText(int status);
    std::string getTimestamp();
    std::string generateOrderId();
    bool validateOrder(const Order& order, string& reason);
}
