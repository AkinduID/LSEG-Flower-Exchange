#include <map>
#include <vector>

#include "ExecutionReport.h"
#include "OrderBook.h"

using namespace std;

class ExchangeSystem {
public:
    long long orderSequence = 0;    // Global sequence counter for time priority
    map<string, OrderBook> orderBooks;
    vector<ExecutionReport> reports;

    void processOrders(const std::vector<Order>& orders);
};