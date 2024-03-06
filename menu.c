#include "menu.h"
#include <stdio.h>
#include "cardService.h"
Card A;
void outputMenu(){
    printf("----------菜单----------\n");
    printf("1.添加卡\n2.查询卡\n3.上机\n4.下机\n5.充值\n6.退费\n7.查询统计\n8.注销卡\n0.退出\n");
    printf("请选择菜单项编号(0~8):");
}
void add(){
    printf("----------添加卡----------");
    printf("请输入卡号(长度为18):");
    char cardnumber[19]={0};
    for(int i=0;i<18;i++){
        scanf("%c",&cardnumber[i]);
        if(cardnumber[i]=='\n')
            break;
    }
    printf("请输入密码:");
    char password[21]={0};
    for(int i=0;i<20;i++){
        scanf("%c",&password[i]);
        if(password[i]=='\n')
            break;
    }
    printf("请输入开卡金额(RMB):");
    int startmoney=0;
    scanf("%d",&startmoney);
    printf("添加卡信息成功！");
}
void query(){}
void exitApp(){}
void logon(){}
void settle(){}
void annul(){}
void addMoney(){}
void refundMoney(){}