#include <gtest/gtest.h>
#include "../include/FileHandler.h"
#include "../include/Order.h"
#include "../include/ExecutionReport.h"
#include <fstream>

TEST(FileHandlerTest, ReadOrdersFromFile_EmptyFile) {
    std::ofstream file("test_empty.csv");
    file << "ClientOrderId,Instrument,Side,Quantity,Price\n";
    file.close();
    auto orders = FileHandler::readOrdersFromFile("test_empty.csv");
    EXPECT_TRUE(orders.empty());
    std::remove("test_empty.csv");
}

TEST(FileHandlerTest, WriteReportsToFile) {
    ExecutionReport r;
    r.orderId = "ord1";
    r.clientOrderId = "cl1";
    r.instrument = "Rose";
    r.side = 1;
    r.status = OrderStatus::New;
    r.quantity = 10;
    r.price = 10.0;
    r.timestamp = "20220101-120000";
    std::vector<ExecutionReport> reports = { r };
    FileHandler::writeReportsToFile("test_report.csv", reports);
    std::ifstream file("test_report.csv");
    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, 
        "Order ID,Client Order ID,Instrument,Side,Exec Status,Quantity,Price,Transaction Time");
    
    std::getline(file, line);
    EXPECT_NE(line.find("ord1"), std::string::npos);
    file.close();
    std::remove("test_report.csv");
}
