#include "../Include/ExchangeSystem.h"
#include "../Include/Order.h"
#include "../Include/Utils.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

void ExchangeSystem::processOrders(const std::vector<Order>& orders) {
    for (auto order : orders) {
        order.sequence = ++orderSequence; // Assign time priority
        std::string reason;
        if (!Utils::validateOrder(order, reason)) {
            ExecutionReport r;
            r.orderId = order.orderId;
            r.clientOrderId = order.clientOrderId;
            r.instrument = order.instrument;
            r.side = order.side;
            r.price = order.price;
            r.quantity = order.quantity;
            r.status = 1; // Rejected
            r.reason = reason;
            r.timestamp = Utils::getTimestamp();
            reports.push_back(r);
            continue;
        }
        int originalQuantity = order.quantity;
        orderBooks[order.instrument].clearFilledOrders();
        orderBooks[order.instrument].processOrder(order);
        for (const auto& filled : orderBooks[order.instrument].filledOrders) {
            ExecutionReport fillReport;
            fillReport.orderId = filled.orderId;
            fillReport.clientOrderId = filled.clientOrderId;
            fillReport.instrument = order.instrument;
            fillReport.side = filled.side;
            fillReport.price = filled.price;
            fillReport.quantity = filled.quantity;
            fillReport.status = 2;  // Fill
            fillReport.reason = "";
            fillReport.timestamp = Utils::getTimestamp();
            reports.push_back(fillReport);

            ExecutionReport aggressorReport;
            aggressorReport.orderId = order.orderId;
            aggressorReport.clientOrderId = order.clientOrderId;
            aggressorReport.instrument = order.instrument;
            aggressorReport.side = order.side;
            aggressorReport.price = filled.price; // Use resting order's price
            aggressorReport.quantity = filled.quantity;
            aggressorReport.status = (order.quantity == 0) ? 2 : 3; // Fill or Pfill
            aggressorReport.reason = "";
            aggressorReport.timestamp = Utils::getTimestamp();
            reports.push_back(aggressorReport);
        }
        if (order.quantity > 0 && order.quantity == originalQuantity) {
            ExecutionReport newReport;
            newReport.orderId = order.orderId;
            newReport.clientOrderId = order.clientOrderId;
            newReport.instrument = order.instrument;
            newReport.side = order.side;
            newReport.price = order.price;
            newReport.quantity = order.quantity;
            newReport.status = 0; // New
            newReport.reason = "";
            newReport.timestamp = Utils::getTimestamp();
            reports.push_back(newReport);
        }
    }
}

