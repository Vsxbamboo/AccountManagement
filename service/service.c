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
    //成员变量
    self->card_service = CardService_Init();
    self->billing_service=BillingService_Init();
    self->money_service=MoneyService_Init();
    //错误码
    self->CARD_VERIFY_ERROR=-1;
    self->CARD_CANNOT_LOGON=-2;
    self->CARD_CANNOT_LOGOUT=-3;
    self->CARD_BLANCE_ADJUST_ERROR=-4;
    self->CARD_CANNOT_FUND=-5;
    self->CARD_CANNOT_CANCEL=-6;
}

void Service_InitFunction(Service *self) {
    self->AddCard = Service_AddCard;
    self->QueryCard = Service_QueryCard;
    self->FuzzQueryCard = Service_FuzzQueryCard;
    self->ShowCard = Service_ShowCard;
    self->LogOnCard=Service_LogOnCard;
    self->LogOutCard=Service_LogOutCard;
    self->AddMoney=Service_AddMoney;
    self->RefundMoney=Service_RefundMoney;
    self->CancelCard=Service_CancelCard;
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
        return self->CARD_VERIFY_ERROR;
    }
    //验证是否符合上机状态
    if(self->card_service.CanLogOn(&self->card_service,card_pointer)){
        return self->CARD_CANNOT_LOGON;
    }
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

int Service_AddMoney(struct Service* self,Card* card_pointer, Money* money, MoneyInfo* money_info){
    //验证卡号和密码是否匹配
    if(self->card_service.VerifyCardPwd(&self->card_service,card_pointer)){
        if(self->card_service.CanFund(&self->card_service,card_pointer)){
            //在card_service中增加余额
            int rcode=self->card_service.AdjustBalance(&self->card_service,card_pointer,money);
            if(rcode==0){
                //填写money_info
                if(money_info!=NULL) {
                    strcpy(money_info->aCardName, card_pointer->aName);
                    money_info->fBalance = card_pointer->fBalance;
                    money_info->fMoney=money->fMoney;
                }
                //写入money
                self->money_service.AddMoney(&self->money_service,money);
                return 1;
            }else{
                return self->CARD_BLANCE_ADJUST_ERROR;
            }
        }else{
            return self->CARD_CANNOT_FUND;
        }

    }else{
        return self->CARD_VERIFY_ERROR;
    }
}

int Service_RefundMoney(struct Service* self,Card* card_pointer, Money* money,MoneyInfo *money_info){
    //验证卡号和密码是否匹配
    if(!self->card_service.VerifyCardPwd(&self->card_service,card_pointer)){
        return self->CARD_VERIFY_ERROR;
    }
    //验证卡能否退费
    if(!self->card_service.CanReFund(&self->card_service,card_pointer)){
        return self->CARD_CANNOT_FUND;
    }
    //在card_service中增加余额
    int rcode=self->card_service.AdjustBalance(&self->card_service,card_pointer,money);
    if(rcode==0){
        //填写money_info
        if(money_info!=NULL) {
            strcpy(money_info->aCardName, card_pointer->aName);
            money_info->fBalance = card_pointer->fBalance;
            money_info->fMoney=money->fMoney;
        }
        //写入money
        self->money_service.AddMoney(&self->money_service,money);
        return 1;
    }else{
        return self->CARD_BLANCE_ADJUST_ERROR;
    }
}

int Service_CancelCard(struct Service* self, Card* card_pointer,MoneyInfo *money_info){
    //判断卡是否能够注销
    //首先验证卡号和密码是否匹配
    if(!self->card_service.VerifyCardPwd(&self->card_service,card_pointer)){
        return self->CARD_VERIFY_ERROR;
    }
    //再单独判断卡是否能够注销
    if(!self->card_service.CanCancel(&self->card_service,card_pointer)){
        return self->CARD_CANNOT_CANCEL;
    }
    //注销卡
    //先退费
    Money money;
    strcpy(money.aCardName,card_pointer->aName);
    money.tTime=time(NULL);
    money.nStatus=1;
    money.fMoney=card_pointer->fBalance;
    money.nDel=0;
    self->RefundMoney(self,card_pointer,&money,money_info);
    //设置卡为注销状态
    self->card_service.CancelCard(&self->card_service,card_pointer->aName);
    //返回成功值
    return 1;
}

void Service_Release(Service *self) {
    self->card_service.Release(&self->card_service);
    self->billing_service.Release(&self->billing_service);
    self->money_service.Release(&self->money_service);
}

