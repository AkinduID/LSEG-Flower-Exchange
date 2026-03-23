#include <iostream>
#include "../Include/ExchangeSystem.h"

using namespace std;

int main() {

    cout << "Flower Exchange System Started" << endl;

    ExchangeSystem exchange;

    exchange.readFile("../Data/order.csv");
    for (auto it = exchange.orderBooks.begin(); it != exchange.orderBooks.end(); ++it) {
        it->second.printOrderBook(it->first);
    }
    exchange.writeReports("../Data/execution_report.csv");

    cout << "\n Processing Completed\n";
    return 0;
}
