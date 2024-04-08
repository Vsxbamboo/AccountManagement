#ifndef ACCOUNTMANAGEMENT_SERVICE_H
#define ACCOUNTMANAGEMENT_SERVICE_H

#include "../model.h"
#include "card_service.h"
#include "billing_service.h"

typedef struct Service {
    //成员变量
    CardService card_service;
    BillingService billing_service;
    int CARD_VERIFY_ERROR;
    int CARD_CANNOT_LOGON;
    int CARD_CANNOT_LOGOUT;
    //成员函数
    //添加卡
    int (*AddCard)(struct Service *self, Card *card_pointer);

    //查询卡
    Card *(*QueryCard)(struct Service *self, char *aName);

    //模糊查询卡
    LinkedList (*FuzzQueryCard)(struct Service *self, char *aName);

    //展示卡
    void (*ShowCard)(struct Service *self, Card *card_pointer);

    //登录卡
    int (*LogOnCard)(struct Service* self, Card* card_pointer, LogonInfo* login_info);

    //下机
    int (*LogOutCard)(struct Service* self, Card* card_pointer, SettleInfo* settle_info);

    //析构函数
    void (*Release)(struct Service *self);
} Service;

Service Service_Init();

void Service_InitVariable(Service *self);

void Service_InitFunction(Service *self);

Status Service_AddCard(Service *self, Card *cardp);

void Service_ShowCard(Service *self, Card *cardp);

Card *Service_QueryCard(Service *self, char *aName);

LinkedList Service_FuzzQueryCard(Service *self, char *aName);

int Service_LogOnCard(struct Service* self, Card* card_pointer, LogonInfo* login_info);

int Service_LogOutCard(struct Service* self, Card* card_pointer, SettleInfo* settle_info);

void Service_Release(Service *self);


#endif //ACCOUNTMANAGEMENT_SERVICE_H
