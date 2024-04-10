#ifndef ACCOUNTMANAGEMENT_MONEY_FILE_H
#define ACCOUNTMANAGEMENT_MONEY_FILE_H

#include <stdio.h>
#include "../enities/linked_list.h"

typedef struct MoneyFile {
    //成员变量
    char* filepath;
    //成员函数
    //用链表中的卡覆写文件
    int (*SaveWithOverwrite)(struct MoneyFile *self, LinkedList money_list);

    //将文件中的卡读到链表中去
    int (*ReadFileToLinkedList)(struct MoneyFile *self, LinkedList *target_list_pointer);

    //析构函数
    void (*Release)(struct MoneyFile* self);
}MoneyFile;

MoneyFile MoneyFile_Init(char* filepath);
void MoneyFile_InitVariable(MoneyFile* self,char* filepath);
void MoneyFile_InitFunction(MoneyFile* self);
void MoneyFile_Release(MoneyFile* self);

int MoneyFile_SaveWithOverwrite(struct MoneyFile *self, LinkedList money_list);

int MoneyFile_ReadFileToLinkedList(struct MoneyFile *self, LinkedList *target_list_pointer);

#endif //ACCOUNTMANAGEMENT_MONEY_FILE_H
