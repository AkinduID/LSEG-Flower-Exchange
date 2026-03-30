#include <map>
#include <vector>

#include "ExecutionReport.h"
#include "OrderBook.h"
#include "Order.h"

using namespace std;

/**
 * @class ExchangeSystem
 * @brief Manages the overall exchange, including order books and order processing.
 */
class ExchangeSystem {
public:
    long long orderSequence = 0;    ///< Global sequence counter for time priority
    map<string, OrderBook> orderBooks; ///< Map of instrument to order book
    vector<ExecutionReport> reports;   ///< All execution reports

    /**
     * @brief Process a list of orders, updating order books and generating reports.
     * @param inputOrders Vector of input orders to process.
     */
    void processOrders(const std::vector<InputOrder>& inputOrders);
};