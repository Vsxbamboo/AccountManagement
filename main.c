#include <stdio.h>
#include "menu.h"
#include "LinkedList.h"
int main() {
    //在此初始化各个数据结构
    LinkedList cardList=NULL;

    int nSelection=-1;//菜单选项
    printf("\n欢迎进入计费管理系统\n");
    do{
        outputMenu();
        nSelection=-1;
        scanf("%d",&nSelection);
        switch (nSelection) {
//            case 1://添加卡
//                add();
//                break;
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
