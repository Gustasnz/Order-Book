#include <iostream>
#include "OrderBook.hpp"

using namespace std;

int main() {

    OrderBook ob;

    cout << "=== Inserindo Ordens ===\n";

	cout << " >> adicionando a ordem (2, 'S', 9.0, 1):" << endl;
    ob.submit(Order(2, 'S', 9.0, 1)); // adiciona ordem de compra
    ob.printBuyOrders();
    ob.printSellOrders(); // sem vendas
    ob.printTransactions(); // sem transações
    cout << " >> adicionando a ordem (3, 'B', 5.0, 2):" << endl;
    ob.submit(Order(3, 'B', 5.0, 2)); // adiciona ordem de compra
    ob.printBuyOrders();
    ob.printSellOrders(); // sem vendas
    ob.printTransactions(); // sem transações
    cout << " >> adicionando a ordem (4, 'B', 9.0, 3):" << endl;
    ob.submit(Order(4, 'B', 9.0, 3)); // adiciona uma ordem de venda que será executada com uma compra anterior
    ob.printBuyOrders(); // uma das ordens é efetuada (deixa de estar na lista)
    ob.printSellOrders(); // a venda adicionada é imediatamente executada, então não aparece na lista de vendas
    ob.printTransactions(); // transação adicionada
    cout << " >> adicionando a ordem (5, 'S', 13.0, 4):" << endl;
    ob.submit(Order(5, 'S', 13.0, 4)); // adiciona ordem de compra
    ob.printBuyOrders();
    ob.printSellOrders(); // ordem adicionada
    ob.printTransactions();

    cout << "\n=== Cancelando Ordens ===\n";
    cout << " >> cancelando a ordem de Id 3:" << endl;
    cout << ob.cancel(3) << endl;
	ob.printBuyOrders();
    ob.printSellOrders();
    ob.printTransactions();
	cout << " >> adicionando a ordens:" << endl;
    ob.submit(Order(6, 'B', 7.5, 5));
    ob.submit(Order(7, 'S', 3.14, 6)); // imediatamente executada com compra anterior
    ob.submit(Order(8, 'B', 18.0, 7)); // imediatamente executada com venda anterior
    ob.submit(Order(9, 'B', 6.7, 8));
    ob.printBuyOrders();
    ob.printSellOrders();
    ob.printTransactions();
    cout << " >> cancelando a ordem de Id 9:" << endl;
    cout << ob.cancel(9) << endl;
	ob.printBuyOrders();
    ob.printSellOrders();
    ob.printTransactions();
    
    return 0;
}
