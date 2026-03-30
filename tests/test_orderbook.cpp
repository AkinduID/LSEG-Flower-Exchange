#include <gtest/gtest.h>
#include "../include/OrderBook.h"

TEST(OrderBookTest, DefaultConstructor) {
    OrderBook ob;
    // Add checks for default state
}

TEST(OrderBookTest, AddOrderAndMatch) {
    OrderBook ob;
    Order buyOrder;
    buyOrder.orderId = "b1";
    buyOrder.side = OrderSide::Buy;
    buyOrder.price = 100;
    buyOrder.quantity = 50;
    buyOrder.sequence = 1;
    ob.processOrder(buyOrder);
    EXPECT_EQ(ob.buySide.orders.size(), 1);
    Order sellOrder;
    sellOrder.orderId = "s1";
    sellOrder.side = OrderSide::Sell;
    sellOrder.price = 100;
    sellOrder.quantity = 50;
    sellOrder.sequence = 2;
    ob.processOrder(sellOrder);
    EXPECT_EQ(ob.buySide.orders.size(), 0);
    EXPECT_EQ(ob.sellSide.orders.size(), 0);
    EXPECT_EQ(ob.filledOrders.size(), 1);
}

// Add more OrderBook tests here
