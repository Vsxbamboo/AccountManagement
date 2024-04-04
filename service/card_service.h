#ifndef ACCOUNTMANAGEMENT_CARD_SERVICE_H
#define ACCOUNTMANAGEMENT_CARD_SERVICE_H

#include <stdio.h>
#include <string.h>
#include "../model.h"
#include "../tool.h"
#include "../file/card_file.h"
#include "../enities/linked_list.h"

//定义报错信息
#define Status int
#define CARD_NULLPOINTER (-1)
#define CARD_ALREADY_EXISTS (-2)

typedef struct CardService{
    //成员变量
    LinkedList card_list;
    CardFile card_file;
    //成员函数
    //添加卡
    int (*Add)(struct CardService* self,Card* card_pointer);
    //查询卡
    Card* (*Query)(struct CardService* self,char* aName);
    //模糊查询卡
    LinkedList (*FuzzQuery)(struct CardService* self,char* aName);
    //展示卡
    void (*Show)(struct CardService* self,Card* card_pointer);
    //判断相同卡号卡是否存在
    int (*Exist)(struct CardService* self,Card* card_pointer);
    //将卡信息链表保存到文件
    int (*SaveCardToFile)(struct CardService* self);
    //获取文件中的卡数量
    int (*GetCardCountFromFile)(struct CardService* self);
    //更新文件中某位置的卡
    void (*UpdateCardInFile)(struct CardService* self,Card *p,int n);
    //判断文件中是否存在某卡号的卡
    int (*CardExistInFile)(struct CardService* self,char *pName);
    //析构函数
    void (*Release)(struct CardService* self);
}CardService;
CardService CardService_Init();
void CardService_InitVariable(CardService* self);
void CardService_InitFunction(CardService* self);
Status CardService_Add(CardService* self,Card* cardp);//返回添加卡是否成功
Card* CardService_Query(CardService* self,char *aName);//精准查询单个卡
LinkedList CardService_FuzzQuery(CardService* self,char *aName);//模糊字串查询
void CardService_Show(CardService* self,Card* cardp);//输出卡的信息
int CardService_Exist(CardService* self,Card* cardp);
void CardService_Release(CardService* self);
//比较两个卡的卡号
int CardService_Compare(void* a,void* b);
int CardService_FuzzCompare(void* a,void *b);

int CardService_SaveCardToFile(CardService* self);
int CardService_GetCardCountFromFile(CardService* self);
void CardService_UpdateCardInFile(CardService* self,Card *p,int n);
int CardService_CardExistInFile(CardService* self,char *pName);

#endif //ACCOUNTMANAGEMENT_CARD_SERVICE_H
