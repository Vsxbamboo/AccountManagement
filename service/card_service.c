#include "card_service.h"


Status addCard(Card* cardp){
    //�жϿ�ָ��
    if(cardp==NULL){
        return CARD_NULLPOINTER;
    }
    //�жϿ����Ƿ��Ѿ�����
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
    printf("����:%s\n",cardp->aName);
    printf("״̬:%d\n",cardp->nStatus);
    printf("���:%.2f\n",cardp->fBalance);
    printf("�ۼ�ʹ��:%.2f\n",cardp->fTotalUse);
    printf("ʹ�ô���:%d\n",cardp->nUseCount);
    char pBuf[20]={0};
    timeToString(cardp->tLast,pBuf);
    printf("�ϴ�ʹ��ʱ��:%s\n",pBuf);
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