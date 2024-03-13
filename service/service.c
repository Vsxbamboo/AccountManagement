//
// Created by vsx on 2024/2/28.
//

#include "service.h"

Status service_add(Card *cardp){
    return addCard(cardp);
}
Card* service_query(char* aName){
    return queryCard(aName);
}
void service_show(Card *cardp){
    showCard(cardp);
}

Status service_saveCard(){
    saveCardToFile();
}

Status service_readCard(){
    readCard();
    for(int i=0;i<cardlength;i++){
        showCard(&cards[i]);
    }
    return 0;
}

int service_getCount(){
    return getCardCountFromFile();
}

Status service_updateCard(Card *p,int n){
    updateCardInFile(p,n);
}

int service_ifinFile(char *pName){
    return CardisExist(pName);
}