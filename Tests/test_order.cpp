#include <gtest/gtest.h>
#include "../include/Order.h"

TEST(OrderTest, DefaultConstructor) {
    Order order;
    EXPECT_EQ(order.orderId, "");
    EXPECT_EQ(order.quantity, 0);
    EXPECT_EQ(order.price, 0.0);
    // Add more checks as needed
}

TEST(OrderTest, ParameterizedConstructor) {
    Order order("cl1", "Rose", 1, 10.5, 100);
    EXPECT_EQ(order.clientOrderId, "cl1");
    EXPECT_EQ(order.instrument, "Rose");
    EXPECT_EQ(order.side, 1);
    EXPECT_EQ(order.price, 10.5);
    EXPECT_EQ(order.quantity, 100);
}

TEST(OrderTest, EqualityOperator) {
    Order o1("cl1", "Rose", 1, 10.5, 100);
    Order o2("cl1", "Rose", 2, 11.0, 200);
    EXPECT_TRUE(o1 == o2);
    Order o3("cl2", "Rose", 1, 10.5, 100);
    EXPECT_FALSE(o1 == o3);
}

// Add more Order tests here
