#include <stdio.h>
#include "menu.h"
#include "LinkedList.h"
int main() {
    //�ڴ˳�ʼ���������ݽṹ
    LinkedList cardList=NULL;

    int nSelection=-1;//�˵�ѡ��
    printf("\n��ӭ����Ʒѹ���ϵͳ\n");
    do{
        outputMenu();
        nSelection=-1;
        scanf("%d",&nSelection);
        switch (nSelection) {
//            case 1://��ӿ�
//                add();
//                break;
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
