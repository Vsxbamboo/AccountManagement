#ifndef ACCOUNTMANAGEMENT_BILLING_SERVICE_H
#define ACCOUNTMANAGEMENT_BILLING_SERVICE_H

#include "../enities/linked_list.h"
#include "../file/billing_file.h"
#include "../model.h"
#include "../global.h"
#include "string.h"

typedef struct BillingService{
    //成员变量
    LinkedList billing_list;
    BillingFile billing_file;
    //成员函数
    int (*Add)(struct BillingService* self,Billing* billing_pointer);
    int (*AddBilling)(struct BillingService* self,Card* card_pointer);
    Billing* (*SettleBilling)(struct BillingService* self,Card* card_pointer);
    Billing* (*QueryLast)(struct BillingService* self,Card* card_pointer);
    int (*SaveBillingToFile)(struct BillingService* self);
    //析构函数
    void (*Release)(struct BillingService* self);
}BillingService;

BillingService BillingService_Init();
void BillingService_InitVariable(BillingService* self);
void BillingService_InitFunction(BillingService* self);
int BillingService_Add(BillingService* self,Billing* billing_pointer);
int BillingService_AddBilling(BillingService* self,Card* card_pointer);
Billing* BillingService_QueryLast(struct BillingService* self,Card* card_pointer);
int BillingService_SaveBillingToFile(struct BillingService* self);
Billing* BillingService_SettleBilling(BillingService* self,Card* card_pointer);

void BillingService_Release(BillingService* self);

int BillingService_CompareLast(void* a,void* b);
#endif //ACCOUNTMANAGEMENT_BILLING_SERVICE_H
