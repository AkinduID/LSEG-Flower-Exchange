#include <iostream>
#include <chrono>
#include "../include/ExchangeSystem.h"
#include "../include/FileHandler.h"

using namespace std;
using namespace std::chrono;

int main() {

    cout << "Flower Exchange System Started" << endl;
    ExchangeSystem exchange;

    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    
    std::vector<Order> orders = FileHandler::readOrdersFromFile("../Data/order.csv");
    exchange.processOrders(orders);
    FileHandler::writeReportsToFile("../Data/execution_report.csv", exchange.reports);

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    for (auto it = exchange.orderBooks.begin(); it != exchange.orderBooks.end(); ++it) {
        it->second.printOrderBook(it->first);
    }

    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "\n Processing Completed in " << duration.count() << " us\n";
    return 0;
}
