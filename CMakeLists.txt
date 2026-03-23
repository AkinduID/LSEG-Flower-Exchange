cmake_minimum_required(VERSION 4.1)
project(LSEG_Flower_Exchange)

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
        Include/Utils.h)
