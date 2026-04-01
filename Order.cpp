#include "Order.hpp"

Order::Order(int id, char type, float price, int timestamp){
	id = id;
	type = type;
	price = price;
	timestamp = timestamp;
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
