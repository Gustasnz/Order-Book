#include <iostream>
#include "OrderBook.hpp"

using namespace std;

int main() {

    OrderBook ob;

    cout << "=== Inserindo ordens ===\n";

    ob.submit(Order(2, 'S', 9.0, 1));
    ob.submit(Order(3, 'B', 10.0, 2));

    ob.printBuyOrders();
    ob.printSellOrders();
    ob.printTransactions();

    cout << "\n=== Novo cenário ===\n";

    ob.submit(Order(10, 'S', 9.5, 1));
    ob.submit(Order(11, 'S', 8.0, 2));
    ob.submit(Order(12, 'S', 8.0, 3));
    ob.submit(Order(13, 'B', 10.0, 4));

    ob.printSellOrders();
    ob.printTransactions();

    cout << "\n=== Cancelamento ===\n";
    cout << ob.cancel(10) << endl;

    ob.printSellOrders();

    return 0;
}
