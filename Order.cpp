#include "Order.hpp"

Order::Order(int id, char type, float price, int timestamp){
	this->id = id;
    this->type = type;
    this->price = price;
    this->timestamp = timestamp;
    this->next = nullptr;
}

Order::~Order(){
	// nothing to delete, right?
}

Order::GetId(){
	return id;
}
Order::GetType(){
	return type;
}
Order::GetPrice(){
	return price;
}
Order::GetTimestamp(){
	return timestamp;
}
