#ifndef LSEG_FLOWER_EXCHANGE_ORDERBOOK_H
#define LSEG_FLOWER_EXCHANGE_ORDERBOOK_H

#include "OrderBookSide.h"
#include "Order.h"
#include <vector>


/**
 * @struct FilledOrder
 * @brief Structure to track filled orders.
 */
struct FilledOrder {
    std::string orderId;        ///< Order ID
    std::string clientOrderId;  ///< Client order ID
    double price;               ///< Fill price
    int quantity;               ///< Fill quantity
    OrderSide side;             ///< 1 = Buy, 2 = Sell
};

/**
 * @class OrderBook
 * @brief Represents the order book for a single instrument, with buy and sell sides.
 */
class OrderBook {
public:
    OrderBookSide buySide; ///< Buy side of the book
    OrderBookSide sellSide; ///< Sell side of the book
    std::vector<FilledOrder> filledOrders;  ///< Track orders that got filled

    /**
     * @brief Process an order (match or add to book).
     * @param order The order to process.
     */
    void processOrder(Order& order);

    /**
     * @brief Print the current state of the order book.
     * @param instrument The instrument name.
     */
    void printOrderBook(const std::string& instrument) const;

    /**
     * @brief Clear the filled orders vector.
     */
    void clearFilledOrders() { filledOrders.clear(); }

private:
    /**
     * @brief Check if an order can be matched.
     */
    bool isMatchingOrder(const Order& order);
    /**
     * @brief Match an order with the opposite side.
     */
    void matchOrder(Order& order);
    /**
     * @brief Add an order to the appropriate side.
     */
    void addOrder(const Order& order);
};

#endif