#include "OrderBook.hpp"
using namespace std;

OrderBook::OrderBook() {
    first_buy = nullptr;
    first_sell = nullptr;
    first_transac = nullptr;
}

OrderBook::~OrderBook() {
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

void OrderBook::addTransaction(int buy_id, int sell_id, float price) {
	Transaction* t = new Transaction(buy_id, sell_id, price);
	t->proxima = first_transac;
	first_transac = t;
}

bool OrderBook::submit(Order order) {
	int id = order.getId();
	char type = order.getType();
    float price = order.getPrice();
    int timestamp = order.getTimestamp();
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
                if (!melhor_valor || compra->getPrice() > melhor_valor->getPrice() ||(compra->getPrice() == melhor_valor->getPrice() && compra->getTimestamp() < melhor_valor->getTimestamp())) {
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

bool OrderBook::cancel(int id) {
    Order* procura = first_buy; // procurando cancelar a compra
    Order* prev = nullptr;
    while (procura) {
        if (procura->getId() == id) {
            if (prev)
                prev->proxima = procura->proxima;
            else
                first_buy = procura->proxima;
            delete procura;
            return true;
        }
        prev = procura;
        procura = procura->proxima;
    }
    
    procura = first_sell; // procurando cancelar a venda
    prev = nullptr;
    while (procura) {
        if (procura->getId() == id) {
            if (prev)
                prev->proxima = procura->proxima;
            else
                first_sell = procura->proxima;
            delete procura;
            return true;
        }
        prev = procura;
        procura = procura->proxima;
    } return false;
}

Order* OrderBook::getBuyOrders(int* n) {
    int count = 0;
    int i = 0;
    Order* compra = first_buy;
    while (compra) {
        count++;
        compra = compra->proxima;
    } *n = count;
    if (count == 0) return nullptr;
    Order* ordens = new Order[count];
    compra = first_buy;
    while (compra) {
        ordens[i++] = Order(
            compra->getId(),
            compra->getType(),
            compra->getPrice(),
            compra->getTimestamp()
        ); compra = compra->proxima;
    } return ordens;
}

Order* OrderBook::getSellOrders(int* n) {
    int count = 0;
    int i = 0;
    Order* venda = first_sell;
    while (venda) {
        count++;
        venda = venda->proxima;
    } *n = count;
    if (count == 0) return nullptr;
    Order* ordens = new Order[count];
    venda = first_sell;
    while (venda) {
        ordens[i++] = Order(
            venda->getId(),
            venda->getType(),
            venda->getPrice(),
            venda->getTimestamp()
        ); venda = venda->proxima;
    } return ordens;
}

Transaction* OrderBook::getTransactions(int* n) {
    int count = 0;
    int i = 0;
    Transaction* curr = first_transac;
    while (transac) {
        count++;
        transac = transac->proxima;
    } *n = count;
    if (count == 0) return nullptr;
    Transaction* transac_list = new Transaction[count];
    transac = first_transac;
    while (curr) {
        transac_list[i++] = Transaction(
            transac->getBuyOrderId(),
            transac->getSellOrderId(),
            transac->getExecutionPrice()
        ); transac = transac->proxima;
    } return transac_list;
}

void OrderBook::printBuyOrders() {
    if (!first_buy) {
        cout << "Nenhuma ordem de compra...\n";
        return;
    }
    Order* curr = first_buy;
    cout << "Ordens de compra:\n";
    while (curr) {
        cout << "[" << curr->getId() << " | "
             << curr->getPrice() << " | "
             << curr->getTimestamp() << "]\n";
        curr = curr->proxima;
    }
}

void OrderBook::printSellOrders() {
    if (!first_buy) {
        cout << "Nenhuma ordem de venda...\n";
        return;
    }
    Order* curr = first_buy;
    cout << "Ordens de venda:\n";
    while (curr) {
        cout << "[" << curr->getId() << " | "
             << curr->getPrice() << " | "
             << curr->getTimestamp() << "]\n";
        curr = curr->proxima;
    }
}

void OrderBook::printTransactions() {
    if (!first_buy) {
        cout << "Nenhuma transação...\n";
        return;
    }
    Order* curr = first_buy;
    cout << "Transações:\n";
    while (curr) {
        cout << "[" << curr->getId() << " | "
             << curr->getPrice() << " | "
             << curr->getTimestamp() << "]\n";
        curr = curr->proxima;
    }
}
