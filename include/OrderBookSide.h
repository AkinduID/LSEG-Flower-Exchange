#ifndef LSEG_FLOWER_EXCHANGE_ORDERBOOKSIDE_H
#define LSEG_FLOWER_EXCHANGE_ORDERBOOKSIDE_H

#include <list>
#include <map>

#include "Order.h"

using namespace std;

/**
 * @class OrderBookSide
 * @brief Represents one side (buy or sell) of an order book, managing orders at each price level.
 */
class OrderBookSide {
public:
    map<double, list<Order>> orders; ///< Map of price to list of orders at that price level

    /**
     * @brief Inserts an order into the order book side.
     *
     * @param order The order to insert.
     * @param isBuySide True if this is the buy side, false for the sell side.
     */
    void insertOrder(const Order& order, bool isBuySide);
};

#endif // LSEG_FLOWER_EXCHANGE_ORDERBOOKSIDE_H