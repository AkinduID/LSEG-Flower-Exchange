//
// Created by Wimukthi Madushan on 3/20/2026.
//

#include "../include/Order.h"
#include "../include/Utils.h"
#include "../include/ExecutionReport.h"


ExecutionReport ExecutionReport::createFillReport(const FilledOrder& filledOrder, 
	const std::string& instrument, OrderSide side, double price, int quantity) {
		
	ExecutionReport r;
	r.orderId = filledOrder.orderId;
	r.clientOrderId = filledOrder.clientOrderId;
	r.instrument = instrument;
	r.side = side==OrderSide::Buy ? 1 : 2;
	r.price = price;
	r.quantity = quantity;
	r.status = OrderStatus::Fill;
	r.reason = "";
	r.timestamp = Utils::getTimestamp();
	return r;
}


ExecutionReport ExecutionReport::createFillReport(const Order& restingOrder, 
	const std::string& instrument, OrderSide side, double price, int quantity) {

	ExecutionReport r;
	r.orderId = restingOrder.orderId;
	r.clientOrderId = restingOrder.clientOrderId;
	r.instrument = instrument;
	r.side = side==OrderSide::Buy ? 1 : 2;
	r.price = price;
	r.quantity = quantity;
	r.status = OrderStatus::Fill;
	r.reason = "";
	r.timestamp = Utils::getTimestamp();
	return r;
}


ExecutionReport ExecutionReport::createAggressorReport(const Order& incomingOrder, 
	const std::string& instrument, double price, int quantity, OrderStatus status) {

	ExecutionReport r;
	r.orderId = incomingOrder.orderId;
	r.clientOrderId = incomingOrder.clientOrderId;
	r.instrument = instrument;
	r.side = incomingOrder.side==OrderSide::Buy ? 1 : 2;
	r.price = price;
	r.quantity = quantity;
	r.status = status;
	r.reason = "";
	r.timestamp = Utils::getTimestamp();
	return r;
}


ExecutionReport ExecutionReport::createNewReport(const Order& order, 
	const std::string& instrument) {

	ExecutionReport r;
	r.orderId = order.orderId;
	r.clientOrderId = order.clientOrderId;
	r.instrument = instrument;
	r.side = order.side==OrderSide::Buy ? 1 : 2;
	r.price = order.price;
	r.quantity = order.quantity;
	r.status = OrderStatus::New;
	r.reason = "";
	r.timestamp = Utils::getTimestamp();
	return r;
}


ExecutionReport ExecutionReport::createRejectReport(const Order& order, 
	const InputOrder& inputOrder, const std::string& instrument, const std::string& reason) {

	ExecutionReport r;
	r.orderId = order.orderId;
	r.clientOrderId = order.clientOrderId;
	r.instrument = instrument;
	r.side = inputOrder.side; // Use original side from input
	r.price = order.price;
	r.quantity = order.quantity;
	r.status = OrderStatus::Rejected;
	r.reason = reason;
	r.timestamp = Utils::getTimestamp();
	return r;
}
