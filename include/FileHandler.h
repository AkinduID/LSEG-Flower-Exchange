#pragma once
#include <vector>
#include <string>
#include "Order.h"

/**
 * @class FileHandler
 * @brief Handles reading orders from and writing reports to CSV files.
 */
class FileHandler {
public:
	/**
	 * @brief Read orders from a CSV file.
	 * @param filePath Path to the input CSV file.
	 * @return Vector of orders.
	 */
	static std::vector<InputOrder> readOrdersFromFile(const std::string& filePath);

	/**
	 * @brief Write execution reports to a CSV file.
	 * @param filePath Path to the output CSV file.
	 * @param reports Vector of execution reports.
	 */
	static void writeReportsToFile(const std::string& filePath, const std::vector<ExecutionReport>& reports);
};
