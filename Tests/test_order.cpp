#include <gtest/gtest.h>
#include "../include/Order.h"

TEST(OrderTest, DefaultConstructor) {
    Order order;
    EXPECT_EQ(order.orderId, "");
    EXPECT_EQ(order.quantity, 0);
    EXPECT_EQ(order.price, 0.0);
    // Add more checks as needed
}

// Add more Order tests here
