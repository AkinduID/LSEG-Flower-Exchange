#include <iostream>
#include "../Include/ExchangeSystem.h"

using namespace std;

int main() {

    cout << "Flower Exchange System Started" << endl;

    ExchangeSystem exchange;

    exchange.readFile("../Data/order.csv");
    for (const auto& [instrument, book] : exchange.orderBooks) {
        book.printOrderBook(instrument);
    }
    exchange.writeReports("../Data/execution_report.csv");

    cout << "\n Processing Completed\n";
    return 0;
}
