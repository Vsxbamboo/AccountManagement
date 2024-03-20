#include "card_service.h"


Status card_add(Card* cardp){
    //判断空指针
    if(cardp==NULL){
        return CARD_NULLPOINTER;
    }
    //判断卡号是否已经存在
    if(card_exist(cardp)==1){
        return CARD_ALREADY_EXISTS;
    }
    CardList temp_pointer=cardList;
    while(temp_pointer->next!=NULL){
        temp_pointer=temp_pointer->next;
    }
    temp_pointer->next=(CardList)malloc(sizeof(CardNode));
    temp_pointer=temp_pointer->next;
    temp_pointer->data=*cardp;
    temp_pointer->next=NULL;
    cardlength++;
    return 0;
}

Card* card_query(char *aName){
    CardList temp_pointer=cardList->next;
    while(temp_pointer!=NULL){
        if(strcmp(aName,temp_pointer->data.aName)==0){
            return &temp_pointer->data;
        }
        temp_pointer=temp_pointer->next;
    }
    return NULL;
}

CardList card_fuzz_query(char *aName){
    //初始化返回链表的表头指针和表尾指针
    CardList resultList=(CardList)malloc(sizeof(CardNode));
    resultList->next=NULL;
    CardList resultTail=resultList;

    CardList temp_pointer=cardList->next;
    while(temp_pointer!=NULL){
        if(fuzz_str_beinclude(aName,temp_pointer->data.aName)==1){
            resultTail->next=(CardList)malloc(sizeof(CardNode));
            resultTail->next->data=temp_pointer->data;
            resultTail->next->next=NULL;
            resultTail=resultTail->next;
        }
        temp_pointer=temp_pointer->next;
    }
    return resultList;
}

void card_show(Card *cardp){
    if(cardp==NULL)
        return;
    printf("卡号:%s\n",cardp->aName);
    printf("状态:%d\n",cardp->nStatus);
    printf("余额:%.2f\n",cardp->fBalance);
    printf("累计使用:%.2f\n",cardp->fTotalUse);
    printf("使用次数:%d\n",cardp->nUseCount);
    char pBuf[20]={0};
    timeToString(cardp->tLast,pBuf);
    printf("上次使用时间:%s\n",pBuf);
}

int card_exist(Card* cardp){
    if(cardp==NULL)
        return 0;
    CardList temp_pointer=cardList->next;
    while(temp_pointer!=NULL){
        if(strcmp(temp_pointer->data.aName,cardp->aName)==0)
            return CARD_ALREADY_EXISTS;
        temp_pointer=temp_pointer->next;
    }
    return 0;
}

void card_clear(){
    CardList clear_pointer;
    while(cardList->next!=NULL){
        clear_pointer=cardList;
        cardList=cardList->next;
        free(clear_pointer);
    }
}

Status saveCardToFile(){

    CardList temp_pointer=cardList->next;
    while(temp_pointer!=NULL){
        saveCard(&temp_pointer->data,CARDPATH);
        temp_pointer=temp_pointer->next;
    }
    return 0;
}

int getCardCountFromFile(){
    return getCardCount(CARDPATH);
}

void updateCardInFile(Card *p,int n){
    updateCard(p,CARDPATH,n);
}
int CardisExist(char *pName){
    return isExsit(pName,CARDPATH);
}