#include "../Include/ExchangeSystem.h"
#include "../Include/Order.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;

std::string getStatusText(int status) {
    switch (status) {
        case 0: return "New";
        case 1: return "Rejected";
        case 2: return "Fill";
        case 3: return "Pfill";
        default: return "Unknown";
    }
}

void ExchangeSystem::readFile(const string& filePath) {

    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Error: Cannot open file\n";
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {

        stringstream ss(line);
        string segment;
        vector<string> row;

        while (getline(ss, segment, ',')) {
            row.push_back(segment);
        }

        if (row.size() >= 5) {

            Order order;
            order.orderId       = generateOrderId();  // Generate order ID first
            order.clientOrderId = row[0];
            order.instrument    = row[1];
            order.side          = stoi(row[2]);
            order.quantity      = stoi(row[3]);
            order.price         = stod(row[4]);
            order.sequence      = ++orderSequence;    // Assign time priority

            string reason;

            if (!validateOrder(order, reason)) {

                ExecutionReport r;
                r.orderId = order.orderId;
                r.clientOrderId = order.clientOrderId;
                r.instrument = order.instrument;
                r.side = order.side;
                r.price = order.price;
                r.quantity = order.quantity;
                r.status = 1; // Rejected
                r.reason = reason;
                r.timestamp = getTimestamp();

                reports.push_back(r);
                continue;
            }

            int originalQuantity = order.quantity;

            // Clear filled orders from previous processing
            orderBooks[order.instrument].clearFilledOrders();
            
            orderBooks[order.instrument].processOrder(order);

            // Generate Fill reports for matched orders (counter-party fills)
            for (const auto& filled : orderBooks[order.instrument].filledOrders) {
                ExecutionReport fillReport;
                fillReport.orderId = filled.orderId;
                fillReport.clientOrderId = filled.clientOrderId;
                fillReport.instrument = order.instrument;
                fillReport.side = filled.side;
                fillReport.price = filled.price;
                fillReport.quantity = filled.quantity;
                fillReport.status = 2;  // Fill
                fillReport.reason = "";
                fillReport.timestamp = getTimestamp();
                reports.push_back(fillReport);
            }

            // Create report for incoming order
            ExecutionReport r;
            r.orderId = order.orderId;
            r.clientOrderId = order.clientOrderId;
            r.instrument = order.instrument;
            r.side = order.side;
            r.price = order.price;
            r.quantity = originalQuantity;
            
            // Determine status: Fill if fully matched, New if added to book
            if (order.quantity == 0) {
                r.status = 2;  // Fill - fully matched
            } else {
                r.status = 0;  // New - partially or not matched
            }
            
            r.timestamp = getTimestamp();

            reports.push_back(r);
        }
    }

    file.close();
}

bool ExchangeSystem::validateOrder(const Order& o, string& reason) {

    if (o.instrument != "Rose" &&
        o.instrument != "Lavender" &&
        o.instrument != "Lotus" &&
        o.instrument != "Tulip" &&
        o.instrument != "Orchid") {

        reason = "Invalid Instrument";
        return false;
        }

    if (o.side != 1 && o.side != 2) {
        reason = "Invalid Side";
        return false;
    }

    if (o.price <= 0) {
        reason = "Invalid Price";
        return false;
    }

    if (o.quantity < 10 || o.quantity > 1000 || o.quantity % 10 != 0) {
        reason = "Invalid Quantity";
        return false;
    }

    return true;
}

string ExchangeSystem::generateOrderId() {
    static int counter = 1;
    return "ord" + to_string(counter++);
}

string ExchangeSystem::getTimestamp() {

    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);

    tm* tm_ptr = localtime(&time);

    char buffer[32];
    strftime(buffer, sizeof(buffer), "%Y%m%d-%H%M%S", tm_ptr);

    return string(buffer);
}


#include <iomanip>   // ADD THIS

void ExchangeSystem::writeReports(const string& filePath) {

    ofstream file(filePath);

    file << "Order ID,Client Order ID,Instrument,Side,Exec Status,Quantity,Price,Transaction Time\n";

    for (const auto& r : reports) {

        file << r.orderId << ","
             << r.clientOrderId << ","
             << r.instrument << ","
             << r.side << ","
             << getStatusText(r.status) << ","
             << r.quantity << ","
             << fixed << setprecision(2) << r.price << ","
             << r.timestamp << "\n";
    }

    file.close();
}