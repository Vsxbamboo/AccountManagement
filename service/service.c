//
// Created by vsx on 2024/2/28.
//

#include "service.h"

Status service_add(Card *cardp){
    return card_add(cardp);
}
Card* service_query(char* aName){
    return card_query(aName);
}
CardList service_fuzz_query(char *aName){
    return card_fuzz_query(aName);
}
void service_show(Card *cardp){
    card_show(cardp);
}
void service_clear(){
    card_clear();
}






Status service_saveCard(){
    saveCardToFile();
}

Status service_readCard(){
    readCard();
    /*
    for(int i=0;i<cardlength;i++){
        card_show(&cards[i]);
    }
     */
    CardList temp_pointer=cardList->next;
    while(temp_pointer!=NULL){
        card_show(&temp_pointer->data);
        temp_pointer=temp_pointer->next;
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