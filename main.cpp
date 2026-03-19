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

    void readOrder(){
        // Code to read order details from input
    }

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
    double ExecutedPrice;
    double ExecutedQuantity;
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

    void getTopOfTheBook() {
        // Code to retrieve the best bid or ask price and quantity
        if (!orders.empty()) {
            Order topOrder = orders.front();
            std::cout << "Top of the book - Price: " << topOrder.Price << ", Quantity: " << topOrder.Quantity << std::endl;
        } else {
            std::cout << "Order book side is empty." << std::endl;
        }
    }
};


class OrderBook {
    public:
    OrderBookSide buySide;
    OrderBookSide sellSide;

    void processOrder(const Order& order) {
        // Code to process incoming orders and update the order book
        if (isMatchingOrder(order)) {
            matchOrder(order);
        } else {
            if (order.Side == 1) { // Buy order
                buySide.insertOrder(order);
            } else { // Sell order
                sellSide.insertOrder(order);
            }
        }
    }

    bool isMatchingOrder(const Order& order) {
        // Code to check if the incoming order matches with existing orders in the order book
        if (order.Side == 1) { // Buy order
            // Check for matching sell orders
            for (const auto& sellOrder : sellSide.orders) {
                if (sellOrder.Price <= order.Price) {
                    return true; // Found a matching sell order
                }
            }
        } else { // Sell order
            // Check for matching buy orders
            for (const auto& buyOrder : buySide.orders) {
                if (buyOrder.Price >= order.Price) {
                    return true; // Found a matching buy order
                }
            }
        }
        return false;
    }

    void matchOrder(const Order& order) {
        // Code to match incoming orders with existing orders in the order book and generate execution reports
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

                orderBooks[newOrder.Instrument].processOrder(newOrder);
            }
        }
    }
};

int main(){
    ExchangeSystem exchange;
    exchange.readFiles("order1.csv");

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
