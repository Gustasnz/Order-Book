#include "Order.hpp"
#include "Transaction.hpp"
#include <iostream>

class OrderBook {

private:
    Order* first_buy = nullptr;
    Order* first_sell = nullptr;
    Transaction* first_transac = nullptr;
    void addTransaction(int buy_id, int sell_id, float price);

public:
    OrderBook();
    ~OrderBook();

    bool submit(Order order);
    bool cancel(int id);

    Order* getBuyOrders(int* n);
    Order* getSellOrders(int* n);
    Transaction* getTransactions(int* n);

    void printBuyOrders();
    void printSellOrders();
    void printTransactions();
};
