#include <iostream>
#include "OrderBook.hpp"

using namespace std;

OrderBook::OrderBook() {
    buyHead = nullptr;
    sellHead = nullptr;
    transHead = nullptr;
}

OrderBook::~OrderBook() {

    Node* curr;

    curr = buyHead;
    while (curr) {
        Node* tmp = curr;
        curr = curr->next;
        delete tmp->order;
        delete tmp;
    }

    curr = sellHead;
    while (curr) {
        Node* tmp = curr;
        curr = curr->next;
        delete tmp->order;
        delete tmp;
    }
    
    TNode* t = transHead;
    while (t) {
        TNode* tmp = t;
        t = t->next;
        delete tmp->transaction;
        delete tmp;
    }
}

bool OrderBook::submit(Order order) {

    Node** head;
    Node** opposite;

    if (order.getType() == 'B') {
        head = &buyHead;
        opposite = &sellHead;
    } else {
        head = &sellHead;
        opposite = &buyHead;
    }

    Node* best = nullptr;
    Node* bestPrev = nullptr;

    Node* curr = *opposite;
    Node* prev = nullptr;

    while (curr) {

        Order* o = curr->order;
        bool compatible = false;

        if (order.getType() == 'B')
            compatible = (o->getPrice() <= order.getPrice());
        else
            compatible = (o->getPrice() >= order.getPrice());

        if (compatible) {

            if (!best) {
                best = curr;
                bestPrev = prev;
            } else {

                if (order.getType() == 'B') {
                    if (o->getPrice() < best->order->getPrice() ||
                        (o->getPrice() == best->order->getPrice() &&
                         o->getTimestamp() < best->order->getTimestamp())) {
                        best = curr;
                        bestPrev = prev;
                    }
                } else {
                    if (o->getPrice() > best->order->getPrice() ||
                        (o->getPrice() == best->order->getPrice() &&
                         o->getTimestamp() < best->order->getTimestamp())) {
                        best = curr;
                        bestPrev = prev;
                    }
                }
            }
        }

        prev = curr;
        curr = curr->next;
    }

    // encontrou contraparte
    if (best) {

        float price = best->order->getPrice();

        int buy_id = (order.getType() == 'B') ? order.getId() : best->order->getId();
        int sell_id = (order.getType() == 'S') ? order.getId() : best->order->getId();

        // remover da lista
        if (bestPrev)
            bestPrev->next = best->next;
        else
            *opposite = best->next;

        delete best->order;
        delete best;

        // registrar transação
        TNode* t = new TNode;
        t->transaction = new Transaction(buy_id, sell_id, price);
        t->next = transHead;
        transHead = t;

        return true;
    }

    // não encontrou → insere
    Node* n = new Node;
    n->order = new Order(order);
    n->next = *head;
    *head = n;

    return false;
}

bool OrderBook::cancel(int id) {

    Node* lists[2] = {buyHead, sellHead};
    Node** heads[2] = {&buyHead, &sellHead};

    for (int i = 0; i < 2; i++) {

        Node* curr = lists[i];
        Node* prev = nullptr;

        while (curr) {

            if (curr->order->getId() == id) {

                if (prev)
                    prev->next = curr->next;
                else
                    *heads[i] = curr->next;

                delete curr->order;
                delete curr;

                return true;
            }

            prev = curr;
            curr = curr->next;
        }
    }

    return false;
}

Order* OrderBook::getBuyOrders(int* n) {

    int count = 0;
    Node* curr = buyHead;

    while (curr) {
        count++;
        curr = curr->next;
    }

    *n = count;

    if (count == 0) return nullptr;

    Order* arr = new Order[count];
    curr = buyHead;

    int i = 0;
    while (curr) {
        arr[i++] = *(curr->order);
        curr = curr->next;
    }

    return arr;
}

void OrderBook::printBuyOrders() {
    cout << "Buy Orders:\n";

    if (!buyHead) {
        cout << "(empty)\n";
        return;
    }

    Node* curr = buyHead;
    while (curr) {
        cout << "[" << curr->order->getId()
             << " | " << curr->order->getPrice()
             << " | " << curr->order->getTimestamp()
             << "]\n";
        curr = curr->next;
    }
}
