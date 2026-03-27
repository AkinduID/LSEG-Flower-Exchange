#pragma once
#include <vector>
#include <string>
#include "Order.h"

class FileHandler {
public:
	static std::vector<Order> readOrdersFromFile(const std::string& filePath);
	static void writeReportsToFile(const std::string& filePath, const std::vector<ExecutionReport>& reports);
};
