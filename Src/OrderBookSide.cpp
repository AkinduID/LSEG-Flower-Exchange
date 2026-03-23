#include "../Include/OrderBookSide.h"
#include <algorithm>

// Insert with sorting (price priority)
void OrderBookSide::insertOrder(const Order& order, bool isBuySide) {

    orders.push_back(order);

    if (isBuySide) {
        // BUY: highest price first
        orders.sort([](const Order& a, const Order& b) {
            return a.price > b.price;
        });
    } else {
        // SELL: lowest price first
        orders.sort([](const Order& a, const Order& b) {
            return a.price < b.price;
        });
    }
}

void OrderBookSide::deleteOrder(const Order& order) {
    orders.remove(order); // uses operator==
}

Order* OrderBookSide::getTopOrder() {

    if (orders.empty())
        return nullptr;

    return &orders.front();
}

