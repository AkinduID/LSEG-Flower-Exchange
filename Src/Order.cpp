#include "../include/Order.h"

Order::Order(std::string id, std::string inst, int s, double p, int q)
    : clientOrderId(id), instrument(inst), side(s), price(p), quantity(q) {}

bool Order::operator==(const Order& other) const {
    return clientOrderId == other.clientOrderId;
}