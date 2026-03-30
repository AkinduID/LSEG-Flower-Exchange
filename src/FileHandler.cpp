#include "../include/ExecutionReport.h"
#include "../include/FileHandler.h"
#include "../include/Utils.h"
#include "../include/Order.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

std::vector<InputOrder> FileHandler::readOrdersFromFile(const std::string& filePath) {
	std::vector<InputOrder> orders;
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
			InputOrder inputOrder;
			inputOrder.clientOrderId = row[0];
			inputOrder.instrument = row[1];
			inputOrder.side = std::stoi(row[2]);
			inputOrder.quantity = std::stoi(row[3]);
			inputOrder.price = std::stod(row[4]);
			orders.push_back(inputOrder);
		}
	}
	file.close();
	return orders;
}

void FileHandler::writeReportsToFile(const std::string& filePath, 
	const std::vector<ExecutionReport>& reports) {

	std::ofstream file(filePath);
	file << 
	"Order ID,Client Order ID,Instrument,Side,Exec Status,Quantity,Price,Reason,Transaction Time\n";
	
	for (const auto& r : reports) {
		file << r.orderId << ","
			 << r.clientOrderId << ","
			 << r.instrument << ","
			 << r.side  << ","
			 << Utils::getStatusText((r.status)) << ","
			 << r.quantity << ","
			 << std::fixed << std::setprecision(2) << r.price << ","
			 << r.reason << ","
			 << r.timestamp << "\n";
	}
	file.close();
}