cmake_minimum_required(VERSION 4.1)

project(LSEG_Flower_Exchange)

# GoogleTest setup
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(CMAKE_CXX_STANDARD 14)

add_executable(LSEG_Flower_Exchange
        src/main.cpp
        src/Order.cpp
        include/Order.h
        src/ExecutionReport.cpp
        include/ExecutionReport.h
        src/OrderBook.cpp
        include/OrderBook.h
        src/OrderBookSide.cpp
        include/OrderBookSide.h
        src/ExchangeSystem.cpp
        include/ExchangeSystem.h
        src/Utils.cpp
        include/Utils.h
        src/FileHandler.cpp
        include/FileHandler.h)

# Test executables

# Test executables with all required sources
set(SRC_FILES
        src/Order.cpp
        src/ExecutionReport.cpp
        src/OrderBook.cpp
        src/OrderBookSide.cpp
        src/ExchangeSystem.cpp
        src/Utils.cpp
        src/FileHandler.cpp
)

add_executable(test_order tests/test_order.cpp ${SRC_FILES})
target_link_libraries(test_order gtest_main)
add_test(NAME test_order COMMAND test_order)

add_executable(test_orderbook tests/test_orderbook.cpp ${SRC_FILES})
target_link_libraries(test_orderbook gtest_main)
add_test(NAME test_orderbook COMMAND test_orderbook)

add_executable(test_executionreport tests/test_executionreport.cpp ${SRC_FILES})
target_link_libraries(test_executionreport gtest_main)
add_test(NAME test_executionreport COMMAND test_executionreport)

add_executable(test_exchangesystem tests/test_exchangesystem.cpp ${SRC_FILES})
target_link_libraries(test_exchangesystem gtest_main)
add_test(NAME test_exchangesystem COMMAND test_exchangesystem)
