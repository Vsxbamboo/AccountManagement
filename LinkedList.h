#ifndef ACCOUNTMANAGEMENT_LINKEDLIST_H
#define ACCOUNTMANAGEMENT_LINKEDLIST_H

//通过宏定义增加链表复用性
#include "cardService.h"
#define DATA Card

typedef struct Node{
    DATA data;
    struct Node* next;
}Node,*LinkedList;

int get(LinkedList list,int index,DATA* datap);
void insert(LinkedList list,DATA* datap);
int in(LinkedList list,DATA* datap);//判断表中是否存在该卡
Card* find(LinkedList list,char *aName);//未找到返回空指针

#endif //ACCOUNTMANAGEMENT_LINKEDLIST_H
