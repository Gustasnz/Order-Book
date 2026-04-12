#include "Order.hpp"

Order::Order(int id, char type, float price, int timestamp){ //cria uma ordem
	this->id = id;
    this->type = type;
    this->price = price;
    this->timestamp = timestamp;
    this->proxima = nullptr;
}

Order::~Order(){
	// nothing to delete, right?
}

int Order::getId(){//retorna atributo privado id
	return id;
}
char Order::getType(){ //retorna atributo privado type
	return type;
}
float Order::getPrice(){//retorna atributo privado price
	return price;
}
int Order::getTimestamp(){//retorna atributo privado timestamp
	return timestamp;
}
