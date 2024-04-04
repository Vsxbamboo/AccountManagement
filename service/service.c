//
// Created by vsx on 2024/2/28.
//

#include "service.h"
#include "../file/card_file.h"

Service Service_Init(){
    Service self;
    Service_InitVariable(&self);
    Service_InitFunction(&self);
    return self;
}
void Service_InitVariable(Service* self){
    self->card_service=CardService_Init();
}
void Service_InitFunction(Service* self){
    self->AddCard=Service_AddCard;
    self->QueryCard=Service_QueryCard;
    self->FuzzQueryCard=Service_FuzzQueryCard;
    self->ShowCard=Service_ShowCard;
    self->Release=Service_Release;
}

Status Service_AddCard(Service* self,Card *cardp){
    return self->card_service.Add(&self->card_service,cardp);
}
Card* Service_QueryCard(Service* self,char* aName){
    return self->card_service.Query(&self->card_service,aName);
}
LinkedList Service_FuzzQueryCard(Service* self,char *aName){
    return self->card_service.FuzzQuery(&self->card_service,aName);
}
void Service_ShowCard(Service* self,Card *cardp){
    self->card_service.Show(&self->card_service,cardp);
}
void Service_Release(Service* self){
    self->card_service.Release(&self->card_service);
}

//废弃代码
//Status service_saveCard(){
//    saveCardToFile();
//}
//
//Status service_readCard(){
//    readCard();
//    CardList temp_pointer=cardList->next;
//    while(temp_pointer!=NULL){
//        //card_show(&temp_pointer->data);
//        temp_pointer=temp_pointer->next;
//    }
//    return 0;
//}
//
//int service_getCount(){
//    return getCardCountFromFile();
//}
//
//Status service_updateCard(Card *p,int n){
//    updateCardInFile(p,n);
//}
//
//int service_ifinFile(char *pName){
//    return CardisExist(pName);
//}