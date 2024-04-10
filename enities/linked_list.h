#ifndef ACCOUNTMANAGEMENT_LINKED_LIST_H
#define ACCOUNTMANAGEMENT_LINKED_LIST_H

//基于引用的类似C++模板的链表
#include <stdlib.h>
#include "../model.h"
//链表节点
typedef struct LinkedList_Node {
    void *data;
    struct LinkedList_Node *next;
} LinkedList_Node;
//链表
typedef struct LinkedList {
    //成员变量
    struct LinkedList_Node *head;
    struct LinkedList_Node *tail;
    int count;

    //成员函数
    int (*Add)(struct LinkedList *self, void *data);

    int (*Delete)(struct LinkedList *self, int index);

    int (*Get)(struct LinkedList *self, int index, void **data_pointer);

    int (*Find)(struct LinkedList *self, void *data);

    int (*Compare)(void *a, void *b);

    struct LinkedList (*FindAll)(struct LinkedList *self, void *data);

    void (*Release)(struct LinkedList *self);

    //错误码常量
    int INDEX_OUT_OF_BOUND;
} LinkedList;

//基本链表操作
int LinkedList_Add(LinkedList *self, void *data);

int LinkedList_Delete(LinkedList *self, int index);

int LinkedList_Get(LinkedList *self, int index, void **data_pointer);

int LinkedList_Find(LinkedList *self, void *data);

struct LinkedList LinkedList_FindAll(struct LinkedList *self, void *data);

//成员变量初始化函数
void LinkedList_InitVariable(LinkedList *self);

//成员函数初始化函数
void LinkedList_InitFunction(LinkedList *self);

//构造函数
LinkedList LinkedList_Init();

//析构函数
void LinkedList_Release(LinkedList *self);


#endif //ACCOUNTMANAGEMENT_LINKED_LIST_H
