#include "Transaction.hpp"

Transaction::Transaction(int buy_order_id, int sell_order_id, float execution_price){
	this->buy_order_id = buy_order_id;
	this->sell_order_id = sell_order_id;
	this->execution_price = execution_price;
	this->proxima = nullptr;
}

Transaction::~Transaction(){
	// may delete buy and sell if they were pointers
}

int Transaction::getBuyOrderId(){
	return buy_order_id;
}
int Transaction::getSellOrderId(){
	return sell_order_id;
}
float Transaction::getExecutionPrice(){
	return execution_price;
}
