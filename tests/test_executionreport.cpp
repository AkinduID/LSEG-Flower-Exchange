#include <gtest/gtest.h>
#include "../include/ExecutionReport.h"

TEST(ExecutionReportTest, DefaultConstructor) {
    ExecutionReport er;
    // Add checks for default state
}

TEST(ExecutionReportTest, CreateNewReport) {
    Order order("cl1", "Rose", OrderSide::Buy, 10.5, 100);
    order.orderId = "ord1";
    auto report = ExecutionReport::createNewReport(order, "Rose");
    EXPECT_EQ(report.orderId, "ord1");
    EXPECT_EQ(report.clientOrderId, "cl1");
    EXPECT_EQ(report.instrument, "Rose");
    EXPECT_EQ(report.side, OrderSide::Buy);
    EXPECT_EQ(report.price, 10.5);
    EXPECT_EQ(report.quantity, 100);
    EXPECT_EQ(report.status, OrderStatus::New);
}

TEST(ExecutionReportTest, CreateRejectReport) {
    Order order("cl1", "Rose", OrderSide::Buy, 10.5, 100);
    order.orderId = "ord1";
    InputOrder inputOrder;
    inputOrder.clientOrderId = "cl1";
    inputOrder.instrument = "Rose";
    inputOrder.side = 3; // Invalid side for test
    inputOrder.quantity = 100;
    inputOrder.price = 10.5;
    auto report = ExecutionReport::createRejectReport(order, inputOrder, "Rose", "Invalid");
    EXPECT_EQ(report.status, OrderStatus::Rejected);
    EXPECT_EQ(report.reason, "Invalid");
    EXPECT_EQ(static_cast<int>(report.side), 3);
}

// Add more ExecutionReport tests here
