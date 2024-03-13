#include "card_service.h"


Status addCard(Card* cardp){
    //判断空指针
    if(cardp==NULL){
        return CARD_NULLPOINTER;
    }
    //判断卡号是否已经存在
//    in(cardList,cardp);
    cards[cardlength]=(*cardp);
//    showCard(&cards[cardlength]);
    cardlength++;
    return 0;
}

Card* queryCard(char *aName){
    for(int i=0;i<cardlength;i++){
        if(strcmp(cards[i].aName,aName)==0){
            return &cards[i];
        }
    }
    return NULL;
}

void showCard(Card *cardp){
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

Status saveCardToFile(){
    for(int i=0;i<cardlength;i++){
        saveCard(&cards[i],CARDPATH);
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