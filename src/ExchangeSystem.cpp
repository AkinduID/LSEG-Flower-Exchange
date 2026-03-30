#include "../Include/ExchangeSystem.h"
#include "../Include/Order.h"
#include "../Include/Utils.h"
#include "../Include/ExecutionReport.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

void ExchangeSystem::processOrders(const vector<Order>& orders) {
    for (auto order : orders) {
        order.sequence = ++orderSequence; // Assign time priority
        string reason;
        if (!Utils::validateOrder(order, reason)) {
            ExecutionReport r = ExecutionReport::createRejectReport(order, order.instrument, reason);
            reports.push_back(r);
            continue;
        }
        int originalQuantity = order.quantity;
        orderBooks[order.instrument].clearFilledOrders();
        orderBooks[order.instrument].processOrder(order);
        for (const auto& filled : orderBooks[order.instrument].filledOrders) {
            reports.push_back(ExecutionReport::createFillReport(filled, order.instrument, filled.side, filled.price, filled.quantity));
            reports.push_back(ExecutionReport::createAggressorReport(order, order.instrument, filled.price, filled.quantity, (order.quantity == 0) ? 2 : 3));
        }
        if (order.quantity > 0 && order.quantity == originalQuantity) {
            reports.push_back(ExecutionReport::createNewReport(order, order.instrument));
        }
    }
}

