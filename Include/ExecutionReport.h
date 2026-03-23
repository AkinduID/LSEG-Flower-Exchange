#ifndef LSEG_FLOWER_EXCHANGE_EXECUTIONREPORT_H
#define LSEG_FLOWER_EXCHANGE_EXECUTIONREPORT_H

#include <string>

class ExecutionReport {
public:
    std::string orderId;
    std::string clientOrderId;
    std::string instrument;
    int side;
    double price;
    int quantity;
    int status;              // 0 New, 1 Reject, 2 Fill, 3 Pfill
    std::string reason;
    std::string timestamp;
};

#endif