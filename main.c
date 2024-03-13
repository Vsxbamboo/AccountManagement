#include "model.h"
#include <malloc.h>
#include <stdio.h>
#include "menu.h"

//global包含对全局变量的声明
#include "global.c"
Card *cards=NULL;
int cardlength;

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
        /*
         * 先取一个，如果是换行符，回来再取
         * */
        char selectbuf;

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
    cards=(Card*) malloc(100*sizeof(Card));
    if(cards==NULL)
        return -1;
    cardlength=0;
    return 0;
}