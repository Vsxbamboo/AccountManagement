#ifndef ACCOUNTMANAGEMENT_CARD_SERVICE_H
#define ACCOUNTMANAGEMENT_CARD_SERVICE_H

#include <stdio.h>
#include <string.h>
#include "../global.c"
#include "../model.h"
#include "../tool.h"
#include "../file/card_file.h"

//定义报错信息
#define Status int
#define CARD_NULLPOINTER (-1)
#define CARD_ALREADY_EXISTS (-2)

Status card_add(Card* cardp);//返回添加卡是否成功
Card* card_query(char *aName);//精准查询单个卡
CardList card_fuzz_query(char *aName);//模糊字串查询
void card_show(Card* cardp);//输出卡的信息
int card_exist(Card* cardp);
void card_clear();

Status saveCardToFile();
int getCardCountFromFile();
void updateCardInFile(Card *p,int n);
int CardisExist(char *pName);

#endif //ACCOUNTMANAGEMENT_CARD_SERVICE_H
