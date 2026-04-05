#include <iostream>
#include "Order.hpp"
#include "Transaction.hpp"

using namespace std;

class OrderSystem {

private:
    Order* first_buy = nullptr;
    Order* first_sell = nullptr;
    Transaction* first_transac = nullptr;
    void addTransaction(int buy_id, int sell_id, float price) {
        Transaction* t = new Transaction(buy_id, sell_id, price);
        t->proxima = first_transac;
        first_transac = t;
    }

public:
    ~OrderSystem() {
        while (first_buy) {
            Order* tmp = first_buy;
            first_buy = first_buy->proxima;
            delete tmp;
        }
        while (first_sell) {
            Order* tmp = first_sell;
            first_sell = first_sell->proxima;
            delete tmp;
        }
        while (first_transac) {
            Transaction* tmp = first_transac;
            first_transac = first_transac->proxima;
            delete tmp;
        }
    }

    bool add_order(int id, char type, float price, int timestamp) {
        Order* new_order = new Order(id, type, price, timestamp);
        if (type == 'B') {
            Order* melhor_valor = nullptr;
            Order* antes_da_melhor = nullptr;
            Order* venda = first_sell;
            Order* prev = nullptr;
            while (venda) {
                if (venda->getPrice() <= price) {
                    if (!melhor_valor || venda->getPrice() < melhor_valor->getPrice() || (venda->getPrice() == melhor_valor->getPrice() && venda->getTimestamp() < melhor_valor->getTimestamp())) {
                        melhor_valor = venda;
                        antes_da_melhor = prev;
                    }
                }
                prev = venda;
                venda = venda->proxima;
            }
            if (melhor_valor) {
                if (antes_da_melhor)
                    antes_da_melhor->proxima = melhor_valor->proxima;
                else
                    first_sell = melhor_valor->proxima;
                addTransaction(id, melhor_valor->getId(), melhor_valor->getPrice());
                delete melhor_valor;
                delete new_order;
                return true;
            }
            new_order->proxima = first_buy;
            first_buy = new_order;
            return false;
        }
        else if (type == 'S') {
            Order* melhor_valor = nullptr;
            Order* antes_da_melhor = nullptr;
            Order* compra = first_buy;
            Order* prev = nullptr;
            while (compra) {
                if (compra->getPrice()>= price) {
                    if (!melhor_valor || compra->getPrice() < melhor_valor->getPrice() ||(compra->getPrice() == melhor_valor->getPrice() && compra->getTimestamp() < melhor_valor->getTimestamp())) {
                        melhor_valor = compra;
                        antes_da_melhor = prev;
                    }
                }
                prev = compra;
                compra = compra->proxima;
            }
            if (melhor_valor) {
                if (antes_da_melhor)
                    antes_da_melhor->proxima = melhor_valor->proxima;
                else
                    first_buy = melhor_valor->proxima;
                addTransaction(melhor_valor->getId(), id, melhor_valor->getPrice());
                delete melhor_valor;
                delete new_order;
                return true;
            }
            new_order->proxima = first_sell;
            first_sell = new_order;
            return false;
        } return false;
    }

    bool cancel(int id) {
        Order* compra = first_buy; // procurando cancelar uma compra
        Order* prev = nullptr;
        while (compra) {
            if (compra->getId() == id) {
                if (prev)
                    prev->proxima = compra->proxima;
                else
                    first_buy = compra->proxima;
                delete compra;
                return true;
            }
            prev = compra;
            compra = compra->proxima;
        }
        
        Order* compra = first_sell; // procurando cancelar uma venda
        prev = nullptr;
        while (compra) {
            if (compra->getId() == id) {
                if (prev)
                    prev->proxima = compra->proxima;
                else
                    first_sell = compra->proxima;
                delete compra;
                return true;
            }
            prev = compra;
            compra = compra->proxima;
        } return false;
    }

    void printBuys() {
        cout << "Buy Orders:\n";
        if (!first_buy) {
            cout << "(empty)\n";
            return;
        }
        Order* curr = first_buy;
        while (curr) {
            cout << "[" << curr->getId() << " | "
                 << curr->getPrice() << " | "
                 << curr->getTimestamp() << "]\n";
            curr = curr->proxima;
        }
    }
    
    void printSells() {
        cout << "Sell Orders:\n";
        if (!first_sell) {
            cout << "(empty)\n";
            return;
        }
        Order* curr = first_sell;
        while (curr) {
            cout << "[" << curr->getId() << " | "
                 << curr->getPrice() << " | "
                 << curr->getTimestamp() << "]\n";
            curr = curr->proxima;
        }
    }

    void printTransactions() {
        cout << "Transactions:\n";
        if (!first_transac) {
            cout << "(empty)\n";
            return;
        }
        Transaction* curr = first_transac;
        /*while (curr) {
            cout << "[" << curr->buy_id << ", "
                 << curr->sell_id << ", "
                 << curr->price << "]\n";
            curr = curr->proxima;
        }*/
    }
};
