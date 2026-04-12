# OrderBook em C++

Implementação de um **Order Book** em C++, capaz de gerenciar ordens de compra e venda de uma ação, realizar matchings e registrar transações.

---

##  Sobre

Este projeto simula o funcionamento básico de um livro de ordens (order book), muito usado em mercados financeiros.

Ele permite:

* Inserir ordens de **compra (Buy)** e **venda (Sell)**
* Realizar automaticamente os **matchings entre buy e sell**
* Registrar as **transações executadas**
* Cancelar ordens existentes
* Listar ponteiros de ordens e transações
* Imprimir ordens e transações existentes

A lógica principal segue:

* **Uma ordem Buy procura matching com o menor preço de Sell possível**
* **Uma ordem Sell procura matchingcom o maior preço de Buy possível**
* Empates são resolvidos por **timestamp (FIFO)**

---

## Estrutura do Projeto

* `OrderBook.hpp` → definição da classe
* `OrderBook.cpp` → implementação
* `Order` → representa uma ordem (id, tipo, preço, timestamp)
* `Transaction` → representa uma transação executada

Internamente, o sistema usa:

* Listas encadeadas para:

  * ordens de compra (`buy`)
  * ordens de venda (`sell`)
  * transações (`transactions`)

---

## Funcionalidades

### ✔️ Submissão de ordens

```cpp
bool submit(Order order);
```

* Insere uma nova ordem
* Tenta casar automaticamente com uma ordem oposta
* Retorna:

  * `true` → se houve transação
  * `false` → se a ordem foi adicionada ao book (Buy ou Sell)

---

### Cancelamento

```cpp
bool cancel(int id);
```

* Remove uma ordem pelo ID
* Procura tanto em buy quanto em sell

---

### Transações

```cpp
void addTransaction(int buy_id, int sell_id, float price);
```

* Registra uma transação realizada

---

### Consulta de dados

```cpp
Order* getBuyOrders(int* n);
Order* getSellOrders(int* n);
Transaction* getTransactions(int* n);
```

* Retorna arrays dinâmicos com os dados
* `n` recebe o tamanho do array



---

### Impressão

```cpp
printBuyOrders();
printSellOrders();
printTransactions();
```

* Mostra o estado atual do sistema no terminal

---

## Lógica de Matching

### Compra (Buy)

* Procura a ordem de venda com:

  * menor preço
  * e menor timestamp em caso de empate
* Condição:

```text
sell_price ≤ buy_price
```

---

### Venda (Sell)

* Procura a ordem de compra com:

  * maior preço
  * e menor timestamp em caso de empate
* Condição:

```text
buy_price ≥ sell_price
```

---

## Exemplo de uso

```cpp
OrderBook ob;

ob.submit(Order(1, 'B', 100.0, 1));
ob.submit(Order(2, 'S', 90.0, 2)); // gera transação

ob.printTransactions();
```

Saída esperada:

```
Transações:
[ Buy Id: 1 | Sell Id: 2 | Price: 100 ]
```

---

## Observações importantes

* Uso manual de memória (`new` / `delete`)
* Estrutura baseada em **listas encadeadas**
* Inserção é O(n) devido à busca pelo melhor match

---