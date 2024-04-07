#include "billing_service.h"
BillingService BillingService_Init(){
    BillingService self;
    BillingService_InitVariable(&self);
    BillingService_InitFunction(&self);
    return self;
}
void BillingService_InitVariable(BillingService* self){
    self->billing_list=LinkedList_Init();
    self->billing_file= BillingFile_Init("C:\\E\\c\\AccountManagement\\billing.ams");
}
void BillingService_InitFunction(BillingService* self){
    self->Add=BillingService_Add;
    self->SaveBillingToFile=BillingService_SaveBillingToFile;
    self->Release=BillingService_Release;
}

void BillingService_Release(BillingService* self){
    //保存链表到文件
    self->SaveBillingToFile(self);
    //析构成员变量
    self->billing_list.Release(&self->billing_list);
    self->billing_file.Release(&self->billing_file);
}

int BillingService_Add(BillingService* self,Billing* billing_pointer){
    if(billing_pointer==NULL)
        return -1;
    Billing* billing_ptr=(Billing*) malloc(sizeof(Billing));
    *billing_ptr=*billing_pointer;
    self->billing_list.Add(&self->billing_list,billing_ptr);
    return 0;
}

int BillingService_SaveBillingToFile(struct BillingService* self){
    return self->billing_file.SaveWithOverwrite(&self->billing_file,self->billing_list);
}