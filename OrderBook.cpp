#include "OrderBook.hpp"
using namespace std;

OrderBook::OrderBook() {//método para criar OrderBook
    first_buy = nullptr;
    first_sell = nullptr;
    first_transac = nullptr;
}

OrderBook::~OrderBook() {//método para deletar OrderBook
	while (first_buy) {//percorre a lista buy eliminando seus integrantes
        Order* tmp = first_buy;
        first_buy = first_buy->proxima;
        delete tmp;
    }
    while (first_sell) {//percorre a lista sell eliminando seus integrantes 
        Order* tmp = first_sell;
        first_sell = first_sell->proxima;
        delete tmp;
    }
    while (first_transac) {//percorre a lista transac eliminando seus integrantes
        Transaction* tmp = first_transac;
        first_transac = first_transac->proxima;
        delete tmp;
    }
}

void OrderBook::addTransaction(int buy_id, int sell_id, float price) {//método para adicionar transação, adiciona no início da lista transac
	Transaction* t = new Transaction(buy_id, sell_id, price);
	t->proxima = first_transac;
	first_transac = t;
}

bool OrderBook::submit(Order order) {//método para adicionar uma ordem (sell ou buy)
	int id = order.getId();
	char type = order.getType();
    float price = order.getPrice();
    int timestamp = order.getTimestamp();
	Order* new_order = new Order(id, type, price, timestamp);//cria um ponteiro para a nova ordem
    if (type == 'B') {
        Order* melhor_valor = nullptr;
        Order* antes_da_melhor = nullptr;
        Order* venda = first_sell;
        Order* prev = nullptr;
        while (venda) {//percorre a lista sell
            if (venda->getPrice() <= price) { //durante o percurso só adiciona valores menores ou iguais ao preço da nova ordem
                if (!melhor_valor || venda->getPrice() < melhor_valor->getPrice() || (venda->getPrice() == melhor_valor->getPrice() && venda->getTimestamp() < melhor_valor->getTimestamp())) {
                    //verifica se o preço é menor do que o menor valor e em casos de preços iguais desempata pelo timestamp
                    melhor_valor = venda;
                    antes_da_melhor = prev;
                }
            }
            prev = venda;
            venda = venda->proxima;
        }
        if (melhor_valor) {//melhor_valor só não será nullptr se um valor válido foi encontrado
            if (antes_da_melhor)
                antes_da_melhor->proxima = melhor_valor->proxima;//salva a ordem antes da melhor para poder ajustar o ponteiro dela
            else
                first_sell = melhor_valor->proxima;
            addTransaction(id, melhor_valor->getId(), melhor_valor->getPrice());//realiza a transação
            //remove os ponteiros
            delete melhor_valor;
            delete new_order;
            return true;
        }
        //em caso de falha adiciona a ordem na lista buy
        new_order->proxima = first_buy;
        first_buy = new_order;
        return false;
    }
    else if (type == 'S') {
        Order* melhor_valor = nullptr;
        Order* antes_da_melhor = nullptr;
        Order* compra = first_buy;
        Order* prev = nullptr;
        while (compra) {//percorre a lista buy
            if (compra->getPrice()>= price) {//só aceita ordens buy válidas, isso é, com preço maior ou igual ao preço de venda
                if (!melhor_valor || compra->getPrice() > melhor_valor->getPrice() ||(compra->getPrice() == melhor_valor->getPrice() && compra->getTimestamp() < melhor_valor->getTimestamp())) {
                    //verifica se o preço atual é maior que o melhor valor e em caso de empate desempata pelo timestamp
                    melhor_valor = compra;
                    antes_da_melhor = prev;
                }
            }
            prev = compra;
            compra = compra->proxima;
        }
        if (melhor_valor) {//melhor valor só não será nullptr se um valor válido foi encontrado
            if (antes_da_melhor)
                antes_da_melhor->proxima = melhor_valor->proxima;//salva a anterior para arrumar os ponteiros 
            else
                first_buy = melhor_valor->proxima;
            addTransaction(melhor_valor->getId(), id, melhor_valor->getPrice());//realiza a transação
            delete melhor_valor;
            delete new_order;
            return true;
        }
        //não encontrou uma ordem válida
        new_order->proxima = first_sell;
        first_sell = new_order;
        return false;
    } return false;//tipo inválido, nem B nem S
}

bool OrderBook::cancel(int id) {
    Order* procura = first_buy; // procurando cancelar a compra
    Order* prev = nullptr;
    while (procura) {//procura na lista buy o id desejado e o remove se encontrar
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
    while (procura) {//procura na lista sell o id desejado e o remove se encontrar
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
    } return false;//se não retornou true até agora então não tinha o id em quaisquer uma das listas
}

Order* OrderBook::getBuyOrders(int* n) {//retorna uma lista de n elementos com os ponteiros das ordens buy
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

Order* OrderBook::getSellOrders(int* n) {//retorna uma lista de n elementos com os ponteiros das ordens sell
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

Transaction* OrderBook::getTransactions(int* n) {//retorna uma lista de n elementos com os ponteiros das transações realizadas
    int count = 0;
    int i = 0;
    Transaction* transac = first_transac;
    while (transac) {
        count++;
        transac = transac->proxima;
    } *n = count;
    if (count == 0) return nullptr;
    Transaction* transac_list = new Transaction[count];
    transac = first_transac;
    while (transac) {
        transac_list[i++] = Transaction(
            transac->getBuyOrderId(),
            transac->getSellOrderId(),
            transac->getExecutionPrice()
        ); transac = transac->proxima;
    } return transac_list;
}

void OrderBook::printBuyOrders() {//imprime todas as ordens buy
    if (!first_buy) {
        cout << "Nenhuma ordem de compra...\n";
        return;
    }
    Order* buy = first_buy;
    cout << "Ordens de compra:\n";
    while (buy) {
        cout << "[ Id: " << buy->getId()
             << " | Price: " << buy->getPrice()
             << " | Timestamp: " << buy->getTimestamp() << " ]\n";
        buy = buy->proxima;
    }
}

void OrderBook::printSellOrders() {//imprime todas as ordens sell
    if (!first_sell) {
        cout << "Nenhuma ordem de venda...\n";
        return;
    }
    Order* sell = first_sell;
    cout << "Ordens de venda:\n";
    while (sell) {
        cout << "[ Id: " << sell->getId()
             << " | Price: " << sell->getPrice()
             << " | Timestamp: " << sell->getTimestamp() << " ]\n";
        sell = sell->proxima;
    }
}

void OrderBook::printTransactions() {//imprime todas as transações
    if (!first_transac) {
        cout << "Nenhuma transação...\n";
        return;
    }
    Transaction* transac = first_transac;
    cout << "Transações:\n";
    while (transac) {
        cout << "[ Buy Id: " << transac->getBuyOrderId()
             << " | Sell Id: " << transac->getSellOrderId()
             << " | Price: " << transac->getExecutionPrice() << " ]\n";
        transac = transac->proxima;
    }
}
