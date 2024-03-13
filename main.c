#include "model.h"
#include <malloc.h>
#include <stdio.h>
#include "menu.h"

//global������ȫ�ֱ���������
#include "global.c"
Card *cards=NULL;
int cardlength;

Status init();

int main() {

    if(init()!=0){
        printf("�����ʼ�����󣬼����˳�...\n");
        return 0;
    }

    int nSelection=-1;//�˵�ѡ��

    printf("\n��ӭ����Ʒѹ���ϵͳ\n");
    do{
        menu_outputMenu();
        /*
         * ��ȡһ��������ǻ��з���������ȡ
         * */
        char selectbuf;

        scanf("%d",&nSelection);
        switch (nSelection) {
            case 1://��ӿ�
                menu_add();
                break;
            case 2://��ѯ��
                menu_query();
                break;
            case 3://�ϻ�
                menu_logon();
                break;
            case 4://�»�
                menu_settle();
                break;
            case 5://��ֵ
                menu_addMoney();
                break;
            case 6://�˷�
                menu_refundMoney();
                break;
            case 7://��ѯͳ��
                break;
            case 8://ע����
                break;
            case 9://��ʱ���ļ������˵�
                menu_cardfile();
                break;
            case 0://�˳�
                menu_exitApp();
                break;
            default:
                printf("����Ĳ˵���Ŵ���\n");
                break;
        }
        printf("\n");

    }while(nSelection!=0);
    return 0;
}

Status init(){
    cards=(Card*) malloc(100*sizeof(Card));
    if(cards==NULL)
        return -1;
    cardlength=0;
    return 0;
}