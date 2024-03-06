#include "cardService.h"
int addCard(Card* cardp){
    //判断空指针
    if(cardp==NULL){
        return NULLPOINTER;
    }
    //判断卡号是否已经存在
    in(cardList,cardp);
    return 0;
}