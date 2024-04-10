#include "billing_service.h"
BillingService BillingService_Init(){
    BillingService self;
    BillingService_InitVariable(&self);
    BillingService_InitFunction(&self);
    return self;
}
void BillingService_InitVariable(BillingService* self){
    self->billing_list=LinkedList_Init();
    self->billing_file= BillingFile_Init(BILLING_PATH);
}
void BillingService_InitFunction(BillingService* self){
    self->Add=BillingService_Add;
    self->AddBilling=BillingService_AddBilling;
    self->SettleBilling=BillingService_SettleBilling;
    self->SaveBillingToFile=BillingService_SaveBillingToFile;
    self->QueryLast=BillingService_QueryLast;
    self->QueryAllByName=BillingService_QueryAllByName;
    self->QueryAllByTime=BillingService_QueryAllByTime;
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

int BillingService_AddBilling(BillingService* self,Card* card_pointer){
    //添加消费信息
    Billing billing;
    strcpy(billing.aCardName,card_pointer->aName);
    billing.tStart=card_pointer->tLast;
    billing.tEnd=billing.tStart;
    billing.fAmount=0;
    billing.nStatus=0;
    billing.nDel=0;
    self->Add(self,&billing);
    return 0;
}

Billing*  BillingService_SettleBilling(BillingService* self,Card* card_pointer){
    Billing* latest_billing=self->QueryLast(self,card_pointer);
    if(latest_billing->nStatus==0 && latest_billing->nDel==0){
        latest_billing->tEnd=time(NULL);
        latest_billing->fAmount=(float)(( (latest_billing->tEnd-latest_billing->tStart)/((int)(UNIT*60))+1 )*CHARGE);
        if(latest_billing->fAmount<=card_pointer->fBalance){
            latest_billing->nStatus=1;
            return latest_billing;
        }
    }
    return NULL;
}

Billing* BillingService_QueryLast(struct BillingService* self,Card* card_pointer){
    Billing *bp=(Billing*) malloc(sizeof(Billing));
    strcpy(bp->aCardName,card_pointer->aName);
    bp->tStart=card_pointer->tLast;
    self->billing_list.Compare=BillingService_CompareLast;
    int index=self->billing_list.Find(&self->billing_list,bp);
    free(bp);
    bp=NULL;
    if(index!=-1){
        self->billing_list.Get(&self->billing_list,index,(void**)&bp);
        return bp;
    }
    return NULL;
}

LinkedList BillingService_QueryAllByName(BillingService* self, char* aName,time_t start_time,time_t end_time){
    LinkedList result=LinkedList_Init();
    Billing* billing_ptr=(Billing*) malloc(sizeof(Billing));
    strcpy(billing_ptr->aCardName,aName);
    billing_ptr->tStart=start_time;
    billing_ptr->tEnd=end_time;
    self->billing_list.Compare=BillingService_CompareNameAndTime;
    LinkedList result_list = self->billing_list.FindAll(&self->billing_list, billing_ptr);
    free(billing_ptr);
    return result_list;
}

LinkedList BillingService_QueryAllByTime(struct BillingService* self,time_t start_time,time_t end_time){
    LinkedList result=LinkedList_Init();
    Billing* billing_ptr=(Billing*) malloc(sizeof(Billing));
    billing_ptr->tStart=start_time;
    billing_ptr->tEnd=end_time;
    self->billing_list.Compare=BillingService_CompareTimeInclude;
    LinkedList result_list = self->billing_list.FindAll(&self->billing_list, billing_ptr);
    free(billing_ptr);
    return result_list;
}

int BillingService_SaveBillingToFile(struct BillingService* self){
    return self->billing_file.SaveWithOverwrite(&self->billing_file,self->billing_list);
}

int BillingService_CompareNameAndTime(void* a,void* b){
    if(a==NULL || b==NULL){
        return 0;
    }
    Billing* b_a=(Billing*)a;
    Billing* b_b=(Billing*)b;
    if(strcmp(b_a->aCardName,b_b->aCardName)==0 && b_a->tStart<=b_b->tStart && b_a->tEnd>=b_b->tEnd){
        return 1;
    }else{
        return 0;
    }
}

int BillingService_CompareTimeInclude(void* a,void* b){
    if(a==NULL || b==NULL){
        return 0;
    }
    Billing* b_a=(Billing*)a;
    Billing* b_b=(Billing*)b;
    if(b_a->tStart<=b_b->tStart && b_a->tEnd>=b_b->tEnd){
        return 1;
    }else{
        return 0;
    }
}

int BillingService_CompareLast(void* a,void* b){
    if(a==NULL || b==NULL){
        return 0;
    }
    Billing* b_a=(Billing*)a;
    Billing* b_b=(Billing*)b;
    if(strcmp(b_a->aCardName,b_b->aCardName)==0 && b_a->tStart==b_b->tStart){
        return 1;
    }else{
        return 0;
    }
}