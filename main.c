#include "model.h"
#include <malloc.h>
#include <stdio.h>
#include "menu.h"

//初始化函数，对全局变量进行初始化
Status init();

int main() {
    //创建菜单
    Menu menu=Menu_Init();
    //全局变量初始化
    if(init()!=0){
        printf("程序初始化错误，即将退出...\n");
        return 0;
    }
    //创建菜单选项
    int nSelection=-1;
    //启动提示词
    printf("\n欢迎进入计费管理系统\n");
    //进入选项菜单
    do{
        //输出选项
        menu.OutputMenu(&menu);
        //获取用户输入
        scanf("%d",&nSelection);
        //根据用户输入执行对应功能
        switch (nSelection) {
            case 1://添加卡
                menu.Add(&menu);
                break;
            case 2://查询卡
                menu.Query(&menu);
                break;
            case 3://上机
                menu.LogOn(&menu);
                break;
            case 4://下机
                menu.Settle(&menu);
                break;
            case 5://充值
                menu.AddMoney(&menu);
                break;
            case 6://退费
                menu.RefundMoney(&menu);
                break;
            case 7://查询统计
                break;
            case 8://注销卡
                break;
            case 9://临时卡文件操作菜单
                menu.CardFile(&menu);
                break;
            case 10://链表演示菜单
                menu.LinkList(&menu);
                break;
            case 0://退出
                menu.ExitApp(&menu);
                break;
            default://非法选项报错
                printf("输入的菜单编号错误！\n");
                break;
        }
        //选项0退出
    }while(nSelection!=0);
    //析构menu
    menu.Release(&menu);
    return 0;
}

Status init(){

    return 0;
}