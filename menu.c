#include "menu.h"
#include <stdio.h>
#include "cardService.h"
Card A;
void outputMenu(){
    printf("----------�˵�----------\n");
    printf("1.���ӿ�\n2.��ѯ��\n3.�ϻ�\n4.�»�\n5.��ֵ\n6.�˷�\n7.��ѯͳ��\n8.ע����\n0.�˳�\n");
    printf("��ѡ��˵�����(0~8):");
}
void add(){
    printf("----------���ӿ�----------");
    printf("�����뿨��(����Ϊ18):");
    char cardnumber[19]={0};
    for(int i=0;i<18;i++){
        scanf("%c",&cardnumber[i]);
        if(cardnumber[i]=='\n')
            break;
    }
    printf("����������:");
    char password[21]={0};
    for(int i=0;i<20;i++){
        scanf("%c",&password[i]);
        if(password[i]=='\n')
            break;
    }
    printf("�����뿪�����(RMB):");
    int startmoney=0;
    scanf("%d",&startmoney);
    printf("���ӿ���Ϣ�ɹ���");
}
void query(){}
void exitApp(){}
void logon(){}
void settle(){}
void annul(){}
void addMoney(){}
void refundMoney(){}