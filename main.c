#include "model.h"
#include <malloc.h>
#include <stdio.h>
#include "menu.h"

//global������ȫ�ֱ���������
#include "global.c"
Card *cards;
int cardlength;

int main() {
    cards=(Card*) malloc(100*sizeof(Card));
    cardlength=0;


    int nSelection=-1;//�˵�ѡ��
//
    printf("\n��ӭ����Ʒѹ���ϵͳ\n");
    do{
        outputMenu();
        scanf("%d",&nSelection);
        switch (nSelection) {
            case 1://��ӿ�
                add();
                break;
            case 2://��ѯ��
                query();
                break;
            case 3://�ϻ�
                logon();
                break;
            case 4://�»�
                settle();
                break;
            case 5://��ֵ
                addMoney();
                break;
            case 6://�˷�
                refundMoney();
                break;
            case 7://��ѯͳ��
                break;
            case 8://ע����
                break;
            case 0://�˳�
                exitApp();
                break;
            default:
                printf("����Ĳ˵���Ŵ���\n");
                break;
        }
        printf("\n");

    }while(nSelection!=0);
    return 0;
}
