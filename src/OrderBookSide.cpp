#include "../include/OrderBookSide.h"
#include <algorithm>

// Insert with sorting (price priority)
void OrderBookSide::insertOrder(const Order& order, bool isBuySide) {

    orders.push_back(order);

    if (isBuySide) {
        // BUY: highest price first
        // Sort BUY: highest price first, then by time priority (earlier orders first)
        std::sort(orders.begin(), orders.end(), [](const Order& a, const Order& b) {
            if (a.price != b.price)
                return a.price > b.price;  // Descending by price (highest first)
            return a.sequence < b.sequence;  // FIFO for same price
        });
    } else {
        // SELL: lowest price first
        // Sort SELL: lowest price first, then by time priority (earlier orders first)
        std::sort(orders.begin(), orders.end(), [](const Order& a, const Order& b) {
            if (a.price != b.price)
                return a.price < b.price;  // Ascending by price (lowest first)
            return a.sequence < b.sequence;  // FIFO for same price
        });
    }
}
