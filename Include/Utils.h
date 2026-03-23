#pragma once
#include <string>

namespace Utils {
    std::string getStatusText(int status);
    std::string getTimestamp();
    std::string generateOrderId();
}
