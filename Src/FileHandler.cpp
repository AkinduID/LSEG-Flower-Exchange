#include "../include/ExecutionReport.h"
#include "../include/FileHandler.h"
#include "../include/Utils.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

std::vector<Order> FileHandler::readOrdersFromFile(const std::string& filePath) {
	std::vector<Order> orders;
	std::ifstream file(filePath);
	if (!file.is_open()) {
		return orders;
	}
	std::string line;
	getline(file, line); // skip header
	while (getline(file, line)) {
		std::stringstream ss(line);
		std::string segment;
		std::vector<std::string> row;
		while (getline(ss, segment, ',')) {
			row.push_back(segment);
		}
		if (row.size() >= 5) {
			Order order;
			order.orderId       = Utils::generateOrderId();
			order.clientOrderId = row[0];
			order.instrument    = row[1];
			order.side          = std::stoi(row[2]);
			order.quantity      = std::stoi(row[3]);
			order.price         = std::stod(row[4]);
			// sequence should be set by ExchangeSystem
			orders.push_back(order);
		}
	}
	file.close();
	return orders;
}

void FileHandler::writeReportsToFile(const std::string& filePath, const std::vector<ExecutionReport>& reports) {
	std::ofstream file(filePath);
	file << "Order ID,Client Order ID,Instrument,Side,Exec Status,Quantity,Price,Transaction Time\n";
	for (const auto& r : reports) {
		file << r.orderId << ","
			 << r.clientOrderId << ","
			 << r.instrument << ","
			 << r.side << ","
			 << Utils::getStatusText(r.status) << ","
			 << r.quantity << ","
			 << std::fixed << std::setprecision(2) << r.price << ","
			 << r.timestamp << "\n";
	}
	file.close();
}