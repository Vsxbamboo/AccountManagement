//
// Created by vsx on 2024/3/6.
//

#include "billing_file.h"
BillingFile BillingFile_Init(char* filepath){
    BillingFile self;
    BillingFile_InitVariable(&self,filepath);
    BillingFile_InitFunction(&self);
    return self;
}
void BillingFile_InitVariable(BillingFile* self,char* filepath){
    self->filepath=filepath;
}
void BillingFile_InitFunction(BillingFile* self){
    self->SaveWithOverwrite=BillingFile_SaveWithOverwrite;
    self->Release=BillingFile_Release;
}

void BillingFile_Release(struct BillingFile* self){

}

int BillingFile_SaveWithOverwrite(struct BillingFile *self, LinkedList billing_list){
    // 文件结构体指针
    FILE *fp = NULL;
    // 以只写的模式打开文件
    if ((fp = fopen(self->filepath, "wb")) == NULL) {
        return -1;
    }
    //写入
    Billing *pBilling;
    for (int i = 0; i < billing_list.count; i++) {
        billing_list.Get(&billing_list, i, (void **) &pBilling);
        fwrite(pBilling, sizeof(Card), 1, fp);
    }
    // 关闭文件
    fclose(fp);
    return 0;
}