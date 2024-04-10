#ifndef ACCOUNTMANAGEMENT_CARD_SERVICE_H
#define ACCOUNTMANAGEMENT_CARD_SERVICE_H

#include <stdio.h>
#include <string.h>
#include "../model.h"
#include "../global.h"
#include "../tool.h"
#include "../file/card_file.h"
#include "../enities/linked_list.h"

//定义报错信息
#define Status int
#define CARD_NULLPOINTER (-1)
#define CARD_ALREADY_EXISTS (-2)

typedef struct CardService {
    //成员变量
    LinkedList card_list;
    CardFile card_file;

    //成员函数
    //添加卡
    int (*Add)(struct CardService *self, Card *card_pointer);

    //查询卡
    Card* (*Query)(struct CardService *self, char *aName);

    //模糊查询卡
    LinkedList (*FuzzQuery)(struct CardService *self, char *aName);

    //展示卡
    void (*Show)(struct CardService *self, Card *card_pointer);

    //判断相同卡号卡是否存在
    int (*Exist)(struct CardService *self, Card *card_pointer);

    //将卡信息链表保存到文件
    int (*SaveCardToFile)(struct CardService *self);

    //获取文件中的卡数量
    int (*GetCardCountFromFile)(struct CardService *self);

    //更新文件中某位置的卡
    void (*UpdateCardInFile)(struct CardService *self, Card *p, int n);

    //判断文件中是否存在某卡号的卡
    int (*CardExistInFile)(struct CardService *self, char *aName);

    //验证卡号与密码是否匹配，并返回卡的其他信息
    int (*VerifyCardPwd)(struct CardService* self,Card* card_pointer);

    //验证是否符合上机状态
    int (*CanLogOn)(struct CardService* self, Card* card_pointer);

    //上机
    int (*LogOnCard)(struct CardService* self, char* aName);

    //验证是否符合下机状态
    int (*CanLogOut)(struct CardService* self, Card* card_pointer);

    //下机
    int (*LogOutCard)(struct CardService* self, char* aName,Billing* billing_pointer);

    //判断是否符合充值
    int (*CanFund)(struct CardService* self, Card* card_pointer);

    //判断是否符合退费条件
    int (*CanReFund)(struct CardService* self, Card* card_pointer);

    //调整余额
    int (*AdjustBalance)(struct CardService* self, Card* card_pointer, Money* money_pointer);

    //判断是否符合注销条件
    int (*CanCancel)(struct CardService* self, Card* card_pointer);

    //注销卡
    int (*CancelCard)(struct CardService* self, char* aName);

    //析构函数
    void (*Release)(struct CardService *self);
} CardService;

CardService CardService_Init();

void CardService_InitVariable(CardService *self);

void CardService_InitFunction(CardService *self);

Status CardService_Add(CardService *self, Card *cardp);
Card *CardService_Query(CardService *self, char *aName);
LinkedList CardService_FuzzQuery(CardService *self, char *aName);
void CardService_Show(CardService *self, Card *cardp);
int CardService_Exist(CardService *self, Card *cardp);
int CardService_VerifyCardPwd(CardService *self,Card* card_pointer);
int CardService_CanLogOn(CardService* self, Card* card_pointer);
int CardService_LogOnCard(CardService* self, char* aName);
int CardService_CanLogOut(CardService* self, Card* card_pointer);
int CardService_LogOutCard(CardService* self, char* aName,Billing* billing_pointer);
int CardService_CanFund(CardService* self, Card* card_pointer);
int CardService_CanReFund(CardService* self, Card* card_pointer);
int CardService_AdjustBalance(CardService* self, Card* card_pointer, Money* money_pointer);
int CardService_CanCancel(CardService* self, Card* card_pointer);
int CardService_CancelCard(CardService* self, char* aName);
void CardService_Release(CardService *self);

int CardService_SaveCardToFile(CardService *self);

int CardService_GetCardCountFromFile(CardService *self);

void CardService_UpdateCardInFile(CardService *self, Card *p, int n);

int CardService_CardExistInFile(CardService *self, char *pName);

//比较两个卡的卡号 static
int CardService_Compare(void *a, void *b);

int CardService_FuzzCompare(void *a, void *b);

#endif //ACCOUNTMANAGEMENT_CARD_SERVICE_H
