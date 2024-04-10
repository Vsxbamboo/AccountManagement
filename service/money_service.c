#include "money_service.h"

MoneyService MoneyService_Init(){
    MoneyService self;
    MoneyService_InitVariable(&self);
    MoneyService_InitFunction(&self);
    return self;
}
void MoneyService_InitVariable(MoneyService* self){
    self->money_list= LinkedList_Init();
    self->money_file= MoneyFile_Init(MONEY_PATH);
    self->money_file.ReadFileToLinkedList(&self->money_file,&self->money_list);
}
void MoneyService_InitFunction(MoneyService* self){
    self->AddMoney= MoneyService_AddMoney;
    self->GetMoneyByIndex= MoneyService_GetMoneyByIndex;
    self->SaveMoneyToFile= MoneyService_SaveMoneyToFile;
    self->Release= MoneyService_Release;
}
void MoneyService_Release(MoneyService* self){
    //保存文件
    self->SaveMoneyToFile(self);
    //析构成员对象
    self->money_file.Release(&self->money_file);
    self->money_list.Release(&self->money_list);
}

void MoneyService_AddMoney(MoneyService* self,Money* money){
    //先专门开辟空间，复制money
    Money* new_money= malloc(sizeof(Money));
    *new_money=*money;
    //再插入链表
    self->money_list.Add(&self->money_list,new_money);
}
Money* MoneyService_GetMoneyByIndex(MoneyService* self,int index){
    Money* money;
    int rcode=self->money_list.Get(&self->money_list, index, (void **) &money);
    if(rcode==0){
        return money;
    }else{
        return NULL;
    }
}
int MoneyService_SaveMoneyToFile(struct MoneyService* self){
    return self->money_file.SaveWithOverwrite(&self->money_file, self->money_list);
}