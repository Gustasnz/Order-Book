#include "Transaction.hpp"

Transaction::Transaction(int buy_order_id, int sell_order_id, float execution_price){
	buy = buy_order_id;
	sell = sell_order_id;
	price = execution_price;
	next = nullptr;
}

Transaction::~Transaction(){
	// may delete buy and sell if they were pointers
}

Trasaction::GetBuyOrderId(){
	return buy;
}
Trasaction::GetSellOrderId(){
	return sell;
}
Trasaction::GetExecutionPrice(){
	return price;
}
