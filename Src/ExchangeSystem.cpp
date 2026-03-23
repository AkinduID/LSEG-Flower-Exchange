#include "../Include/ExchangeSystem.h"
#include "../Include/Order.h"
#include "../Include/Utils.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

// std::string getStatusText(int status) {
//     switch (status) {
//         case 0: return "New";
//         case 1: return "Rejected";
//         case 2: return "Fill";
//         case 3: return "Pfill";
//         default: return "Unknown";
//     }
// }

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
            order.orderId       = Utils::generateOrderId();  // Generate order ID first
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
                r.timestamp = Utils::getTimestamp();

                reports.push_back(r);
                continue;
            }

            int originalQuantity = order.quantity;

            // Clear filled orders from previous processing
            orderBooks[order.instrument].clearFilledOrders();
            
            orderBooks[order.instrument].processOrder(order);

            // For each fill (counterparty)
            for (const auto& filled : orderBooks[order.instrument].filledOrders) {
                // Report for resting order (already done)
                ExecutionReport fillReport;
                fillReport.orderId = filled.orderId;
                fillReport.clientOrderId = filled.clientOrderId;
                fillReport.instrument = order.instrument;
                fillReport.side = filled.side;
                fillReport.price = filled.price;
                fillReport.quantity = filled.quantity;
                fillReport.status = 2;  // Fill
                fillReport.reason = "";
                fillReport.timestamp = Utils::getTimestamp();
                reports.push_back(fillReport);

                // Report for incoming order (aggressor)
                ExecutionReport aggressorReport;
                aggressorReport.orderId = order.orderId;
                aggressorReport.clientOrderId = order.clientOrderId;
                aggressorReport.instrument = order.instrument;
                aggressorReport.side = order.side;
                aggressorReport.price = filled.price; // Use resting order's price
                aggressorReport.quantity = filled.quantity;
                aggressorReport.status = (order.quantity == 0) ? 2 : 3; // Fill or Pfill
                aggressorReport.reason = "";
                aggressorReport.timestamp = Utils::getTimestamp();
                reports.push_back(aggressorReport);
            }

            // If any quantity remains, report as "New"
            if (order.quantity > 0 && order.quantity == originalQuantity) {
                ExecutionReport newReport;
                newReport.orderId = order.orderId;
                newReport.clientOrderId = order.clientOrderId;
                newReport.instrument = order.instrument;
                newReport.side = order.side;
                newReport.price = order.price;
                newReport.quantity = order.quantity;
                newReport.status = 0; // New
                newReport.reason = "";
                newReport.timestamp = Utils::getTimestamp();
                reports.push_back(newReport);
            }

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



void ExchangeSystem::writeReports(const string& filePath) {

    ofstream file(filePath);

    file << "Order ID,Client Order ID,Instrument,Side,Exec Status,Quantity,Price,Transaction Time\n";

    for (const auto& r : reports) {

        file << r.orderId << ","
             << r.clientOrderId << ","
             << r.instrument << ","
             << r.side << ","
             << Utils::getStatusText(r.status) << ","
             << r.quantity << ","
             << fixed << setprecision(2) << r.price << ","
             << r.timestamp << "\n";
    }

    file.close();
}