
#ifndef ACCOUNTMANAGEMENT_MENU_H
#define ACCOUNTMANAGEMENT_MENU_H

#include <stdio.h>
#include <string.h>
#include "model.h"
#include "service/service.h"

typedef struct Menu{
    //��Ա����
    Service service;
    //��Ա����
    //����˵�
    void (*OutputMenu)(struct Menu* self);
    //��ӿ�
    void (*Add)(struct Menu* self);
    //��ѯ��
    void (*Query)(struct Menu* self);
    //�˳�
    void (*ExitApp)(struct Menu* self);
    //��¼�ϻ�
    void (*LogOn)(struct Menu* self);
    //�»�
    void (*Settle)(struct Menu* self);
    //ע����
    void (*Annul)(struct Menu* self);
    //��ֵ
    void (*AddMoney)(struct Menu* self);
    //�˷�
    void (*RefundMoney)(struct Menu* self);
    //���ļ���ʾ
    void (*CardFile)(struct Menu* self);
    //������ʾ
    void (*LinkList)(struct Menu* self);
    //��������
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
