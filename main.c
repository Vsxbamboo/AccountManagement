#include "model.h"
#include <malloc.h>
#include <stdio.h>
#include "menu.h"

//global包含对全局变量的声明
#include "global.c"
Card *cards;
int cardlength;

int main() {
    cards=(Card*) malloc(100*sizeof(Card));
    cardlength=0;


    int nSelection=-1;//菜单选项
//
    printf("\n欢迎进入计费管理系统\n");
    do{
        outputMenu();
        scanf("%d",&nSelection);
        switch (nSelection) {
            case 1://添加卡
                add();
                break;
            case 2://查询卡
                query();
                break;
            case 3://上机
                logon();
                break;
            case 4://下机
                settle();
                break;
            case 5://充值
                addMoney();
                break;
            case 6://退费
                refundMoney();
                break;
            case 7://查询统计
                break;
            case 8://注销卡
                break;
            case 0://退出
                exitApp();
                break;
            default:
                printf("输入的菜单编号错误！\n");
                break;
        }
        printf("\n");

    }while(nSelection!=0);
    return 0;
}
