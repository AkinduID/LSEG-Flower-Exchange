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

    // Buy side (descending prices)
    auto buyIt = buySide.orders.rbegin();
    // Sell side (ascending prices)
    auto sellIt = sellSide.orders.begin();

    // Secondary iterators for the lists at each price level
    auto buyListIt = (buyIt != buySide.orders.rend()) ? buyIt->second.begin() : list<Order>::iterator();
    auto sellListIt = (sellIt != sellSide.orders.end()) ? sellIt->second.begin() : list<Order>::iterator();

    while (buyIt != buySide.orders.rend() || sellIt != sellSide.orders.end()) {

        // BUY SIDE
        if (buyIt != buySide.orders.rend()) {
            std::cout << std::left << std::setw(12) << buyListIt->orderId;
            std::cout << std::right << std::setw(10) << buyListIt->quantity;
            std::cout << std::right << std::setw(12) << std::fixed << std::setprecision(2) << buyListIt->price;
            
            ++buyListIt;
            if (buyListIt == buyIt->second.end()) {
                ++buyIt;
                if (buyIt != buySide.orders.rend()) buyListIt = buyIt->second.begin();
            }
        } else {
            std::cout << std::setw(12) << ""
                      << std::setw(10) << ""
                      << std::setw(12) << "";
        }

        std::cout << " | ";

        // SELL SIDE
        if (sellIt != sellSide.orders.end()) {
            std::cout << std::setfill(' ');
            std::cout << std::right << std::setw(12) << std::fixed << std::setprecision(2) << sellListIt->price;
            std::cout << std::right << std::setw(10) << sellListIt->quantity;
            std::cout << std::left << std::setw(12) << sellListIt->orderId;
            
            ++sellListIt;
            if (sellListIt == sellIt->second.end()) {
                ++sellIt;
                if (sellIt != sellSide.orders.end()) sellListIt = sellIt->second.begin();
            }
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
    // Merge matching and processing to avoid redundant scans
    matchOrder(order);

    // If still remaining → add to book
    if (order.quantity > 0) {
        addOrder(order);
    }
}

bool OrderBook::isMatchingOrder(const Order& order) {
    if (order.side == OrderSide::Buy) { // BUY
        if (sellSide.orders.empty()) return false;
        return sellSide.orders.begin()->first <= order.price;
    } else { // SELL
        if (buySide.orders.empty()) return false;
        return buySide.orders.rbegin()->first >= order.price;
    }
}

void OrderBook::matchOrder(Order& order) {

    if (order.side == OrderSide::Buy) { // BUY against Sell Side (lowest price first)

        while (order.quantity > 0 && !sellSide.orders.empty()) {
            auto it = sellSide.orders.begin(); // Lowest price
            if (it->first <= order.price) {
                auto& orderList = it->second;
                auto listIt = orderList.begin();

                int tradedQty = std::min(order.quantity, listIt->quantity);

                FilledOrder filled;
                filled.orderId = listIt->orderId;
                filled.clientOrderId = listIt->clientOrderId;
                filled.price = listIt->price;
                filled.quantity = tradedQty;
                filled.side = OrderSide::Sell;
                filledOrders.push_back(filled);

                order.quantity -= tradedQty;
                listIt->quantity -= tradedQty;

                if (listIt->quantity == 0) {
                    orderList.erase(listIt);
                }

                if (orderList.empty()) {
                    sellSide.orders.erase(it);
                }
            } else {
                break; // Sell price too high
            }
        }

    } else { // SELL against Buy Side (highest price first)

        // Using a while loop with direct erase to avoid reverse iterator complexities
        while (order.quantity > 0 && !buySide.orders.empty()) {
            auto it = buySide.orders.rbegin(); // Highest price
            if (it->first >= order.price) {
                auto& orderList = it->second;
                auto listIt = orderList.begin();

                int tradedQty = std::min(order.quantity, listIt->quantity);

                FilledOrder filled;
                filled.orderId = listIt->orderId;
                filled.clientOrderId = listIt->clientOrderId;
                filled.price = listIt->price;
                filled.quantity = tradedQty;
                filled.side = OrderSide::Buy;
                filledOrders.push_back(filled);

                order.quantity -= tradedQty;
                listIt->quantity -= tradedQty;

                if (listIt->quantity == 0) {
                    orderList.erase(listIt);
                }

                if (orderList.empty()) {
                    // Erase the price level entirely
                    auto baseIt = std::prev(buySide.orders.end());
                    buySide.orders.erase(baseIt);
                }
            } else {
                break; // Buy price too low
            }
        }
    }
}

void OrderBook::addOrder(const Order& order) {

    if (order.side == OrderSide::Buy) {
        buySide.insertOrder(order, true);

    } else {
        sellSide.insertOrder(order, false);
    }
}