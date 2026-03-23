    
#ifndef LSEG_FLOWER_EXCHANGE_EXECUTIONREPORT_H
#define LSEG_FLOWER_EXCHANGE_EXECUTIONREPORT_H

#include <string>
#include "Order.h"
#include "OrderBook.h"

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

    static ExecutionReport createFillReport(const Order& restingOrder, const std::string& instrument, int side, double price, int quantity);
    static ExecutionReport createFillReport(const FilledOrder& filledOrder, const std::string& instrument, int side, double price, int quantity);
    static ExecutionReport createAggressorReport(const Order& incomingOrder, const std::string& instrument, double price, int quantity, int status);
    static ExecutionReport createNewReport(const Order& order, const std::string& instrument);
    static ExecutionReport createRejectReport(const Order& order, const std::string& instrument, const std::string& reason);
};

#endif