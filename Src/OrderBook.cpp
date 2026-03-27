#include "./../include/OrderBook.h"
#include <algorithm>

#include <iostream>
#include <iomanip>

void OrderBook::printOrderBook(const std::string& instrument) const {

    std::cout << "\n=============================\n";
    std::cout << "OrderBook : " << instrument << "\n";
    std::cout << "=============================\n";

    std::cout << std::left
              << std::setw(12) << "OrderID"
              << std::setw(10) << "Qty"
              << std::setw(12) << "Price"
              << " | "
              << std::setw(12) << "Price"
              << std::setw(10) << "Qty"
              << std::setw(12) << "OrderID"
              << "\n";

    std::cout << "-----------------------------------------------------------\n";
    auto buyIt = buySide.orders.begin();
    auto sellIt = sellSide.orders.begin();

    while (buyIt != buySide.orders.end() || sellIt != sellSide.orders.end()) {

        // BUY SIDE (highest price first)
        if (buyIt != buySide.orders.end()) {
            std::cout << std::left << std::setw(12) << buyIt->orderId;
            std::cout << std::right << std::setw(10) << buyIt->quantity;
            std::cout << std::right << std::setw(12) << std::fixed << std::setprecision(2) << buyIt->price;
            ++buyIt;
        } else {
            std::cout << std::setw(12) << ""
                      << std::setw(10) << ""
                      << std::setw(12) << "";
        }

        std::cout << " | ";

        // SELL SIDE (lowest price first)
        if (sellIt != sellSide.orders.end()) {
            std::cout << std::setfill(' ');
            std::cout << std::right << std::setw(12) << std::fixed << std::setprecision(2) << sellIt->price;
            std::cout << std::right << std::setw(10) << sellIt->quantity;
            std::cout << std::left << std::setw(12) << sellIt->orderId;
            ++sellIt;
        } else {
            std::cout << std::setw(12) << ""
                      << std::setw(10) << ""
                      << std::setw(12) << "";
        }

        std::cout << "\n";
    }

    std::cout << "=============================\n";
}


void OrderBook::processOrder(Order& order) {

    if (isMatchingOrder(order)) {
        matchOrder(order);
    }

    // If still remaining → add to book
    if (order.quantity > 0) {
        addOrder(order);
    }
}

bool OrderBook::isMatchingOrder(const Order& order) {

    if (order.side == 1) { // BUY
        for (const auto& sell : sellSide.orders) {
            if (sell.price <= order.price)
                return true;
        }
    } else { // SELL
        for (const auto& buy : buySide.orders) {
            if (buy.price >= order.price)
                return true;
        }
    }

    return false;
}

void OrderBook::matchOrder(Order& order) {

    if (order.side == 1) { // BUY

        for (auto it = sellSide.orders.begin(); it != sellSide.orders.end();) {

            if (it->price <= order.price) {

                int tradedQty = std::min(order.quantity, it->quantity);

                // Track the filled sell order
                FilledOrder filled;
                filled.orderId = it->orderId;
                filled.clientOrderId = it->clientOrderId;
                filled.price = it->price;
                filled.quantity = tradedQty;
                filled.side = 2;  // Sell side
                filledOrders.push_back(filled);

                order.quantity -= tradedQty;
                it->quantity -= tradedQty;

                // Remove if fully matched
                if (it->quantity == 0)
                    it = sellSide.orders.erase(it);
                else
                    ++it;

                if (order.quantity == 0)
                    return;
            } else {
                ++it;
            }
        }

    } else { // SELL

        for (auto it = buySide.orders.begin(); it != buySide.orders.end();) {

            if (it->price >= order.price) {

                int tradedQty = std::min(order.quantity, it->quantity);

                // Track the filled buy order
                FilledOrder filled;
                filled.orderId = it->orderId;
                filled.clientOrderId = it->clientOrderId;
                filled.price = it->price;
                filled.quantity = tradedQty;
                filled.side = 1;  // Buy side
                filledOrders.push_back(filled);

                order.quantity -= tradedQty;
                it->quantity -= tradedQty;

                if (it->quantity == 0)
                    it = buySide.orders.erase(it);
                else
                    ++it;

                if (order.quantity == 0)
                    return;
            } else {
                ++it;
            }
        }
    }
}

void OrderBook::addOrder(const Order& order) {

    if (order.side == 1) {
        buySide.insertOrder(order, true);

    } else {
        sellSide.insertOrder(order, false);
    }
}