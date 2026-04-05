class BuyOrder{
public:
    BuyOrder* proxima=nullptr;
    //method buyorder is necessary here but i am a lazy bum
}
class SellOrder{
public:
    SellOrder* proxima=nullptr;
    int price;
}
class Transaction{
public:
    Transaction* proxima=nullptr;
}
class OrderSystem{
public:
    BuyOrder* first_buy=nullptr;
    SellOrder* first_sell=nullptr;
    Transaction* first_transac=nullptr;
    void add_order(int id, char type, float price, int timestamp){
        if(type == 'B'){
            if(this->first_sell==nullptr){
                if(this->first_buy==nullptr){
                    this->first_buy=BuyOrder(id,price,timestamp);
                }
                else{
                    BuyOrder* compra=this->first_buy;
                    while(compra->proxima!=nullptr){
                        if(compra==BuyOrder(id,price,timestamp)){
                            //error, two orders are the same
                        }
                        else{
                            if (compra->proxima!=nullptr){
                                compra=compra->proxima;
                            }
                        }
                    }
                }

            }
            else{
                int melhor_valor=this->first_buy->price;
                SellOrder* antes_da_melhor=this->first_sell;
                SellOrder* venda=this->first_sell;
                while(venda->proxima!=nullptr){
                    if(venda->proxima->price<melhor_valor){
                        antes_da_melhor=venda->proxima;
                        melhor_valor=venda->proxima->price;
                        
                    }
                    if(venda->proxima->proxima!=nullptr){
                        venda=venda->proxima;
                    }   
                }
                if(price<melhor_valor){
                    //no deal
                }
                else{
                    SellOrder*temp=antes_da_melhor->proxima;
                    if(first_transac==nullptr){
                        first_transac=Transaction(temp,BuyOrder(id,price,timestamp))
                        antes_da_melhor->proxima=temp->proxima;
                    }
                    else{
                        Transaction* transac=first_transac;
                        while(transac->proxima!=nullptr){
                            transac=transac->proxima;
                        }
                        transac->proxima=Transaction(temp,BuyOrder(id,price,timestamp));
                    }
                }
            }
        }
        if(type=="s"){
    if(this->first_buy==nullptr){
        // no buyers → just insert into sell list
        if(this->first_sell==nullptr){
            this->first_sell = new SellOrder(id, price, timestamp);
        }
        else{
            SellOrder* venda = this->first_sell;
            while(venda->proxima != nullptr){

                if(venda->id == id){
                    // error, duplicate order
                }
                venda = venda->proxima;
            }
            venda->proxima = new SellOrder(id, price, timestamp);
        }
    }
    else{
        // find BEST BUY (highest price)
        int melhor_valor = this->first_buy->price;
        BuyOrder* antes_do_melhor = nullptr;
        BuyOrder* compra = this->first_buy;

        while(compra->proxima != nullptr){
            if(compra->proxima->price > melhor_valor){
                melhor_valor = compra->proxima->price;
                antes_do_melhor = compra;
            }
            compra = compra->proxima;
        }

        if(price > melhor_valor){
            // no deal (seller wants too much)
        }
        else{
            // match with best buy
            BuyOrder* temp;

            if(antes_do_melhor == nullptr){
                // best is first node
                temp = this->first_buy;
                this->first_buy = temp->proxima;
            }
            else{
                temp = antes_do_melhor->proxima;
                antes_do_melhor->proxima = temp->proxima;
            }

            // create transaction
            if(first_transac == nullptr){
                first_transac = new Transaction(temp, new SellOrder(id, price, timestamp));
            }
            else{
                Transaction* transac = first_transac;
                while(transac->proxima != nullptr){
                    transac = transac->proxima;
                }
                transac->proxima = new Transaction(temp, new SellOrder(id, price, timestamp));
            }
        }
    }
}
}
}
