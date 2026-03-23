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

            orderBooks[order.instrument].processOrder(order);

            // NEW order report
            ExecutionReport r;
            r.orderId = order.orderId;
            r.clientOrderId = order.clientOrderId;
            r.instrument = order.instrument;
            r.side = order.side;
            r.price = order.price;
            r.quantity = order.quantity;
            r.status = 0;  // 0 = New
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