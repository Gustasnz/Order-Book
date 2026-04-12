# OrderBook em C++

Implementação de um **Order Book** em C++ para gerenciar ordens de compra e venda, realizar *matching* automático e registrar transações.

## Sobre

O sistema simula um livro de ordens financeiro, permitindo:

- Inserir ordens de compra (Buy) e venda (Sell)
- Executar *matching* automaticamente
- Registrar transações
- Cancelar ordens
- Listar e imprimir ordens e transações

A lógica segue prioridade de **preço** e, em caso de empate, **timestamp (FIFO)**.

## Estrutura

- `OrderBook` → gerenciamento do sistema
- `Order` → representa uma ordem
- `Transaction` → representa uma transação

Internamente, utiliza **listas encadeadas** para ordens de compra, venda e transações.

## Funcionalidades

- `submit(Order)` → insere ordem e tenta executar (*true* se houve match)
- `cancel(id)` → remove ordem
- `get*()` → retorna arrays de ordens/transações
- `print*()` → exibe estado atual

## Matching

- **Buy** casa com menor preço de Sell (`sell ≤ buy`)
- **Sell** casa com maior preço de Buy (`buy ≥ sell`)
- Empate resolvido por timestamp

## Exemplo

```cpp
OrderBook ob;

ob.submit(Order(1, 'B', 100.0, 1));
ob.submit(Order(2, 'S', 90.0, 2));

ob.printTransactions();

## Compilação
Para compilar o projeto, utilize um compilador C++ (como o `g++`) executando:

```bash
g++ main.cpp OrderBook.cpp Order.cpp Transaction.cpp -o order_book
