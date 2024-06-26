#include "card_service.h"

CardService CardService_Init() {
    CardService self;
    CardService_InitVariable(&self);
    CardService_InitFunction(&self);
    return self;
}

void CardService_InitVariable(CardService *self) {
    self->card_list = LinkedList_Init();
    self->card_file = CardFile_Init(CARD_PATH);
    self->card_file.ReadFileToLinkedList(&self->card_file,&self->card_list);
}

void CardService_InitFunction(CardService *self) {
    self->Add = CardService_Add;
    self->Query = CardService_Query;
    self->FuzzQuery = CardService_FuzzQuery;
    self->Show = CardService_Show;
    self->Exist = CardService_Exist;
    self->SaveCardToFile = CardService_SaveCardToFile;
    self->GetCardCountFromFile = CardService_GetCardCountFromFile;
    self->UpdateCardInFile = CardService_UpdateCardInFile;
    self->CardExistInFile = CardService_CardExistInFile;
    self->VerifyCardPwd=CardService_VerifyCardPwd;
    self->CanLogOn=CardService_CanLogOn;
    self->LogOnCard=CardService_LogOnCard;
    self->CanLogOut=CardService_CanLogOut;
    self->LogOutCard=CardService_LogOutCard;
    self->CanFund=CardService_CanFund;
    self->CanReFund=CardService_CanReFund;
    self->AdjustBalance=CardService_AdjustBalance;
    self->CanCancel=CardService_CanCancel;
    self->CancelCard=CardService_CancelCard;
    self->Release = CardService_Release;
}

Status CardService_Add(CardService *self, Card *cardp) {
    //判断空指针
    if (cardp == NULL) {
        return CARD_NULLPOINTER;
    }
    //判断卡号是否已经存在
    if (self->Exist(self, cardp) != 0) {
        return CARD_ALREADY_EXISTS;
    }
    //存入链表的操作
    //最好重新分配空间
    Card *new_card_pointer = (Card *) malloc(sizeof(Card));
    *new_card_pointer = *cardp;
    self->card_list.Add(&self->card_list, new_card_pointer);
    return 0;
}

Card *CardService_Query(CardService *self, char *aName) {
    Card *cp = (Card *) malloc(sizeof(Card));
    strcpy(cp->aName, aName);
    self->card_list.Compare = CardService_Compare;
    int index = self->card_list.Find(&self->card_list, cp);
    free(cp);
    cp=NULL;
    if (index != -1) {
        self->card_list.Get(&self->card_list, index, (void **) &cp);
        return cp;
    }

    return NULL;
}

LinkedList CardService_FuzzQuery(CardService *self, char *aName) {
    Card *cp = (Card *) malloc(sizeof(Card));
    strcpy(cp->aName, aName);
    self->card_list.Compare = CardService_FuzzCompare;
    LinkedList result_list = self->card_list.FindAll(&self->card_list, cp);
    return result_list;
}

void CardService_Show(CardService *self, Card *cardp) {
    if (cardp == NULL)
        return;
    printf("卡号:%s\n", cardp->aName);
    printf("状态:%d\n", cardp->nStatus);
    printf("余额:%.2f\n", cardp->fBalance);
    printf("累计使用:%.2f\n", cardp->fTotalUse);
    printf("使用次数:%d\n", cardp->nUseCount);
    char pBuf[20] = {0};
    timeToString(cardp->tLast, pBuf);
    printf("上次使用时间:%s\n", pBuf);
}

int CardService_Exist(CardService *self, Card *cardp) {
    if (cardp == NULL)
        return 0;
    self->card_list.Compare = CardService_Compare;
    if (self->card_list.Find(&self->card_list, cardp) != -1) {
        return CARD_ALREADY_EXISTS;
    }
    return 0;
}

int CardService_VerifyCardPwd(CardService *self,Card* card_pointer){
    //判断传入的卡是否不为空，且卡号存在
    if(card_pointer==NULL || self->Exist(self,card_pointer)!=CARD_ALREADY_EXISTS){
        return 0;
    }
    //获取对应卡
    Card* corr_card_in_list=self->Query(self,card_pointer->aName);
    //比较密码
    if(strcmp(card_pointer->aPwd,corr_card_in_list->aPwd)==0){
        //匹配后返回完整卡信息
        *card_pointer=*corr_card_in_list;
        return 1;
    }
    return 0;
}

int CardService_CanLogOn(CardService* self, Card* card_pointer){
    if(card_pointer==NULL)
        return 0;
    if(card_pointer->nStatus==0 //未上机
    && card_pointer->tEnd>time(NULL) //未到截止时间
    && card_pointer->fBalance>0 //尚且有余额
    && card_pointer->nDel==0 //未被删除
    ){
        return 1;
    }else{
        return 0;
    }
}

