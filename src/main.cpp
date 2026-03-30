#include <iostream>
#include <chrono>
#include "../include/ExchangeSystem.h"
#include "../include/FileHandler.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {

    cout << "Flower Exchange System Started" << endl;
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_csv_file> [output_csv_file]" << endl;
        return 1;
    }

    std::string input_path = argv[1];
    // Extract filename from input_path
    size_t last_slash = input_path.find_last_of("/\\");
    std::string filename = (last_slash == std::string::npos) ? input_path : 
        input_path.substr(last_slash + 1);

    // Remove .csv extension if present
    size_t dot = filename.rfind(".csv");
    if (dot != std::string::npos)
        filename = filename.substr(0, dot);
    // Compose output path: ../data/output/<filename>_exec_report.csv
    std::string output_path = "../data/output/" + filename + "_exec_report.csv";

    ExchangeSystem exchange;
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    std::vector<InputOrder> orders = FileHandler::readOrdersFromFile(input_path);
    exchange.processOrders(orders);
    FileHandler::writeReportsToFile(output_path, exchange.reports);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    for (auto it = exchange.orderBooks.begin(); it != exchange.orderBooks.end(); ++it) {
        it->second.printOrderBook(it->first);
    }

    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "\n Processing Completed in " << duration.count() << " us\n";
    cout << "Execution report saved to: " << output_path << endl;
    return 0;
}
