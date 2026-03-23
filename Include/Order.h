#ifndef LSEG_FLOWER_EXCHANGE_ORDER_H
#define LSEG_FLOWER_EXCHANGE_ORDER_H

#include <string>

using namespace std;

class Order {
public:
    string orderId;           // System-generated order ID
    string clientOrderId;
    string instrument;
    int side{};        // 1 = Buy, 2 = Sell
    double price{};
    int quantity{};

    Order() = default;
    Order(string id, string inst, int s, double p, int q);

    bool operator==(const Order& other) const;
};

#endif // LSEG_FLOWER_EXCHANGE_ORDER_H