#include "Transaction.hpp"

Transaction::Transaction(int buy_order_id, int sell_order_id, float execution_price){//cria transação
	this->buy_order_id = buy_order_id;
	this->sell_order_id = sell_order_id;
	this->execution_price = execution_price;
	this->proxima = nullptr;
}

Transaction::~Transaction(){
	// may delete buy and sell if they were pointers
}

int Transaction::getBuyOrderId(){//retorna atributo privado buy_order_id
	return buy_order_id;
}
int Transaction::getSellOrderId(){//retorna atributo privado sell_order_id
	return sell_order_id;
}
float Transaction::getExecutionPrice(){//retorna atributo privado execution_price
	return execution_price;
}
