#include <gtest/gtest.h>
#include "../include/Utils.h"
#include "../include/Order.h"

TEST(UtilsTest, GetStatusText) {
    EXPECT_EQ(Utils::getStatusText(OrderStatus::New), "New");
    EXPECT_EQ(Utils::getStatusText(OrderStatus::Rejected), "Rejected");
    EXPECT_EQ(Utils::getStatusText(OrderStatus::Fill), "Fill");
    EXPECT_EQ(Utils::getStatusText(OrderStatus::Pfill), "Pfill");
    EXPECT_EQ(Utils::getStatusText(static_cast<OrderStatus>(99)), "Unknown");
}

TEST(UtilsTest, GenerateOrderIdUnique) {
    std::string id1 = Utils::generateOrderId();
    std::string id2 = Utils::generateOrderId();
    EXPECT_NE(id1, id2);
}

TEST(UtilsTest, ValidateOrder) {
    Order validOrder;
    validOrder.instrument = "Rose";
    validOrder.side = OrderSide::Buy;
    validOrder.price = 10.0;
    validOrder.quantity = 20;
    std::string reason;
    EXPECT_TRUE(Utils::validateOrder(validOrder, reason));

    Order invalidOrder;
    invalidOrder.instrument = "Invalid";
    invalidOrder.side = OrderSide::Buy;
    invalidOrder.price = 10.0;
    invalidOrder.quantity = 20;
    EXPECT_FALSE(Utils::validateOrder(invalidOrder, reason));
    EXPECT_EQ(reason, "Invalid Instrument");
}
