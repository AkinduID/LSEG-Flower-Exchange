#include "./../Include/OrderBook.h"
#include <algorithm>

#include <iostream>
#include <iomanip>

void OrderBook::printOrderBook(const std::string& instrument) const {

    std::cout << "\n=============================\n";
    std::cout << "OrderBook : " << instrument << "\n";
    std::cout << "=============================\n";

    std::cout << std::left
              << std::setw(10) << "OrderID"
              << std::setw(10) << "Qty"
              << std::setw(10) << "Price"
              << " | "
              << std::setw(10) << "Price"
              << std::setw(10) << "Qty"
              << std::setw(10) << "OrderID"
              << "\n";

    std::cout << "-----------------------------------------------------------\n";
    auto buyIt = buySide.orders.begin();
    auto sellIt = sellSide.orders.begin();

    while (buyIt != buySide.orders.end() || sellIt != sellSide.orders.end()) {

        // BUY SIDE (highest price first)
        if (buyIt != buySide.orders.end()) {
            std::cout << std::left
                      << std::setw(10) << buyIt->orderId
                      << std::setw(10) << buyIt->quantity
                      << std::setw(10) << std::fixed << std::setprecision(2) << buyIt->price;
            ++buyIt;
        } else {
            std::cout << std::setw(10) << ""
                      << std::setw(10) << ""
                      << std::setw(10) << "";
        }

        std::cout << " | ";

        // SELL SIDE (lowest price first)
        if (sellIt != sellSide.orders.end()) {
            std::cout << std::right
                      << std::setw(10) << std::fixed << std::setprecision(2) << sellIt->price
                      << std::left
                      << std::setw(10) << sellIt->quantity
                      << std::setw(10) << sellIt->orderId;
            ++sellIt;
        } else {
            std::cout << std::setw(10) << ""
                      << std::setw(10) << ""
                      << std::setw(10) << "";
        }

        std::cout << "\n";
    }

    std::cout << "=============================\n";
}


void OrderBook::processOrder(Order order) {

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
        buySide.orders.push_back(order);

        // Sort BUY: highest price first
        buySide.orders.sort([](const Order& a, const Order& b) {
            return a.price > b.price;
        });

    } else {
        sellSide.orders.push_back(order);

        // Sort SELL: lowest price first
        sellSide.orders.sort([](const Order& a, const Order& b) {
            return a.price < b.price;
        });
    }
}