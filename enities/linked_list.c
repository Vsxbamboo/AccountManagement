//
// Created by vsx on 2024/4/3.
//

#include "linked_list.h"

//基本链表操作
int LinkedList_Add(LinkedList *self, void *data) {
    //开辟空间
    LinkedList_Node *p = malloc(sizeof(LinkedList_Node));
    p->data = data;
    p->next = NULL;
    //尾插
    self->tail->next = p;
    self->tail = self->tail->next;
    self->count++;
    return 0;
}

int LinkedList_Delete(LinkedList *self, int index) {
    int i = -1;
    LinkedList_Node *p = self->head;
    while (p->next != NULL) {
        i++;
        if (i == index) {
            break;
        }
        p = p->next;
    }
    if (i != index || index < 0) {
        return self->INDEX_OUT_OF_BOUND;
    } else {
        //将节点移出链表
        LinkedList_Node *t = p->next;
        p->next = p->next->next;
        //尾指针修改
        if (self->tail == p->next) {
            self->tail = p;
        }
        //清理空间
        free(t);
        self->count--;
        return 0;
    }
}

int LinkedList_Get(LinkedList *self, int index, void **data_pointer) {
    int i = -1;
    LinkedList_Node *p = self->head;
    while (p->next != NULL) {
        i++;
        if (i == index) {
            break;
        }
        p = p->next;
    }
    if (i != index || index < 0) {
        return self->INDEX_OUT_OF_BOUND;
    } else {
        *(data_pointer) = p->next->data;
        return 0;
    }
}

int LinkedList_Find(LinkedList *self, void *data) {
    int i = 0;
    LinkedList_Node *p = self->head;
    while (p->next != NULL) {
        if (self->Compare(data, p->next->data) == 1) {
            return i;
        }
        i++;
        p = p->next;
    }
    return -1;
}

struct LinkedList LinkedList_FindAll(struct LinkedList *self, void *data) {
    LinkedList result_list = LinkedList_Init();
    LinkedList_Node *p = self->head;
    while (p->next != NULL) {
        if (self->Compare(data, p->next->data) == 1) {
            result_list.Add(&result_list, p->next->data);
        }
        p = p->next;
    }
    return result_list;
}

//成员变量初始化
void LinkedList_InitVariable(LinkedList *self) {
    self->head = (LinkedList_Node *) malloc(sizeof(LinkedList_Node));
    self->head->next = NULL;
    self->tail = self->head;
    self->count = 0;
    self->INDEX_OUT_OF_BOUND = -1;
}

//成员函数初始化
void LinkedList_InitFunction(LinkedList *self) {
    self->Add = LinkedList_Add;
    self->Delete = LinkedList_Delete;
    self->Get = LinkedList_Get;
    self->Find = LinkedList_Find;
    self->FindAll = LinkedList_FindAll;
    self->Release = LinkedList_Release;
}

//构造函数
LinkedList LinkedList_Init() {
    LinkedList self;
    LinkedList_InitVariable(&self);
    LinkedList_InitFunction(&self);
    return self;
}

//析构函数
void LinkedList_Release(LinkedList *self) {
    LinkedList_Node *clear_pointer;
    while (self->head != NULL) {
        clear_pointer = self->head;
        self->head = self->head->next;
        free(clear_pointer);
    }
}