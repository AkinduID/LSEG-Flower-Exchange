#include "../include/OrderBookSide.h"
#include <algorithm>

// Insert with price-time priority using the map
void OrderBookSide::insertOrder(const Order& order, bool isBuySide) {
    // orders is a map<double, list<Order>>
    // The map is naturally sorted by price (ascending by default)
    // We will handle the direction (descending for Buy) during matching/iteration
    // or we could use different map types, but for now common map works.
    orders[order.price].push_back(order);
}
