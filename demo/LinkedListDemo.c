//
// Created by vsx on 2024/3/20.
//

#include "LinkedListDemo.h"

void ll_init(){
    list=(LinkedList)malloc(sizeof(LinkedListNode));
    list->next=NULL;
}
int ll_insert(int e,int index){
    if(list==NULL){
        printf("list null\n");
        return -1;
    }
    int i=0;
    LinkedList p=list;
    while(p->next!=NULL){
        if(i==index){
            break;
        }else{
            p=p->next;
            i++;
        }
    }

    LinkedList t=p->next;
    p->next=(LinkedList)malloc(sizeof(LinkedListNode));
    p->next->data=e;
    p->next->next=t;
    return 0;
}
int ll_del(int index){
    int i=0;
    LinkedList p=list;
    while(p->next!=NULL){
        if(i==index){
            break;
        }else{
            p=p->next;
            i++;
        }
    }
    if(i!=index){
        return -1;
    }else{
        LinkedList t=p->next;
        p->next=p->next->next;
        free(t);
        return 0;
    }
}
int ll_get(int index,int *pInt){
    int i=0;
    LinkedList p=list;
    while(p->next!=NULL){
        if(i==index){
            break;
        }else{
            p=p->next;
            i++;
        }
    }
    if(i!=index){
        return -1;
    }else{
        *pInt=p->next->data;
        return 0;
    }
}

void ll_release(){
    LinkedList c;
    while(list->next!=NULL){
        c=list;
        list=list->next;
        free(c);
    }
}

void ll_show(){
    LinkedList p=list;
    while(p->next!=NULL){
        printf("%d ",p->next->data);
        p=p->next;
    }
    printf("\n");
}