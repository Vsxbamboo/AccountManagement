#include "model.h"
#include <malloc.h>
#include <stdio.h>
#include "menu.h"

//全局变量声明
int cardlength;
CardList cardList;
LinkedList list;
//初始化函数，对全局变量进行初始化
Status init();

int main() {

    if(init()!=0){
        printf("程序初始化错误，即将退出...\n");
        return 0;
    }

    int nSelection=-1;//菜单选项

    printf("\n欢迎进入计费管理系统\n");
    do{
        menu_outputMenu();
        scanf("%d",&nSelection);
        switch (nSelection) {
            case 1://添加卡
                menu_add();
                break;
            case 2://查询卡
                menu_query();
                break;
            case 3://上机
                menu_logon();
                break;
            case 4://下机
                menu_settle();
                break;
            case 5://充值
                menu_addMoney();
                break;
            case 6://退费
                menu_refundMoney();
                break;
            case 7://查询统计
                break;
            case 8://注销卡
                break;
            case 9://临时卡文件操作菜单
                menu_cardfile();
                break;
            case 10:
                menu_linklist();
                break;
            case 0://退出
                menu_exitApp();
                break;
            default:
                printf("输入的菜单编号错误！\n");
                break;
        }
        printf("\n");

    }while(nSelection!=0);
    return 0;
}

Status init(){
    //先设置初值
    cardlength=0;
    cardList=NULL;
    //分配空间
    cardList=(CardList)malloc(sizeof(CardNode));
    //判断分配空间是否成功
    if(cardList==NULL)
        return -1;
    //对头指针指向的内容初始化
    cardList->next=NULL;

    return 0;
}