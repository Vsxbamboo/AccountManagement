#include "cardService.h"



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

int findCard(char *aName){
    for(int i=0;i<cardlength;i++){
        if(strcmp(cards[i].aName,aName)==0){
            return i;
        }
    }
}

void showCard(Card *cardp){
    printf("����:%s\n",cardp->aName);
    printf("״̬:%d\n",cardp->nStatus);
    printf("���:%.2f\n",cardp->fBalance);
    printf("�ۼ�ʹ��:%.2f\n",cardp->fTotalUse);
    printf("ʹ�ô���:%d\n",cardp->nUseCount);
    char pBuf[20]={0};
    timeToString(cardp->tLast,pBuf);
    printf("�ϴ�ʹ��ʱ��:%s\n",pBuf);
}
