//
// Created by Wimukthi Madushan on 3/20/2026.
//

#include "../include/Order.h"
#include "../include/Utils.h"
#include "../include/ExecutionReport.h"

ExecutionReport ExecutionReport::createFillReport(const FilledOrder& filledOrder, const std::string& instrument, int side, double price, int quantity) {
	ExecutionReport r;
	r.orderId = filledOrder.orderId;
	r.clientOrderId = filledOrder.clientOrderId;
	r.instrument = instrument;
	r.side = side;
	r.price = price;
	r.quantity = quantity;
	r.status = 2; // Fill
	r.reason = "";
	r.timestamp = Utils::getTimestamp();
	return r;
}

ExecutionReport ExecutionReport::createFillReport(const Order& restingOrder, const std::string& instrument, int side, double price, int quantity) {
	ExecutionReport r;
	r.orderId = restingOrder.orderId;
	r.clientOrderId = restingOrder.clientOrderId;
	r.instrument = instrument;
	r.side = side;
	r.price = price;
	r.quantity = quantity;
	r.status = 2; // Fill
	r.reason = "";
	r.timestamp = Utils::getTimestamp();
	return r;
}

ExecutionReport ExecutionReport::createAggressorReport(const Order& incomingOrder, const std::string& instrument, double price, int quantity, int status) {
	ExecutionReport r;
	r.orderId = incomingOrder.orderId;
	r.clientOrderId = incomingOrder.clientOrderId;
	r.instrument = instrument;
	r.side = incomingOrder.side;
	r.price = price;
	r.quantity = quantity;
	r.status = status; // Fill or Pfill
	r.reason = "";
	r.timestamp = Utils::getTimestamp();
	return r;
}

ExecutionReport ExecutionReport::createNewReport(const Order& order, const std::string& instrument) {
	ExecutionReport r;
	r.orderId = order.orderId;
	r.clientOrderId = order.clientOrderId;
	r.instrument = instrument;
	r.side = order.side;
	r.price = order.price;
	r.quantity = order.quantity;
	r.status = 0; // New
	r.reason = "";
	r.timestamp = Utils::getTimestamp();
	return r;
}

ExecutionReport ExecutionReport::createRejectReport(const Order& order, const std::string& instrument, const std::string& reason) {
    ExecutionReport r;
    r.orderId = order.orderId;
    r.clientOrderId = order.clientOrderId;
    r.instrument = instrument;
    r.side = order.side;
    r.price = order.price;
    r.quantity = order.quantity;
    r.status = 1; // Rejected
    r.reason = reason;
    r.timestamp = Utils::getTimestamp();
    return r;
}
