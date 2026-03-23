#ifndef LSEG_FLOWER_EXCHANGE_ORDERBOOKSIDE_H
#define LSEG_FLOWER_EXCHANGE_ORDERBOOKSIDE_H

#include <list>
#include "Order.h"

using namespace std;

class OrderBookSide {
public:
    list<Order> orders;

    void insertOrder(const Order& order, bool isBuySide);
    void deleteOrder(const Order& order);
    Order* getTopOrder();
};

#endif // LSEG_FLOWER_EXCHANGE_ORDERBOOKSIDE_H