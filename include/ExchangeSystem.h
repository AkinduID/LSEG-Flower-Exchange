#include <map>
#include <vector>

#include "ExecutionReport.h"
#include "OrderBook.h"

using namespace std;

class ExchangeSystem {
public:
    std::map<std::string, std::string> orderIdMap;
    int orderCounter = 1;
    long long orderSequence = 0;    // Global sequence counter for time priority
    map<string, OrderBook> orderBooks;
    vector<ExecutionReport> reports;

    void processOrders(const std::vector<Order>& orders);
};