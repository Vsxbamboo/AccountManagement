#ifndef ACCOUNTMANAGEMENT_CARDSERVICE_H
#define ACCOUNTMANAGEMENT_CARDSERVICE_H

#include <stdio.h>
#include <string.h>
#include "../global.c"
#include "../model.h"
#include "../tool.h"

//定义报错信息
#define Status int
#define CARD_NULLPOINTER (-1)
#define CARD_ALREADY_EXISTS (-2)

Status addCard(Card* cardp);//返回添加卡是否成功
int findCard(char *aName);
void showCard(Card* cardp);//输出卡的信息

#endif //ACCOUNTMANAGEMENT_CARDSERVICE_H
