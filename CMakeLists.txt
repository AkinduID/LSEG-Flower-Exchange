cmake_minimum_required(VERSION 3.20)

project(LSEG_Flower_Exchange)

set(CMAKE_CXX_STANDARD 14)

# GoogleTest setup
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Main executable
add_executable(LSEG_Flower_Exchange
        src/main.cpp
        src/Order.cpp
        src/ExecutionReport.cpp
        src/OrderBook.cpp
        src/OrderBookSide.cpp
        src/ExchangeSystem.cpp
        src/Utils.cpp
        src/FileHandler.cpp
)

target_include_directories(LSEG_Flower_Exchange PRIVATE include)

# Shared source files for tests
set(SRC_FILES
        src/Order.cpp
        src/ExecutionReport.cpp
        src/OrderBook.cpp
        src/OrderBookSide.cpp
        src/ExchangeSystem.cpp
        src/Utils.cpp
        src/FileHandler.cpp
)

# Tests
add_executable(test_order tests/test_order.cpp ${SRC_FILES})
target_link_libraries(test_order gtest_main)
target_include_directories(test_order PRIVATE include)
add_test(NAME test_order COMMAND test_order)

add_executable(test_orderbook tests/test_orderbook.cpp ${SRC_FILES})
target_link_libraries(test_orderbook gtest_main)
target_include_directories(test_orderbook PRIVATE include)
add_test(NAME test_orderbook COMMAND test_orderbook)

add_executable(test_executionreport tests/test_executionreport.cpp ${SRC_FILES})
target_link_libraries(test_executionreport gtest_main)
target_include_directories(test_executionreport PRIVATE include)
add_test(NAME test_executionreport COMMAND test_executionreport)

add_executable(test_exchangesystem tests/test_exchangesystem.cpp ${SRC_FILES})
target_link_libraries(test_exchangesystem gtest_main)
target_include_directories(test_exchangesystem PRIVATE include)
add_test(NAME test_exchangesystem COMMAND test_exchangesystem)