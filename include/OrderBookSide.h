#ifndef LSEG_FLOWER_EXCHANGE_ORDERBOOKSIDE_H
#define LSEG_FLOWER_EXCHANGE_ORDERBOOKSIDE_H

#include <list>
#include <vector>
#include "Order.h"

using namespace std;

class OrderBookSide {
public:
    vector<Order> orders;

    void insertOrder(const Order& order, bool isBuySide);
};

#endif // LSEG_FLOWER_EXCHANGE_ORDERBOOKSIDE_H