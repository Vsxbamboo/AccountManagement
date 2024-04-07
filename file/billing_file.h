#ifndef ACCOUNTMANAGEMENT_BILLING_FILE_H
#define ACCOUNTMANAGEMENT_BILLING_FILE_H

#include "../enities/linked_list.h"
#include <stdio.h>
#include "../model.h"

typedef struct BillingFile{
    //成员变量
    char* filepath;
    //成员函数
    int (*SaveWithOverwrite)(struct BillingFile *self, LinkedList billing_list);
    void (*Release)(struct BillingFile* self);
}BillingFile;

BillingFile BillingFile_Init(char* filepath);
void BillingFile_InitVariable(BillingFile* self,char* filepath);
void BillingFile_InitFunction(BillingFile* self);
void BillingFile_Release(struct BillingFile* self);
int BillingFile_SaveWithOverwrite(struct BillingFile *self, LinkedList billing_list);
#endif //ACCOUNTMANAGEMENT_BILLING_FILE_H
