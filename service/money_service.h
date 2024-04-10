#ifndef ACCOUNTMANAGEMENT_MONEY_SERVICE_H
#define ACCOUNTMANAGEMENT_MONEY_SERVICE_H

#include "../global.h"
#include "../file/money_file.h"
#include "../enities/linked_list.h"
#include "../model.h"

typedef struct MoneyService {
    //成员变量
    LinkedList money_list;
    MoneyFile money_file;
    //成员函数
    void (*Release)(struct MoneyService* self);
    void (*AddMoney)(struct MoneyService* self,Money* money);
    Money* (*GetMoneyByIndex)(struct MoneyService* self,int index);
    int (*SaveMoneyToFile)(struct MoneyService* self);
}MoneyService;

MoneyService MoneyService_Init();
void MoneyService_InitVariable(MoneyService* self);
void MoneyService_InitFunction(MoneyService* self);
void MoneyService_Release(MoneyService* self);

void MoneyService_AddMoney(MoneyService* self,Money* money);
Money* MoneyService_GetMoneyByIndex(MoneyService* self,int index);
int MoneyService_SaveMoneyToFile(struct MoneyService* self);


#endif //ACCOUNTMANAGEMENT_MONEY_SERVICE_H