int CardService_LogOnCard(CardService* self, char* aName){
    Card* cp=self->Query(self,aName);
    if(cp==NULL){
        return -1;
    }else{
        cp->nStatus=1;
        cp->tLast=time(NULL);
        cp->nUseCount+=1;
    }
    return 0;
}

int CardService_CanLogOut(CardService* self, Card* card_pointer){
    if(card_pointer==NULL)
        return 0;
    if(card_pointer->nStatus==1 //未上机
       && card_pointer->nDel==0 //未被删除
            ){
        return 1;
    }else{
        return 0;
    }
}

int CardService_LogOutCard(CardService* self, char* aName,Billing* billing_pointer){
    Card* cp=self->Query(self,aName);
    if(cp==NULL){
        return -1;
    }else{
        cp->nStatus=0;//状态下机
        cp->tLast=billing_pointer->tEnd;//更新最后使用时间
        cp->fTotalUse+=billing_pointer->fAmount;//增加总共使用费用
        cp->fBalance-=billing_pointer->fAmount;//减少余额
    }
    return 0;
}

int CardService_CanFund(CardService* self, Card* card_pointer){
    if(card_pointer==NULL){
        return 0;
    }
    if((card_pointer->nStatus==1 || card_pointer->nStatus==0) //未上机或上机中
    && card_pointer->nDel==0 //未被删除
    && card_pointer->tEnd>time(NULL) //未到截止时间
        ){
        return 1;
    }else{
        return 0;
    }
}

int CardService_CanReFund(struct CardService* self, Card* card_pointer){
    if(card_pointer==NULL){
        return 0;
    }
    if(card_pointer->nStatus==0 //未上机
       && card_pointer->nDel==0 //未被删除
            ){
        return 1;
    }else{
        return 0;
    }
}

int CardService_AdjustBalance(CardService* self, Card* card_pointer, Money* money_pointer){
    if(card_pointer==NULL || money_pointer==NULL || strcmp(card_pointer->aName,money_pointer->aCardName)!=0){
        return -1;
    }
    if(self->VerifyCardPwd(self,card_pointer)){
        Card* cp=self->Query(self,card_pointer->aName);
        if(money_pointer->nStatus==0){
            if(cp->fBalance+money_pointer->fMoney>=0){
                cp->fBalance+=money_pointer->fMoney;
                *card_pointer=*cp;
            }else{
                return -1;
            }
        }else if(money_pointer->nStatus==1) {
            if(cp->fBalance-money_pointer->fMoney>=0){
                cp->fBalance-=money_pointer->fMoney;
                *card_pointer=*cp;
            }else{
                return -1;
            }
        }else{
            return -1;
        }
        return 0;
    }
    return -1;
}

int CardService_CanCancel(CardService* self, Card* card_pointer){
    if(card_pointer==NULL){
        return 0;
    }
    if(card_pointer->nStatus==0 //未上机
    && card_pointer->nDel==0 //未被删除
    && card_pointer->fBalance>=0 //还有或没有余额
            ){
        return 1;
    }else{
        return 0;
    }
}

int CardService_CancelCard(CardService* self, char* aName){
    Card* cp=self->Query(self,aName);
    if(cp==NULL) {
        return -1;
    }
    cp->nStatus=2;
    cp->fBalance=0;
    return 0;
}

void CardService_Release(CardService *self) {
    //保存链表
    self->SaveCardToFile(self);
    //析构成员
    self->card_list.Release(&self->card_list);
    self->card_file.Release(&self->card_file);
}

int CardService_Compare(void *a, void *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    Card *ap = (Card *) a;
    Card *bp = (Card *) b;
    if (strcmp(ap->aName, bp->aName) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int CardService_FuzzCompare(void *a, void *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    Card *ap = (Card *) a;
    Card *bp = (Card *) b;
    if (fuzz_str_beinclude(ap->aName, bp->aName) == 1) {
        return 1;
    } else {
        return 0;
    }
}

int CardService_SaveCardToFile(CardService *self) {
    return self->card_file.SaveWithOverwrite(&self->card_file, self->card_list);
}

int CardService_GetCardCountFromFile(CardService *self) {
    return self->card_file.GetCardCout(&self->card_file);
}

void CardService_UpdateCardInFile(CardService *self, Card *p, int n) {
    self->card_file.UpdateCard(&self->card_file, n, p);
}

int CardService_CardExistInFile(CardService *self, char *pName) {
    return self->card_file.Exist(&self->card_file, pName);
}
