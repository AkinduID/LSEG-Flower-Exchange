#ifndef LSEG_FLOWER_EXCHANGE_ORDERBOOKSIDE_H
#define LSEG_FLOWER_EXCHANGE_ORDERBOOKSIDE_H

#include <list>
#include <map>

#include "Order.h"

using namespace std;

class OrderBookSide {
public:
    // price -> list of orders (FIFO at each price level)
    map<double, list<Order>> orders;

    void insertOrder(const Order& order, bool isBuySide);
};

#endif // LSEG_FLOWER_EXCHANGE_ORDERBOOKSIDE_H