#include <gtest/gtest.h>
#include "../include/ExecutionReport.h"

TEST(ExecutionReportTest, DefaultConstructor) {
    ExecutionReport er;
    // Add checks for default state
}

TEST(ExecutionReportTest, CreateNewReport) {
    Order order("cl1", "Rose", 1, 10.5, 100);
    order.orderId = "ord1";
    auto report = ExecutionReport::createNewReport(order, "Rose");
    EXPECT_EQ(report.orderId, "ord1");
    EXPECT_EQ(report.clientOrderId, "cl1");
    EXPECT_EQ(report.instrument, "Rose");
    EXPECT_EQ(report.side, 1);
    EXPECT_EQ(report.price, 10.5);
    EXPECT_EQ(report.quantity, 100);
    EXPECT_EQ(report.status, 0);
}

TEST(ExecutionReportTest, CreateRejectReport) {
    Order order("cl1", "Rose", 1, 10.5, 100);
    order.orderId = "ord1";
    auto report = ExecutionReport::createRejectReport(order, "Rose", "Invalid");
    EXPECT_EQ(report.status, 1);
    EXPECT_EQ(report.reason, "Invalid");
}

// Add more ExecutionReport tests here
