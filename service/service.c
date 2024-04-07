//
// Created by vsx on 2024/2/28.
//

#include "service.h"

Service Service_Init() {
    Service self;
    Service_InitVariable(&self);
    Service_InitFunction(&self);
    return self;
}

void Service_InitVariable(Service *self) {
    self->card_service = CardService_Init();
    self->billing_service=BillingService_Init();
}

void Service_InitFunction(Service *self) {
    self->AddCard = Service_AddCard;
    self->QueryCard = Service_QueryCard;
    self->FuzzQueryCard = Service_FuzzQueryCard;
    self->ShowCard = Service_ShowCard;
    self->LogOnCard=Service_LogOnCard;
    self->Release = Service_Release;
}

Status Service_AddCard(Service *self, Card *cardp) {
    return self->card_service.Add(&self->card_service, cardp);
}

Card *Service_QueryCard(Service *self, char *aName) {
    return self->card_service.Query(&self->card_service, aName);
}

LinkedList Service_FuzzQueryCard(Service *self, char *aName) {
    return self->card_service.FuzzQuery(&self->card_service, aName);
}

void Service_ShowCard(Service *self, Card *cardp) {
    self->card_service.Show(&self->card_service, cardp);
}

int Service_LogOnCard(struct Service* self, Card* card_pointer){
    //验证卡号和密码是否匹配
    if(self->card_service.VerifyCardPwd(&self->card_service,card_pointer)){
        //验证是否符合上机状态
        if(self->card_service.CanLogOn(&self->card_service,card_pointer)){
            //修改卡信息中的上机时间等
            self->card_service.LogOnCard(&self->card_service, card_pointer->aName);
            //添加消费信息
            Billing billing;
            strcpy(billing.aCardName,card_pointer->aName);
            billing.tStart=card_pointer->tLast;
            billing.tEnd=billing.tStart;
            billing.fAmount=0;
            billing.nStatus=0;
            billing.nDel=0;
            self->billing_service.Add(&self->billing_service,&billing);
            return 1;
        }

    }
    return 0;
}

void Service_Release(Service *self) {
    self->card_service.Release(&self->card_service);
    self->billing_service.Release(&self->billing_service);
}

