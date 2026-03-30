#include "../include/ExchangeSystem.h"
#include "../include/Order.h"
#include "../include/Utils.h"
#include "../include/ExecutionReport.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

void ExchangeSystem::processOrders(const std::vector<InputOrder>& inputOrders) {
    for (auto inputOrder : inputOrders) {
        Order order = Utils::convertInputOrderToOrder(inputOrder, Utils::generateOrderId());
        order.sequence = ++orderSequence; // Assign time priority
        std::string reason;
        if (!Utils::validateOrder(order, reason)) {
            ExecutionReport r = ExecutionReport::createRejectReport(order,inputOrder, 
                order.instrument, reason);

            reports.push_back(r);
            continue;
        }
        // Order order = Utils::convertInputOrderToOrder(inputOrder, Utils::generateOrderId());
        int originalQuantity = order.quantity;
        orderBooks[order.instrument].clearFilledOrders();
        orderBooks[order.instrument].processOrder(order);
        int matchedQty = 0;
        int fillsCount = orderBooks[order.instrument].filledOrders.size();
        int fillIndex = 0;
        for (const auto& filled : orderBooks[order.instrument].filledOrders) {
            ++fillIndex;
            // Always report the fill for the resting order
            reports.push_back(ExecutionReport::createFillReport(filled, order.instrument, 
                filled.side, filled.price, filled.quantity));

            matchedQty += filled.quantity;
            // For each match, generate an aggressor report for the incoming order
            OrderStatus status = OrderStatus::Pfill;
            if (fillIndex == fillsCount && order.quantity == 0) {
                status = OrderStatus::Fill;
            }
            reports.push_back(ExecutionReport::createAggressorReport(order, order.instrument, 
                filled.price, filled.quantity, status));
        }
        // If the incoming order was not matched at all, report as new
        if (order.quantity > 0 && order.quantity == originalQuantity) {
            reports.push_back(ExecutionReport::createNewReport(order, order.instrument));
        }
    }
}

