
#ifndef ACCOUNTMANAGEMENT_MENU_H
#define ACCOUNTMANAGEMENT_MENU_H

#include <stdio.h>
#include <string.h>
#include "model.h"
#include "service/service.h"

typedef struct Menu{
    //成员变量
    Service service;
    //成员函数
    //输出菜单
    void (*OutputMenu)(struct Menu* self);
    //添加卡
    void (*Add)(struct Menu* self);
    //查询卡
    void (*Query)(struct Menu* self);
    //退出
    void (*ExitApp)(struct Menu* self);
    //登录上机
    void (*LogOn)(struct Menu* self);
    //下机
    void (*Settle)(struct Menu* self);
    //注销卡
    void (*Annul)(struct Menu* self);
    //充值
    void (*AddMoney)(struct Menu* self);
    //退费
    void (*RefundMoney)(struct Menu* self);
    //卡文件演示
    void (*CardFile)(struct Menu* self);
    //链表演示
    void (*LinkList)(struct Menu* self);
    //析构函数
    void (*Release)(struct Menu* self);
}Menu;

void Menu_InitVariable(Menu* self);
void Menu_InitFunction(Menu* self);
Menu Menu_Init();
void Menu_Release(Menu* self);
void Menu_OutputMenu(Menu* self);
void Menu_Add(Menu* self);
void Menu_Query(Menu* self);
void Menu_ExitApp(Menu* self);
void Menu_LogOn(Menu* self);
void Menu_Settle(Menu* self);
void Menu_Annul(Menu* self);
void Menu_AddMoney(Menu* self);
void Menu_RefundMoney(Menu* self);
void Menu_CardFile(Menu* self);
void Menu_LinkList(Menu* self);

#endif //ACCOUNTMANAGEMENT_MENU_H
