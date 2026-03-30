#ifndef LSEG_FLOWER_EXCHANGE_ORDER_H
#define LSEG_FLOWER_EXCHANGE_ORDER_H

#include <string>

using namespace std;
/**
 * @struct InputOrder
 * @brief Structure to track input orders.
 */
struct InputOrder {
    std::string clientOrderId;
    std::string instrument;
    int side; // raw side value from CSV
    int quantity;
    double price;

    InputOrder() = default;
        InputOrder(const std::string& clientOrderId_, const std::string& instrument_, int side_, 
            double price_, int quantity_) : clientOrderId(clientOrderId_), instrument(instrument_), 
            side(side_), quantity(quantity_), price(price_) {}
};
/**
 * @enum OrderSide
 * @brief Enum for order side (Buy/Sell)
 */
enum class OrderSide {
    Buy = 1, ///< Buy side
    Sell = 2 ///< Sell side
};

/**
 * @enum OrderStatus
 * @brief Enum for order status (New, Rejected, Fill, Partial Fill)
 */
enum class OrderStatus {
    New = 0,      ///< New order
    Rejected = 1, ///< Rejected order
    Fill = 2,     ///< Fully filled
    Pfill = 3     ///< Partially filled
};

/**
 * @class Order
 * @brief Represents a single order in the exchange.
 */
class Order {
public:
    string orderId;           ///< System-generated order ID
    string clientOrderId;     ///< Client-supplied order ID
    string instrument;        ///< Instrument/flower type
    OrderSide side;           ///< Order side (Buy/Sell)
    double price{};           ///< Order price
    int quantity{};           ///< Order quantity
    long long sequence{};     ///< Time priority (FIFO) - order of arrival

    /**
     * @brief Default constructor.
     */
    Order() = default;
    /**
     * @brief Parameterized constructor.
     */
    Order(string id, string inst, OrderSide s, double p, int q);

    /**
     * @brief Equality operator for orders.
     */
    bool operator==(const Order& other) const;
};

#endif // LSEG_FLOWER_EXCHANGE_ORDER_H