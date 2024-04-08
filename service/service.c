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
    self->CARD_VERIFY_ERROR=-1;
    self->CARD_CANNOT_LOGON=-2;
    self->CARD_CANNOT_LOGOUT=-3;
}

void Service_InitFunction(Service *self) {
    self->AddCard = Service_AddCard;
    self->QueryCard = Service_QueryCard;
    self->FuzzQueryCard = Service_FuzzQueryCard;
    self->ShowCard = Service_ShowCard;
    self->LogOnCard=Service_LogOnCard;
    self->LogOutCard=Service_LogOutCard;
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

int Service_LogOnCard(struct Service* self, Card* card_pointer,LogonInfo* login_info){
    //验证卡号和密码是否匹配
    if(self->card_service.VerifyCardPwd(&self->card_service,card_pointer)){
        //验证是否符合上机状态
        if(self->card_service.CanLogOn(&self->card_service,card_pointer)){
            //修改卡信息中的上机时间等
            self->card_service.LogOnCard(&self->card_service, card_pointer->aName);
            //更新卡
            card_pointer=self->card_service.Query(&self->card_service,card_pointer->aName);
            //添加计费信息
            self->billing_service.AddBilling(&self->billing_service,card_pointer);
            //返回登录信息
            if(login_info!=NULL){
                strcpy(login_info->aCardName,card_pointer->aName);
                login_info->fBalance=card_pointer->fBalance;
                login_info->tLogon=card_pointer->tLast;
            }
            return 1;
        }else{
            return self->CARD_CANNOT_LOGON;
        }

    }else{
        return self->CARD_VERIFY_ERROR;
    }

}

int Service_LogOutCard(struct Service* self, Card* card_pointer,SettleInfo* settle_info){
    //验证卡号和密码是否匹配
    if(self->card_service.VerifyCardPwd(&self->card_service,card_pointer)){
        //验证是否符合下机状态
        if(self->card_service.CanLogOut(&self->card_service,card_pointer)){
            //结算消费信息
            Billing* result_billing=self->billing_service.SettleBilling(&self->billing_service,card_pointer);
            if(result_billing!=NULL){
                //修改卡信息中的余额和上次使用时间等
                self->card_service.LogOutCard(&self->card_service, card_pointer->aName,result_billing);
                //返回登出信息
                if(settle_info!=NULL){
                    //填写登出结构体
                    strcpy(settle_info->aCardName,card_pointer->aName);
                    settle_info->tStart=result_billing->tStart;
                    settle_info->tEnd=result_billing->tEnd;
                    settle_info->fAmount=result_billing->fAmount;
                    settle_info->fBalance=card_pointer->fBalance-result_billing->fAmount;
                }
                return 1;
            }else{
                return self->CARD_CANNOT_LOGOUT;
            }
        }else{
            return self->CARD_CANNOT_LOGOUT;
        }

    }else{
        return self->CARD_VERIFY_ERROR;
    }
}

void Service_Release(Service *self) {
    self->card_service.Release(&self->card_service);
    self->billing_service.Release(&self->billing_service);
}

