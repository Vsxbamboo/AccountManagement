#ifndef ACCOUNTMANAGEMENT_CARD_FILE_H
#define ACCOUNTMANAGEMENT_CARD_FILE_H

#include <stdio.h>    // 包含文件结构体头文件
#include <string.h>   // 包含字符处理头文件
#include <stdlib.h>   // 包含standard library标准库头文件
#include "../model.h"
#include "../enities/linked_list.h"

typedef struct CardFile {
    //成员变量
    char *filepath;

    //成员函数
    //用链表中的卡覆写文件
    int (*SaveWithOverwrite)(struct CardFile *self, LinkedList card_list);

    //向文件追加卡
    int (*AppendCard)(struct CardFile *self, Card *pCard);

    //将文件中的卡读到链表中去
    int (*ReadFileToLinkedList)(struct CardFile *self, LinkedList *target_list_pointer);

    //更新文件指定位置的卡
    int (*UpdateCard)(struct CardFile *self, int index, Card *pCard);

    //获取文件中的卡数量
    int (*GetCardCout)(struct CardFile *self);

    //判断卡在文件中是否存在
    int (*Exist)(struct CardFile *self, char *pNum);

    //析构函数
    void (*Release)(struct CardFile *self);
} CardFile;

CardFile CardFile_Init(char *filepath);

void CardFile_InitVariable(CardFile *self, char *filepath);

void CardFile_InitFunction(CardFile *self);

int CardFile_SaveWithOverwrite(struct CardFile *self, LinkedList card_list);

int CardFile_AppendCard(CardFile *self, Card *pCard);

int CardFile_ReadFileToLinkedList(CardFile *self, LinkedList *target_list_pointer);

int CardFile_UpdateCard(CardFile *self, int index, Card *pCard);

int CardFile_GetCardCout(CardFile *self);

int CardFile_Exist(CardFile *self, char *pNum);

void CardFile_Release(CardFile *self);

#endif //ACCOUNTMANAGEMENT_CARD_FILE_H
