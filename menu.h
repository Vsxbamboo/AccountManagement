
#ifndef ACCOUNTMANAGEMENT_MENU_H
#define ACCOUNTMANAGEMENT_MENU_H

#include <stdio.h>
#include <string.h>
#include "model.h"
#include "service/service.h"

void menu_outputMenu();//输出菜单
void menu_add();//添加卡
void menu_query();//查询卡
void menu_exitApp();//退出
void menu_logon();//登录
void menu_settle();//下机
void menu_annul();//注销卡
void menu_addMoney();//充值
void menu_refundMoney();//退费
void menu_cardfile();


#endif //ACCOUNTMANAGEMENT_MENU_H
