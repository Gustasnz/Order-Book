# Order Book

## Descrição
Este projeto implementa um sistema simplificado de *order book* em C++, responsável por gerenciar ordens de compra e venda de ativos. O sistema permite inserir ordens, realizar o *matching* automático entre ordens compatíveis (execução), cancelar ordens existentes e registrar as transações realizadas.

Internamente, são utilizadas listas encadeadas para armazenar ordens de compra, ordens de venda e o histórico de transações.

## Compilação
Para compilar o projeto, utilize um compilador C++ (como o `g++`) executando:

```bash
g++ main.cpp OrderBook.cpp Order.cpp Transaction.cpp -o order_book
