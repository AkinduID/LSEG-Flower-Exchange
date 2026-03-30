#ifndef LSEG_FLOWER_EXCHANGE_ORDERBOOKSIDE_H
#define LSEG_FLOWER_EXCHANGE_ORDERBOOKSIDE_H

#include <list>
#include <vector>
#include "Order.h"

using namespace std;

/**
 * @class OrderBookSide
 * @brief Represents one side (buy or sell) of an order book.
 */
class OrderBookSide {
public:
    vector<Order> orders; ///< Orders on this side of the book

    /**
     * @brief Insert an order and maintain price/time priority.
     * @param order The order to insert.
     * @param isBuySide True if buy side, false if sell side.
     */
    void insertOrder(const Order& order, bool isBuySide);
};

#endif // LSEG_FLOWER_EXCHANGE_ORDERBOOKSIDE_H