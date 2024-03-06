//
// Created by vsx on 2024/2/28.
//

#include "service.h"

Status service_add(Card *cardp){
    return addCard(cardp);
}
void* service_query(char* aName){
    return findCard(aName);
}
void service_show(Card *cardp){
    showCard(cardp);
}