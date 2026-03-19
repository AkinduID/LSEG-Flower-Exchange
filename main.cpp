#include<iostream>
#include<string>
#include <list>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

class Order {
    public:
    std::string ClientOrderID;
    std::string Instrument;
    int Side;
    double Price;
    int Quantity;

    bool operator==(const Order& other) const {
        return ClientOrderID == other.ClientOrderID &&
               Instrument == other.Instrument &&
               Side == other.Side &&
               Price == other.Price &&
               Quantity == other.Quantity;
    }
};

class ExecutionReport {
    public:
    int OrderID;
    std::string ClientOrderID;
    std::string Instrument;
    int Side;
    double Price;
    int Quantity;
    // double ExecutedPrice;
    // double ExecutedQuantity;
    int Status;
    std::string Reason;
    std::string Timestamp;
};

class OrderBookSide {
    public:
    std::list<Order> orders;
    void insertOrder(const Order& order) {
        // Code to add order to the order book side
        orders.push_back(order);
    }

    void deleteOrder(const Order& order) {
        // Code to remove order from the order book side
        orders.remove(order);
    }
};


class OrderBook {
    public:
    OrderBookSide buySide;
    OrderBookSide sellSide;

    ExecutionReport processOrder(const Order& order) {
        // Code to process incoming orders and update the order book
        if (order.Side == 1) { // Buy order
            buySide.insertOrder(order);
        } else { // Sell order
            sellSide.insertOrder(order);
        }
        ExecutionReport report;
        report.OrderID = 0; // Placeholder for order ID generation logic
        report.ClientOrderID = order.ClientOrderID;
        report.Instrument    = order.Instrument;
        report.Side          = order.Side;
        report.Price         = order.Price;
        report.Quantity      = order.Quantity;
        report.Status        = 1; // Assuming 1 means accepted
        report.Timestamp     = std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
        return report;
    }
};

class ExchangeSystem {
    public:
    std::map<std::string, OrderBook> orderBooks;

    void readFiles(std::string filePath) {
        std::ifstream file(filePath);
        std::string line;

        // Skip the header line (Client Order ID, Instrument, Side, Price, Quantity)
        if (!std::getline(file, line)) return;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> row;

            // Split the line by comma
            while (std::getline(ss, segment, ',')) {
                row.push_back(segment);
            }

            // map the vector to Order object
            if (row.size() >= 5) {
                Order newOrder;
                newOrder.ClientOrderID = row[0];
                newOrder.Instrument    = row[1];
                newOrder.Side          = std::stoi(row[2]);   // String to Int
                newOrder.Price         = std::stod(row[3]);   // String to Double
                newOrder.Quantity      = std::stoi(row[4]);   // String to Int

                ExecutionReport report = orderBooks[newOrder.Instrument].processOrder(newOrder);
                WriteFile(report);
            }
        }
        return;
    }

    void WriteFile(ExecutionReport report) {
        std::ofstream outFile("execution_report.csv", std::ios::app);
        if (outFile.is_open()) {
            outFile << report.OrderID << ","
                    << report.ClientOrderID << ","
                    << report.Instrument << ","
                    << report.Side << ","
                    << report.Price << ","
                    << report.Quantity << ","
                    // << report.ExecutedPrice << ","
                    // << report.ExecutedQuantity << ","
                    << report.Status << ","
                    << report.Reason << ","
                    << report.Timestamp << "\n";
            outFile.close();
        }
    }
};

int main(){
    ExchangeSystem exchange;
    exchange.readFiles("example1.csv");

    for (const auto& [instrument, orderBook] : exchange.orderBooks) {
        std::cout << "Instrument: " << instrument << std::endl;
        std::cout << "  Buy Orders:" << std::endl;
        for (const auto& order : orderBook.buySide.orders) {
            std::cout << "    ID: " << order.ClientOrderID << ", Price: " << order.Price << ", Qty: " << order.Quantity << std::endl;
        }
        std::cout << "  Sell Orders:" << std::endl;
        for (const auto& order : orderBook.sellSide.orders) {
            std::cout << "    ID: " << order.ClientOrderID << ", Price: " << order.Price << ", Qty: " << order.Quantity << std::endl;
        }
    }
    return 0;
}
