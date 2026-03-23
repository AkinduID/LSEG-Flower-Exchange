#ifndef LSEG_FLOWER_EXCHANGE_ORDERBOOK_H
#define LSEG_FLOWER_EXCHANGE_ORDERBOOK_H

#include "OrderBookSide.h"
#include "Order.h"
#include <vector>

// Structure to track filled orders
struct FilledOrder {
    std::string orderId;
    std::string clientOrderId;
    double price;
    int quantity;
    int side;  // 1 = Buy, 2 = Sell
};

class OrderBook {
public:
    OrderBookSide buySide;
    OrderBookSide sellSide;
    std::vector<FilledOrder> filledOrders;  // Track orders that got filled

    void processOrder(Order& order);
    void printOrderBook(const std::string& instrument) const;
    void clearFilledOrders() { filledOrders.clear(); }

private:
    bool isMatchingOrder(const Order& order);
    void matchOrder(Order& order);
    void addOrder(const Order& order);

};

#endif