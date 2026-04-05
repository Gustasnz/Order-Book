class OrderBook {

private:

    struct Node {
        Order* order;
        Node* next;
    };

    struct TNode {
        Transaction* transaction;
        TNode* next;
    };

    Node* buyHead;
    Node* sellHead;
    TNode* transHead;

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

    // Outros métodos auxiliares, se necessário
};
