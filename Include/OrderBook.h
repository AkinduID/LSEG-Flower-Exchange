#ifndef LSEG_FLOWER_EXCHANGE_ORDERBOOK_H
#define LSEG_FLOWER_EXCHANGE_ORDERBOOK_H

#include "OrderBookSide.h"
#include "Order.h"

class OrderBook {
public:
    OrderBookSide buySide;
    OrderBookSide sellSide;

    void processOrder(Order order);
    void printOrderBook(const std::string& instrument) const;

private:
    bool isMatchingOrder(const Order& order);
    void matchOrder(Order& order);
    void addOrder(const Order& order);

};

#endif