#ifndef ACCOUNTMANAGEMENT_SERVICE_H
#define ACCOUNTMANAGEMENT_SERVICE_H

#include "../model.h"
#include "card_service.h"

typedef struct Service{
    //成员变量
    CardService card_service;
    //成员函数
    //添加卡
    int (*AddCard)(struct Service* self,Card* card_pointer);
    //查询卡
    Card* (*QueryCard)(struct Service* self,char* aName);
    //模糊查询卡
    LinkedList (*FuzzQueryCard)(struct Service* self,char* aName);
    //展示卡
    void (*ShowCard)(struct Service* self,Card* card_pointer);
    //析构函数
    void (*Release)(struct Service* self);
}Service;
Service Service_Init();
void Service_InitVariable(Service* self);
void Service_InitFunction(Service* self);
Status Service_AddCard(Service* self,Card* cardp);
void Service_ShowCard(Service* self,Card* cardp);
Card* Service_QueryCard(Service* self,char* aName);
LinkedList Service_FuzzQueryCard(Service* self,char* aName);
void Service_Release(Service* self);

Status service_saveCard();
Status service_readCard();
int service_getCount();
Status service_updateCard(Card *p,int n);
int service_ifinFile(char *pName);

#endif //ACCOUNTMANAGEMENT_SERVICE_H
