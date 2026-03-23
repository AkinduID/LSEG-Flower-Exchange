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
        Src/main.cpp
        Src/Order.cpp
        Include/Order.h
        Src/ExecutionReport.cpp
        Include/ExecutionReport.h
        Src/OrderBook.cpp
        Include/OrderBook.h
        Src/OrderBookSide.cpp
        Include/OrderBookSide.h
        Src/ExchangeSystem.cpp
        Include/ExchangeSystem.h
        Src/Utils.cpp
        Include/Utils.h
        Src/FileHandler.cpp
        Include/FileHandler.h)

# Test executables
add_executable(test_order tests/test_order.cpp)
target_link_libraries(test_order gtest_main)
add_test(NAME test_order COMMAND test_order)

add_executable(test_orderbook tests/test_orderbook.cpp)
target_link_libraries(test_orderbook gtest_main)
add_test(NAME test_orderbook COMMAND test_orderbook)

add_executable(test_executionreport tests/test_executionreport.cpp)
target_link_libraries(test_executionreport gtest_main)
add_test(NAME test_executionreport COMMAND test_executionreport)

add_executable(test_exchangesystem tests/test_exchangesystem.cpp)
target_link_libraries(test_exchangesystem gtest_main)
add_test(NAME test_exchangesystem COMMAND test_exchangesystem)
