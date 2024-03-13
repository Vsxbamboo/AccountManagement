//
// Created by vsx on 2024/3/6.
//

#ifndef ACCOUNTMANAGEMENT_CARD_FILE_H
#define ACCOUNTMANAGEMENT_CARD_FILE_H

#include <stdio.h>    // 包含文件结构体头文件
#include <string.h>   // 包含字符处理头文件
#include <stdlib.h>   // 包含standard library标准库头文件
#include <time.h>

#define FALSE 0
#define TRUE  1
#define CARDPATH "C:\\E\\c\\AccountManagement\\card.ams"     // 卡信息保存路径

#include "../model.h"
#include "../global.c"

int saveCard(const Card *pCard, const char *pPath);

int readCard();

int updateCard(const Card *pCard, const char *pPath, int nIndex);

int getCardCount(const char *pPath);

int isExsit(const char *pNum, const char *pPath);

#endif //ACCOUNTMANAGEMENT_CARD_FILE_H
